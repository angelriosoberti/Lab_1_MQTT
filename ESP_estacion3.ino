#include <PubSubClient.h>
#include <ESP32HTTPUpdateServer.h>
#include <EspMQTTClient.h>

EspMQTTClient client(
  "Family_rios",
  "yeraybenjamin",
  "192.168.1.132",  // Boker MQTT 
  "",// aqui va el usuario mqtt
  "",//aqui va la contraseña mqtt
  "estacion3"      // Cliente, nombre del dispositivo 
);
int variable=0;
void setup() {
  Serial.begin(9600);
  
  }

void onConnectionEstablished() {

  client.subscribe("embasadora/estacion3/Produccion", [] (const String &payload)  {
    Serial.println(payload);
  });
 /*   client.subscribe("mytopic/test", [] (const String &payload)  {
    Serial.println(payload);
  });*/

 
  client.publish("embasadora/estacion1/S_calidad",String(variable) /*colocar aca la variable en string*/);
  client.publish("embasadora/estacion1/S_numbotella","2" /*colocar aca la variable*/);
  client.publish("embasadora/estacion1/S_", "1"/*colocar aca la variable*/);
  client.publish("embasadora/estacion1/S_volumen","1800" /*colocar aca la variable*/);

}

void loop() {
  variable = variable + 1 ;
  client.loop();
  onConnectionEstablished();
  delay(1000);
}