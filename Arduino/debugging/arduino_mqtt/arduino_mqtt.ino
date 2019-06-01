/*********
  Used tutorial: 
  https://randomnerdtutorials.com/wifimanager-with-esp8266-autoconnect-custom-parameter-and-manage-your-ssid-and-password/
*********/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

#include "mqtt.h"
#include "motorDriver.h"
#include "pressureSensor.h"
#include "shift_165.h"
//.......................................

const int pin  = A0;
#define IN1   D6 
#define IN2   D7
#define PWMA  D4 //base
#define PWMB  D3 //pen
#define PWMA1 D2 // pump
#define PWMA2 D5

#define enable D1
#define load   1 //GPIO3
#define clock  D8
#define data   D0


const int exitContainer = 0;
int neededContainer = 0;

const int local_id            = 1;
const String mqtt_id          = "Dispenser:" + String(local_id);
const int mqtt_port           = 1883;
const char* mqtt_server       = "rety.dynu.net";

const String in_topic    = "server-dispenser";
const String out_topic   = "outTopic";

// Set web server port number to 80
WiFiServer server(81);

//.......................................

Mosquitto mosquitto = Mosquitto(mqtt_server, mqtt_port, mqtt_id, in_topic, out_topic);

Motor base = Motor(IN1,IN2, PWMA);
Motor pump = Motor(IN1, IN2, PWMB);
Motor h = Motor(IN1,IN2, PWMA1);
Motor v = Motor(IN1,IN2, PWMA2);
Shift_165 shift_register = Shift_165(enable, load, clock, data);
Sensor sensor = Sensor(A0);

void setup() {
  
Serial.begin(9600);
shift_register.Shift_bytes();
WiFiManager wifiManager;

  
 // Uncomment and run it once, if you want to erase all the stored information
//  wifiManager.resetSettings();
//  Serial.println("resetSettings");

  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("Connected.");

//.......................................
  
  Serial.println("Connecting mosquitto broker");

  mosquitto.mqtt_setup();
  mosquitto.setCallback(mqttCallback);

}

//.......................................

void loop(){
  
  if(! mosquitto.read()) Serial.println("Failed to read !!!");
  
}

//.......................................

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//  Serial.println(".....");

  String msg;
  for (int i = 0; i < length; i++)
  {
//    Serial.print((char) payload[i]);
    msg += (char) payload[i];
  }

//  Serial.println();

  String tmp = msg.substring(5);
  if(tmp.indexOf(":") <= 0)
    {
      mosquitto.publish("error");
      return;
    }
  int container = (tmp.substring(0, tmp.indexOf(":"))).toInt();
  int count = (tmp.substring(tmp.indexOf(":") + 1)).toInt();
  if (count > 0) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println(".....");
    Serial.print("container ");
    Serial.println(container);
    Serial.print("count ");
    Serial.println(count);
  }
  neededContainer = container;
  for (int i = 0; i < count; i++) {
    sensor.SetState();
    pickPill();
  }
  

//  {
//    
//  // publish case-todo  
//  }
}

//......................................
//void getPill() {

//}

void pickPill () {  
  char msg[50];
  snprintf (msg, 75, "Container #%ld", neededContainer);
  mosquitto.publish(msg);
//  Serial.print("Pick pill container: ");
  
  //setup pen
  
  Serial.println("Setup");
  movePen(1024,0,h);
  
//  Serial.println("BASE");
//  mosquitto.publish("BASE");
//  base.drive(800,2000);
//
////  Serial.println("Horizontal R");
//    mosquitto.publish("Horizontal forward");
//    movePen(-1024,neededContainer,h);
////  delay(1000);
//////
//    Serial.println("PUMP");
//    mosquitto.publish("PUMP on");
//    pump.drive(1024);
//////
//    Serial.println("DOWN");
//    mosquitto.publish("Vertical DOWN");
//    movePenDown(-600,v);
//////
//    Serial.println("UP");
//    mosquitto.publish("Vertical UP");
//    movePen(600,7,v);
//    
//////  
////////  
//    Serial.println("Horizontal L");
//    mosquitto.publish("Horizontal backward");
////  delay(2000);
//    movePen(1024,exitContainer,h);
//    pump.brake(); 
//    delay(8000);
  }

void movePen(int speed, int container, Motor motor) {
  int* shifted = shift_register.Shift_bytes();
  Serial.println(shifted[container]);
  motor.drive(speed);
  while (shifted[container] != 1) {
    shifted = shift_register.Shift_bytes();
    Serial.print(shifted[container]);
//        shift_register.ShiftPrint(shifted);       
    yield();  
    }
  motor.brake();
  
  Serial.println("stop");
  }
void movePenDown(int speed, Motor motor) {
  Serial.println("Start motor");
  motor.drive(speed);
  while (!sensor.PressureCheck()) {
    yield();
    }
    motor.brake();
//    pump.brake();
  }
