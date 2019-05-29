/*********
  Used tutorial: 
  https://randomnerdtutorials.com/wifimanager-with-esp8266-autoconnect-custom-parameter-and-manage-your-ssid-and-password/
*********/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

#include "Mosquitto.h"
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
//const int DEBUG_LEVEL         = 3;
const int send_requests_count = 10;
const int local_id            = 1;

const String mqtt_host        = "rety.dynu.net";
const int mqtt_port           = 1883;
const String mqtt_id          = "Dispenser:" + String(local_id);

const String mqtt_topic_in    = "server-dispenser";
const String mqtt_topic_out   = "dispenser-server";

// Set web server port number to 80
WiFiServer server(81);

//.......................................

Mosquitto mosquitto;
Motor base = Motor(IN1,IN2, PWMA);
Motor pump = Motor(IN1, IN2, PWMB);
Motor h = Motor(IN1,IN2, PWMA1);
Motor v = Motor(IN1,IN2, PWMA2);
Shift_165 shift_register = Shift_165(enable, load, clock, data);
Sensor sensor = Sensor(A0);

void setup() {
  
Serial.begin(9600);
WiFiManager wifiManager;
  
 // Uncomment and run it once, if you want to erase all the stored information
//  wifiManager.resetSettings();
//  Serial.println("resetSettings");

  wifiManager.autoConnect("AutoConnectAP");
  
  Serial.println("Connected.");

//.......................................
  
  Serial.println("Connecting mosquitto broker");

  mosquitto.setMqttReconnectCount(send_requests_count);
//  mosquitto.setDebugLevel(DEBUG_LEVEL);
  mosquitto.setCallback(mqttCallback);

  mosquitto.setup(mqtt_host, mqtt_id, mqtt_port, mqtt_topic_in, mqtt_topic_out);

}

//.......................................

void loop(){
  
  if(! mosquitto.read()) Serial.println("Failed to read !!!");
  
}

//.......................................

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(".....");

  String msg;
  for (int i = 0; i < length; i++)
  {
    Serial.print((char) payload[i]);
    msg += (char) payload[i];
  }

  Serial.println();

  String tmp = msg.substring(5);
  if(tmp.indexOf(":") <= 0)
    {
      mosquitto.publish("error");
      return;
    }
  int container = (tmp.substring(0, tmp.indexOf(":"))).toInt();
  int count = (tmp.substring(tmp.indexOf(":") + 1)).toInt();
  
  Serial.print("container ");
  Serial.println(container);
  Serial.print("count ");
  Serial.println(count);

  for (int i = 0; i < count; i++) {
    getPill(container);
  }
  

//  {
//    
//  // publish case-todo  
//  }
}

//......................................
void getPill(int container) {
  Serial.print("......container...... ");
  Serial.println(container);

  sensor.SetState();
  pickPill();
}

void pickPill () {
//  Serial.println("BASE");
//  delay(2000);
//  base.drive(800,2000);
//  delay(2000);
//  
//  Serial.println("Horizontal R");
//  delay(2000);
//  movePen(1024,neededContainer,h);
//  delay(2000);
//
  Serial.println("PUMP");
  pump.drive(1000);
//  delay(1000);
  
  Serial.println("DOWN");
//  delay(1000);
  movePenDown(1024,v);
   delay(1000);

delay(3000);
//  Serial.println("UP");
//  delay(2000);
//  movePen(-1024,neededContainer,v);
//  delay(2000);
//  
//  Serial.println("Horizontal L");
//  delay(2000);
//  movePen(-1024,neededContainer,h);
//  delay(2000);
  }

  
void movePen(int speed, int container, Motor motor) {
  int* shifted = shift_register.Shift_bytes();
  Serial.println(shifted[container]);
  motor.drive(speed);
  while (shifted[container] != 0) {
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
    pump.brake();
  }
