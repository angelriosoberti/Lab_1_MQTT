#include <PubSubClient.h>
#include "EspMQTTClient.h"

EspMQTTClient client(
  "Family_rios",
  "yeraybenjamin",
  "192.168.1.132",  // Boker MQTT 
  "",// aqui va el usuario mqtt
  "",//aqui va la contraseña mqtt
  "estacion2"      // Cliente, nombre del dispositivo 
);


bool S_Calidad;
int stock_botellas = 500;
String sub_Prod;
String sub_botellas;

void setup() {
  Serial.begin(115200);
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  //client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
  }

void onConnectionEstablished() {

  // Suscribirse a el topic de produccion y 
  client.subscribe("embasadora/estacion4/produccion", [](const String & payload) {
    Serial.println(payload);
    sub_Prod = payload;
  });

  
// Publicaciones con sus respectivos topics.
  client.publish("embasadora/estacion2/S_Calidad", String(S_Calidad) /*colocar aca la variable en string*/ );
  client.publish("embasadora/estacion2/stockbotellas",String(stock_botellas)  /*colocar aca la variable*/);
  

}


void loop() {
    //colocar la logica 
  
  client.loop();
  S_Calidad = true;
  stock_botellas -=;
 
  onConnectionEstablished();
    delay(1500);


}