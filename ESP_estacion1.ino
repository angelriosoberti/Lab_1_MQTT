#include <PubSubClient.h>
#include <ESP32HTTPUpdateServer.h>
#include <EspMQTTClient.h>

EspMQTTClient client(
  "Family_rios",
  "yeraybenjamin",
  "192.168.1.132",  // Boker MQTT 
  "",// aqui va el usuario mqtt
  "",//aqui va la contraseña mqtt
  "estacion1"      // Cliente, nombre del dispositivo 
);
int S_flujo;
int S_temperatura;
bool S_particular;
int S_Volumen = 2000;
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
  client.publish("embasadora/estacion1/S_flujo", String(S_flujo) /*colocar aca la variable en string*/ );
  client.publish("embasadora/estacion1/S_temperatura",String(S_temperatura)  /*colocar aca la variable*/);
  client.publish("embasadora/estacion1/S_particula", String(S_particular)/*colocar aca la variable*/);
  client.publish("embasadora/estacion1/S_volumen",String(S_Volumen)/*colocar aca la variable*/);

}


void loop() {
    //colocar la logica 
  
  client.loop();
  
if (sub_Prod == "0" && sub_botellas == "0")
{
        S_flujo = 0;
        S_temperatura= 0;
        S_particular= false;
}else{
        S_flujo = random(200,600);
        S_temperatura= random(1,5);
        S_particular= true;
        S_Volumen = S_Volumen - S_flujo/1000;
}
  onConnectionEstablished();
    delay(1500);

}