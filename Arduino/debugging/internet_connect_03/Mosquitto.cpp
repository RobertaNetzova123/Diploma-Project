#include "Mosquitto.h"
//library - https://pubsubclient.knolleary.net/api.html#subscribe
//######################################################################################################################
bool Mosquitto::reconnect()
{
	int count = _mqtt_reconnect_count;

	while ( ! _mqtt_client.connected() )
	{
		  Serial.print("Connecting MQTT server ...");

		if ( _mqtt_client.connect( _mqtt_id.c_str()))
		{
			  Serial.println("OK");
			_mqtt_client.subscribe( _mqtt_topic_in.c_str() );
		} else {
      
				Serial.print("(");
				Serial.print( _mqtt_client.state() );
				Serial.println(") FAILED");
       
			if( (--count) <= 0 ) break;
			delay( 2000 );
		}
	}

	return _mqtt_client.connected();
}

//######################################################################################################################
//void Mosquitto::setup() { 
//  _mqtt_client.setServer( _mqtt_host.c_str(), _mqtt_port ); 
//}
//
////######################################################################################################################
//void Mosquitto::setup(String host, String id, int port)
//{
//	setMqttHost( host );
//	setMqttId( id );
//	setMqttPort( port );
//	
//	setup();
//}

//######################################################################################################################
void Mosquitto::setup(String host, String id, int port, String topic_in, String topic_out)
{
	setMqttTopicIn( topic_in );
	setMqttTopicOut( topic_out );

  setMqttHost( host );
  setMqttId( id );
  setMqttPort( port );

  _mqtt_client.setServer( _mqtt_host.c_str(), _mqtt_port ); 
//	setup(host, id, port);
}

//######################################################################################################################
void Mosquitto::setCallback(void (*callback)(char*, uint8_t*, unsigned int))
{
	_mqtt_client.setCallback(callback);
}

//######################################################################################################################
bool Mosquitto::connection_checkup () {
      if ( ! _mqtt_client.connected() ) reconnect();
      if ( ! _mqtt_client.connected() ) return false;
      return true;
  }
bool Mosquitto::read()
{
	if (! connection_checkup()) return false;

	return _mqtt_client.loop();
}

//######################################################################################################################
bool Mosquitto::publish(String message)
{
	if (! connection_checkup()) return false;

	_mqtt_client.publish( _mqtt_topic_out.c_str(), message.c_str());
  Serial.println("Publish message: " + message);

	return true;
}
