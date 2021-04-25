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

float S_presionCO2;
String sub_Prod;
String sub_botellas;

void setup() {
  Serial.begin(115200);
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
  }

void onConnectionEstablished() {

  // Suscribirse a el topic de produccion y 
  client.subscribe("embasadora/estacion4/produccion", [](const String & payload) {
    Serial.println(payload);
    sub_Prod = payload;
  });
  // Suscribirse a el topic de stock_botellas y 
    client.subscribe("embasadora/estacion2/stockbotellas", [](const String & payload1) {
    Serial.println(payload1);
    sub_botellas = payload1;
  });
  
// Publicaciones con sus respectivos topics.
  client.publish("embasadora/estacion3/S_presionCO2", String(S_presionCO2) /*colocar aca la variable en string*/ );

}


void loop() {
    //colocar la logica 
  
  client.loop();
  



if (sub_Prod == "0" && sub_botellas == "0")
{
  S_presionCO2 = 0;
}else{
S_presionCO2 = random(1,3);
}

 
  onConnectionEstablished();
    delay(1500);

}