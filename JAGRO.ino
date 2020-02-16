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
#include <DallasTemperature.h>

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

void toggleRelay(int relay, int state){
  // RELAY_PINS is 2D array
  // Hardware pin is at [idx][0]
  // Pin state is at [idx][1]
  digitalWrite(RELAY_PINS[relay][0], state);
  RELAY_PINS[relay][1] = state;
  char topic[50]; 
  sprintf(topic,"jagro/JAGRO1/relay/%d/status",relay + 1);
  char msg[2]= "";
  sprintf(msg,"%d",state);
  client.publish(topic,msg);
}
void callback(char* topic, byte* payload, unsigned int length){
  //Handle incoming messages
  Serial.print("Recieved Message: ");
  
  Serial.println(topic);
  Serial.println(payload[0]);
  
  if(strcmp(topic,"jagro/JAGRO1/relay/1") == 0){
    char cmd = payload[0];
    Serial.println(cmd);
    switch (cmd)
    {
    case '1':
      Serial.println("Turning relay 1 off");
      toggleRelay(0,HIGH);
      break;
    case '0':
      Serial.println("Turning relay 1 on!");
      toggleRelay(0,LOW);
      break;
    default:
      break;
    }
  }
}

void reconnect(){
  // Connected to mqtt_server
  // Subscribe to relay control topics
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    // Attempt to connect
    if (client.connect(UNIQUE_ID, mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe("jagro/JAGRO1/relay/1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

float readSoilHum(){
  return 0;
}
void readSensors(){
  //Send sensor data
  airTemp = bme.readTemperature();
  airHum = bme.readHumidity();
  Serial.print("Temp: ");
  Serial.println(airTemp);
  Serial.print("Hum: ");
  Serial.println(airHum);

  DS18B20.requestTemperatures();
  soilTemp = DS18B20.getTempCByIndex(0);
  soilHum = readSoilHum();
}

void publish(){
  char buff[5];
  dtostrf(airTemp,5,2,buff);
  client.publish("jagro/JAGRO1/sensor/1",buff);
  dtostrf(airHum,5,2,buff);
  client.publish("jagro/JAGRO1/sensor/2",buff);
  dtostrf(soilTemp,5,2,buff);
  client.publish("jagro/JAGRO1/sensor/3",buff);
  dtostrf(soilHum,5,2,buff);
  client.publish("jagro/JAGRO1/sensor/4",buff);
}
void setup() {
  // start serial ouput for debugging
  Serial.begin(9600);
  Serial.println("JAGRO: Starting up...");
  pinMode(RELAY_PIN_1,OUTPUT);
  pinMode(RELAY_PIN_2,OUTPUT);
  pinMode(RELAY_PIN_3,OUTPUT);
  pinMode(RELAY_PIN_4,OUTPUT);

  digitalWrite(RELAY_PIN_1,1);
  digitalWrite(RELAY_PIN_2,1);
  digitalWrite(RELAY_PIN_3,1);
  digitalWrite(RELAY_PIN_4,1);
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
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  if((millis() - last_publish) > PUBLISH_RATE){
    readSensors();
    publish();
    last_publish = millis();
  }
}
