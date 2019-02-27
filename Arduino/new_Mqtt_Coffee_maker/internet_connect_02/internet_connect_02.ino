/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager
#include "Mosquitto.h"
#include <ArduinoJson.h>

#define __APP_VERSION__  "1.0.1 build 2018-12-27"

//................................

const int DEBUG_LEVEL         = 3;
const int send_requests_count = 10;
const int local_id            = 1;

const String mqtt_host        = "rety.dynu.net";
const int mqtt_port           = 1883;
const String mqtt_id          = "Coffee_Machine:" + String(local_id);
const String mqtt_user        = "rety";
const String mqtt_password    = "retypass";
const String mqtt_topic_in    = "machine";
const String mqtt_topic_out   = "server";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

//.........
Mosquitto mosquitto;

void setup() {
  Serial.begin(9600);
  

  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  
  // Uncomment and run it once, if you want to erase all the stored information
//  wifiManager.resetSettings();
//  Serial.println("resetSettings");
  
  // set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
  
  server.begin();

  //....................
  Serial.println("Connecting mosquitto broker");

  mosquitto.setMqttReconnectCount(send_requests_count);
  mosquitto.setDebugLevel(DEBUG_LEVEL);
  mosquitto.setCallback(mqttCallback);

  mosquitto.setup(mqtt_host, mqtt_id, mqtt_user, mqtt_password, mqtt_port, mqtt_topic_in, mqtt_topic_out);
}

void loop(){

 if(! mosquitto.read()) Serial.println("Failed to read !!!");
}

//.......................................

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String msg;
  for (int i = 0; i < length; i++)
  {
    Serial.print((char) payload[i]);
    msg += (char) payload[i];
  }

  Serial.println();

  if(msg.equals("on_off")) doOnOff();
  else if(msg.equals("make_one_cup")) doStartOneCup();
  else if(msg.equals("make_two_cups")) doStartTwoCups();
  else if(msg.equals("get_version"))
  {
    mosquitto.publish("version:" + String(__APP_VERSION__));
    return;
  }else if(msg.startsWith("set:")){
    String tmp = msg.substring(4);

    if(tmp.indexOf(":") <= 0)
    {
      mosquitto.publish("error");
      return;
    }
      mosquitto.publish("success");
  }
}
//........................................
void doOnOff() {Serial.println ("Switch ON OFF funcion");}
void doStartOneCup() {Serial.println ("One cup function");}
void doStartTwoCups() {Serial.println ("One cup function");}
