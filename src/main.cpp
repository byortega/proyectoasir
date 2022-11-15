#include <Arduino.h>
#include <Adafruit_CCS811.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>

Adafruit_CCS811 miccs;
const char* ssid = "ESP32_"; //Definimos el SSID
const char* password = "12345678"; //Definimos La contraseña
const char* mqttServer = "192.168.5.1";
const int mqttPort = 1883;
const char* mqttUser = "Asir";
const char* mqttPassword = "Asir2022";
IPAddress local_ip(192,168,5,1); //Definimos IP dispositivo
IPAddress gateway(192,168,5,1); // Definimos puerta de enlace
IPAddress subnet(255,255,255,0); //Definimos mascara de subred
WebServer server(312); // Definimos puertos del webserver
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

WiFi.softAP(ssid, password);        //Arrancamos el Punto de acceso
WiFi.softAPConfig(local_ip, gateway, subnet);
delay(100);

server.begin(); //Iniciamos el servidor
Serial.println("Servidor HTTP Arrancado");

  Serial.println("miccs811 test");

  if(!miccs.begin()){
    Serial.println("Fallo al arrancar el sensor (Verificar cableado)");
    while(1);
  }
  client.setServer(mqttServer, mqttPort);
while (!client.connected())
{      Serial.println("ConectandoMQTT...");
       if (client.connect("ESP32Client", mqttUser, mqttPassword ))
           Serial.println("Conectado mqtt");
       else
       {   Serial.print("Error:");
           Serial.print(client.state());
           delay(2000);
       }
}

  // Aqui solo cabe esperar a que el sensor empieze a funcionar
  while(!miccs.available());
}
void loop() {
  if(miccs.available()){
    if(!miccs.readData()){
      Serial.print("Concentracion Co2: ");
      Serial.print(miccs.geteCO2());
      Serial.print("(PPM), Calidad del aire(TVOC): ");
      Serial.println(miccs.getTVOC());
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  delay(500);
}