#include <PubSubClient.h>

#include "EspMQTTClient.h"

EspMQTTClient client(
  "Family_rios",
  "yeraybenjamin",
  "192.168.1.132",  // Boker MQTT 
  "",// aqui va el usuario mqtt
  "",//aqui va la contraseña mqtt
  "estacion4"      // Cliente, nombre del dispositivo 
);
int produccion;
int botellas;
int btl;
int req_botellas;
int Six_pack;
String sub_botellas;

void setup() {
  Serial.begin(115200);
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
  }

void onConnectionEstablished() {
  // Suscribirse a el topic de stock_botellas y 
    client.subscribe("embasadora/estacion2/stockbotellas", [](const String & payload1) {
    Serial.println(payload1);
    sub_botellas = payload1;
  });
  // Publicaciones con sus respectivos topics.
  client.publish("embasadora/estacion4/produccion", String(produccion) /*colocar aca la variable en string*/ );
  client.publish("embasadora/estacion1/botellas",String(botellas)  /*colocar aca la variable*/);
  client.publish("embasadora/estacion1/six_pack", String(Six_pack)/*colocar aca la variable*/);
  }


void loop() {
    //colocar la logica 
  
  client.loop();
  
if ( sub_botellas == "0")
{
  req_botellas= produccion
       
}else{
  produccion -=;
  botellas+=;
  btl +=;
  if(btl >= 6){
     Six_pack +=;
    btl = 0; 
  }
        
}
  onConnectionEstablished();
    delay(1500);

}