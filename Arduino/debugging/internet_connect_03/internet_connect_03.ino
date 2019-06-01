/*********
  Used tutorial: 
  https://randomnerdtutorials.com/wifimanager-with-esp8266-autoconnect-custom-parameter-and-manage-your-ssid-and-password/
*********/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

#include "Mosquitto.h"

//.......................................

const int container1 = D8;
const int container2 = D3;
//const int DEBUG_LEVEL         = 3;
const int send_requests_count = 10;
const int local_id            = 1;

const String mqtt_host        = "rety.dynu.net";
const int mqtt_port           = 1883;
const String mqtt_id          = "Dispenser:" + String(local_id);

const String mqtt_topic_in    = "server-dispenser";
const String mqtt_topic_out   = "dispenser-server";

// Set web server port number to 80
WiFiServer server(80);

//.......................................

Mosquitto mosquitto;

void setup() {
  pinMode(container1,OUTPUT);
  digitalWrite(container2,LOW);
  pinMode(container1,OUTPUT);
  digitalWrite(container2,LOW);
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
  int executeContainer = 0;
  switch (container) {
    case 1: 
      executeContainer = container1;
      break;
    case 2:
      executeContainer = container2;
      break;
    default: Serial.println("ERROR");
    }
  digitalWrite(executeContainer,HIGH);
  delay(1000);
  digitalWrite(executeContainer,LOW);
  delay(500);
}
