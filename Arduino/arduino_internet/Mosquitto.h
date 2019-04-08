#ifndef _MOSQUITTO__H_
#define _MOSQUITTO__H_

#define MQTT_MAX_PACKET_SIZE 300

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class Mosquitto {
	private:
		WiFiClient _client;
		PubSubClient _mqtt_client;

		int _mqtt_reconnect_count;

	protected:
		String _mqtt_host;
		String _mqtt_id;
		int _mqtt_port;
		String _mqtt_topic_in;
		String _mqtt_topic_out;

	public:
		void setup();
		void setup(String host, String id, int port);
		void setup(String host, String id, int port, String topic_in, String topic_out);

		bool reconnect();
		bool read();
		bool publish(String message);
    bool connection_checkup();

		void setMqttHost(String host) { _mqtt_host = host; }
		void setMqttId(String id) { _mqtt_id = id; }
		void setMqttPort(int port) { _mqtt_port = port; }
		void setMqttTopicIn(String topic_in) { _mqtt_topic_in = topic_in; }
		void setMqttTopicOut(String topic_out) { _mqtt_topic_out = topic_out; }
		void setMqttReconnectCount(unsigned int count) { _mqtt_reconnect_count = count; }
		void setCallback(void (*callback)(char*, uint8_t*, unsigned int));
	public:
		Mosquitto() {
		  _mqtt_client.setClient(_client); 
		  _mqtt_reconnect_count = 0; 
		};
		~Mosquitto() {};
};

#endif
