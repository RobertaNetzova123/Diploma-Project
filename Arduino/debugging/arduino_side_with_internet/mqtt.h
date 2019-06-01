#ifndef _MQTT__H_
#define _MQTT__H_

#define MQTT_MAX_PACKET_SIZE 300

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class Mosquitto {

public:
	Mosquitto(String server, int port, String id, String in_topic, String out_topic);
	void mqtt_setup();
  bool read();
  void setCallback(void (*callback)(char*, uint8_t*, unsigned int));
  bool reconnect();
  bool publish(String message);
//   bool connection_check();


private:
	WiFiClient _client;
	PubSubClient _mqtt_client;
	String _server, _id,_in_topic, _out_topic;
	int _port;
  bool connection_check();
};
#endif
