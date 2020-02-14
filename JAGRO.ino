/*
*
* Just Another Garden RObot
* NodeMCU Based Environment Module ( Temperature, Humidity, Water and Lighting control )
* Dana Simmons 2020
*
*/
#include "JAGRO.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <OneWire.h>
#include <DalasTemperature.h>

//Setup global objects
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_BME280 bme;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
// mq_tt topics for input output


// * MUST HAVE A SECRET.H FILE WITH THE FOLLOWING DEFINES * //
//const char auth[] 
//const char ssid[]  
//const char pass[]  

//const char* mqtt_server 
//const char* mqtt_user 
//const char* mqtt_pass 
#include "secrets.h"

// Perform device setup

void setup() {
  // start serial ouput for debugging
  Serial.begin(9600);
  Serial.println("JAGRO: Starting up...");
  pinMode(RELAY_PIN_1,OUTPUT);
  pinMode(RELAY_PIN_2,OUTPUT);
  pinMode(RELAY_PIN_3,OUTPUT);
  pinMode(RELAY_PIN_4,OUTPUT);
  // setup wifi connection
  // We start by connecting to a WiFi network
  Serial.print("Connecting to: ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // start i2c bus and bme sensors
  Wire.begin(SDA_PIN,SCL_PIN);
  bme.begin(BME_ADDR,&Wire);
  // start 1 wire interface
  DS18B20.begin();
  // setup unique id for this unit
  // setup mqtt connection and set callback for messages
  Serial.print("Connecting to mqtt server: ");
  Serial.println(mqtt_server);
  client.setServer(mqtt_server, MQTT_PORT);
  client.setCallback(callback);

  randomSeed(micros());
}


void loop() {
}
