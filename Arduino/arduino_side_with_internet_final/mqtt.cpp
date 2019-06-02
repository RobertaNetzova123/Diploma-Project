//library - https://pubsubclient.knolleary.net/api.html#subscribe
#include "mqtt.h"

Mosquitto::Mosquitto(String server, int port,String id, String in_topic, String out_topic) {
	_server = server;
  _port = port;
  _id = id;
  _in_topic = in_topic;
  _out_topic = out_topic;
}

void Mosquitto::mqtt_setup() {
   _mqtt_client.setClient(_client); 
	_mqtt_client.setServer(_server.c_str(), _port);
}


void Mosquitto::setCallback(void (*callback)(char*, uint8_t*, unsigned int))
{
  _mqtt_client.setCallback(callback);
}

bool Mosquitto::reconnect() {
  int attempts = 10;
  while (!_mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (_mqtt_client.connect(_id.c_str())) {
      Serial.println("connected");
      // ... and resubscribe
      _mqtt_client.subscribe(_in_topic.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.println(_mqtt_client.state());
      if (--attempts <= 0) break;
      delay(2000);
    }
  }
  return _mqtt_client.connected();
}
bool Mosquitto::  connection_check() {
  if (!_mqtt_client.connected()) reconnect();
  if (!_mqtt_client.connected()) return false;
  return true;
  }
bool Mosquitto::read()
{
    if(! connection_check()) return false;
  return _mqtt_client.loop();
}

bool Mosquitto::publish(String message)
{
  if (!connection_check()) return false;

  _mqtt_client.publish(_out_topic.c_str(), message.c_str());
  Serial.println("Publish message: " + message);

  return true;
}

