/*
 * Pill Dispencer project Arduino Side
 * Developed by:          Roberta Netzova
 * Last updated on:       19.05.30del
 * Current version:       01.07
 * Working functionality: Base rotation; VP finding container; 
 *                        VP catching pill - With pressure class; 
 *                        main working flow; 
 *                        Check if pill has fallen in the way (pressure sensor validation)
 *                        Check if pill has fallen in the index container (Shift register validation)
 *                        Connect with Internet (in adrduino_internet code);
 * ..................TODO:.......................
 * Optimize delays
 * fix endless while in case of error
 * add comments
 * Fix case when dispencer is empty
 * 
*/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

#include "mqtt.h"

const int local_id            = 1;
const String mqtt_id          = "Dispenser:" + String(local_id);
const int mqtt_port           = 1883;
const char* mqtt_server       = "84.40.122.103";

const String in_topic    = "server-dispenser";
const String out_topic   = "outTopic";

#define CONTAINERS_COUNT 6

WiFiServer server(80);
Mosquitto mosquitto = Mosquitto(mqtt_server, mqtt_port, mqtt_id, in_topic, out_topic);

void setup() {
  
  Serial.begin(9600);
 
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("Connected.");

  Serial.println("Connecting mosquitto broker");
  mosquitto.setCallback(mqttCallback);
}

void loop(){
  
   if(! mosquitto.read()) Serial.println("Failed to read !!!");
   
  }

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//  Serial.println(".....");

  char msg[length];
  for (int i = 0; i < length; i++)
  {
//    Serial.print((char) payload[i]);
    msg[i] = (char) payload[i];
  }

 doPrescription(msg);
  
}

/*
 *................functions.................. 
 */
void doPrescription(char* msg) {
  
  int pills_count[CONTAINERS_COUNT];
  char *tmp = strtok(msg, "{,}");
    for(int i = 0; tmp != NULL && i < CONTAINERS_COUNT; i++)
    {
        String current_container = tmp;
        int count = (current_container.substring(current_container.indexOf(":")+ 1)).toInt();
        tmp = strtok(NULL, "{,}");
        pills_count[i] = count;
    }

    for(int i = 0; i < CONTAINERS_COUNT; i++)
   { 
      for (int k = 0; k < pills_count[i]; k ++) {
          pickPill(i+1);
        }
   }
  }
void pickPill (int cont) {

  Serial.print("Container ");
  Serial.println(cont);
}

