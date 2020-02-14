/*
* JAGRO.h
* Define static data
* Dana Simmons 2020 
*
*/
#define MQTT_PORT 1833
#define SOIL_HUM_PIN A0
#define SOIL_HUM_VCC D8

#define ONE_WIRE_BUS 14
#define SDA_PIN D1
#define SCL_PIN D2
#define BME_ADDR 0x76
#define LCD_ADR 0x32

#define RELAY_PIN_1 D0
#define RELAY_PIN_2 D6
#define RELAY_PIN_3 D7
#define RELAY_PIN_4 D9

float airHum = 0;
float airTemp = 0;
float soilTemp = 0;
float soilHum = 0;
long last_publish = 0;

int relayStatus1 = 1; // 1 = HIGH, 0 = LOW. HIGH = OFF, LOW = ON
int relayStauts2 = 1;
int relayStatus3 = 1;
int relayStatus4 = 1;
