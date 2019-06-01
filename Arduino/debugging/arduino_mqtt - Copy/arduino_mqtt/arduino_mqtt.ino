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
int send_requests_count = 10;

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
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(".....");
  String str = "Hello";
  mqttSend(str);
}


void mqttSend (String &message) {
  int count = 0;
  while (message.length()) {
  
    if (count++ >send_requests_count) break;
    if (mosquitto.publish(message)) break;
  
  }

//  {
//    
//  // publish case-todo  
//  }
}


