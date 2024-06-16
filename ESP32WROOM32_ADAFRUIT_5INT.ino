///////////////////////////////////////////////////////////////////DEFINICIONES////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
// Credenciales Red WiFi
#define WIFI_SSID "iPhone de Scarlet"
#define WIFI_PASSWORD "scarlet1604"
// Credenciales Adafruit
#define ADAFRUIT_USER "*****"
#define ADAFRUIT_KEY "****"
// Servidor
#define ADAFRUIT_SERVER "io.adafruit.com"
#define ADAFRUIT_PORT 1883
char ADAFRUIT_ID[30];
// Publicar
#define ADAFRUIT_DATOS  ADAFRUIT_USER "/feeds/datos"
// Definimos las variables en las que guardaremos
int a;
// Define el led del ESP
#define pin_led 22

///////////////////////////////////////////////////////////////////DEFINICIONES////////////////////////////////////////////////////////////////////
//***********************************************************************************************************************************************//
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
//***********************************************************************************************************************************************//
////////////////////////////////////////////////////////////////DECLARAMOS FUNCIONES///////////////////////////////////////////////////////////////
void setup_wifi();
void reconnect();
void mqtt_publish(String feed, int val);
void get_MQTT_ID();
////////////////////////////////////////////////////////////////DECLARAMOS FUNCIONES///////////////////////////////////////////////////////////////
//***********************************************************************************************************************************************//
void setup() 
{
    Serial.begin(115200);
    delay(10);

    pinMode(pin_led, OUTPUT);
    digitalWrite(pin_led, LOW); 

    get_MQTT_ID();
    setup_wifi();
    client.setServer(ADAFRUIT_SERVER, ADAFRUIT_PORT);
    
    digitalWrite(pin_led, HIGH); delay(200);digitalWrite(pin_led, LOW); delay(200);
    digitalWrite(pin_led, HIGH); delay(200);digitalWrite(pin_led, LOW); delay(200);
    digitalWrite(pin_led, HIGH); delay(200);digitalWrite(pin_led, LOW); delay(200);
    digitalWrite(pin_led, HIGH); delay(200);digitalWrite(pin_led, LOW); delay(200);
}
  
void loop() 
{
    if (!client.connected()) 
    {
      reconnect();
    }

    client.loop();
    
    if (Serial.available() > 0) { // Si hay datos disponibles en el puerto serial
      int a = Serial.read(); // Lee el carácter recibido
      if (a > 0){
       Serial.print("Dato: ");Serial.print(a);
      //Publicar
       mqtt_publish(ADAFRUIT_DATOS, a);
       delay(5000);
       a = 0;
       mqtt_publish(ADAFRUIT_DATOS, a); 
      }
    }

}
//***********************************************************************************************************************************************//
//-------------------//
//*****FUNCIONES*****//
//-------------------//
//***********************************************************************************************************************************************//
////////////////////////////////////////////////////////Función para Publicar por MQTT/////////////////////////////////////////////////////////////
void mqtt_publish(String feed, int val){
    String value = String(val);
    if(client.connected()){
        client.publish(feed.c_str(), value.c_str());
        Serial.println("Publicando al tópico: " + String(feed) + " | mensaje: " + value);        
    }
}
////////////////////////////////////////////////////////Función para Publicar por MQTT/////////////////////////////////////////////////////////////
//***********************************************************************************************************************************************//
/////////////////////////////////////////////////////////Función para configurar Wifi//////////////////////////////////////////////////////////////
void setup_wifi()
{
    delay(10);
    
    // Nos conectamos a nuestra red Wifi
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(String(WIFI_SSID));

    //Serial.println(ssid);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("Conectado a red WiFi!");
    Serial.println("Dirección IP: ");
    Serial.println(WiFi.localIP());
}
////////////////////////////////////////////////////////Función para configurar Wifi///////////////////////////////////////////////////////////////
//***********************************************************************************************************************************************//
/////////////////////////////////////////////////////////Capturar el ChipID para Id de MQTT////////////////////////////////////////////////////////
void get_MQTT_ID(){
    uint64_t chipid = ESP.getEfuseMac();    
    snprintf(ADAFRUIT_ID, sizeof(ADAFRUIT_ID),"%llu", chipid );
}
/////////////////////////////////////////////////////////Capturar el ChipID para Id de MQTT////////////////////////////////////////////////////////
//***********************************************************************************************************************************************//
/////////////////////////////////////////////////////////FUNCION DE RECONECTADO////////////////////////////////////////////////////////////////////
void reconnect() 
{
    while (!client.connected()) 
    {   
        if(client.connect(ADAFRUIT_ID, ADAFRUIT_USER, ADAFRUIT_KEY))
        {
           Serial.println("MQTT conectado!");

          } else {
            Serial.print("falló :( con error -> ");
            Serial.print(client.state());
            Serial.println(" Intentamos de nuevo en 5 segundos");
            delay(5000);
          }
      }
}
/////////////////////////////////////////////////////////FUNCION DE RECONECTADO////////////////////////////////////////////////////////////////////
  
