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
 *                        Fix case when dispencer is empty - 3 attempts and terminating the recipe
 * ..................TODO:.......................
 * Optimize delays
 * fix endless while in case of error
 * add comments
 * 
*/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

#include "mqtt.h"
#include "motorDriver.h"
#include "pressureSensor.h"
#include "shift_165.h"

const int pin  = A0;
#define IN1   D6 
#define IN2   D7
#define PWMA  D4 //base
#define pump  D3 //PUMP
#define PWMA1 D2 // pump
#define PWMA2 D5

#define enable D1
#define load   1 //GPIO3
#define clock  D8
#define data   D0

#define register_number 2

#define exitContainer 0
#define upMoveStopper 7
#define downMoveStopper 9
#define SIZE  3
#define CONTAINERS_COUNT 6

bool EMPTY = false;

const int local_id            = 1;
const String mqtt_id          = "Dispenser:" + String(local_id);
const int mqtt_port           = 1883;
const char* mqtt_server       = "rety.dynu.net";

const String in_topic    = "server-dispenser";
const String out_topic   = "outTopic";



WiFiServer server(81);
Mosquitto mosquitto = Mosquitto(mqtt_server, mqtt_port, mqtt_id, in_topic, out_topic);

Motor base = Motor(IN1,IN2, PWMA);
Motor h = Motor(IN1,IN2, PWMA1);
Motor v = Motor(IN1,IN2, PWMA2);

Sensor sensor = Sensor(A0);
Shift_165 shift_register = Shift_165(enable, load, clock, data,register_number);
int size = shift_register.get_register_size();



void setup() {
  
  Serial.begin(9600);
  pinMode(pump, OUTPUT);
  digitalWrite(pump,LOW);

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("Connected.");

  Serial.println("Connecting mosquitto broker");
  mosquitto.mqtt_setup();
  mosquitto.setCallback(mqttCallback);
  
  delay(500);
  sensor.SetState();
  int shifted[size];
  shift_register.Shift_bytes(shifted);
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
  EMPTY = false;
  
  char msg[length];
  for (int i = 0; i < length; i++)
  {
//    Serial.print((char) payload[i]);
    msg[i] = (char) payload[i];
  }

  configurePrescription(msg);
}

/*
 *................functions.................. 
 */
void configurePrescription(char* msg) {
  
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
          doPrescription(i+1, pills_count[i]);
    }
}

void doPrescription(int container, int repeats) {

   for (int i = 0; i < repeats; i++) {
    sensor.SetState();
    delay(1000);
    while (!sensor.PressureCheck()) {
      deliverPill(container);
      delay(100);
      
      if (EMPTY) {
          Serial.print("EMPTY: ");
          Serial.println(container);
          digitalWrite(pump,LOW);
          return;
        }
      }    
     delay (100);
     movePen(-600,downMoveStopper,v);
     digitalWrite(pump,LOW);

  
       if (shift_register.ShiftChecker(5000,8)) {
        Serial.println ("SUCCESS");
       } else {
       Serial.println ("FAIL");
       movePen(600,upMoveStopper,v);
       return;
       }
      
      delay(2000);
      Serial.println("Moving up");
      movePen(600,upMoveStopper,v);
      delay(2000);
  }
}

  
bool is_pill_picked() {

  int dispenser_debug_count = SIZE;
  for (; dispenser_debug_count > 0; dispenser_debug_count--) {
      base.drive(-800,1000);
      movePenDown(-600,v);
      movePen(600,upMoveStopper,v);
   if (sensor.PressureCheck()) return true;
  }
  
  return false;
}
 
void deliverPill (int cont) {
  
  movePen(1024,exitContainer,h);
  
  movePen(-1024,cont,h);
 
  
  digitalWrite(pump,HIGH);
  delay(500);

  
  if (!is_pill_picked()) {
    base.drive(1000,2000);
    if (!is_pill_picked())
      EMPTY = true;
  }
 
  movePen(600,upMoveStopper,v);
  movePen(1024,exitContainer,h);
}

void movePen(int speed, int container, Motor motor) {
  
  int shifted[size];
  shift_register.Shift_bytes(shifted);
  
  Serial.println(shifted[container]);
  shift_register.ShiftPrint(shifted);
  delay(500);
  
  motor.drive(speed);
  while (shifted[container] != 1) {
    shift_register.Shift_bytes(shifted);
    Serial.print(shifted[container]);     
    yield();  
    }
  
  motor.brake();
  Serial.println();
  shift_register.ShiftPrint(shifted);
  Serial.println("#######");
  Serial.println("stop");
  delay(500);
  }
  

void movePenDown(int speed, Motor motor) {
  
  int shifted[size];
  shift_register.Shift_bytes(shifted);
  shift_register.ShiftPrint(shifted);
  delay(500);
  
  Serial.println("Start motor");
  motor.drive(speed);
 
  while (!sensor.PressureCheck()) {
     shift_register.Shift_bytes(shifted);
    Serial.print(shifted[downMoveStopper]);
     if (shifted[downMoveStopper] == 1) break;
     yield();
    }
    motor.brake();
    delay(500);
  }
