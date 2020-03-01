/*
* JAGRO.h
* Define static data
* Dana Simmons 2020 
*
*/

#define WATER_BTN D9
#define LIGHT_BTN D10

#define PUBLISH_RATE 5000
#define SOIL_HUM_PIN A0
// #define SOIL_HUM_VCC D8

#define ONE_WIRE_BUS 14
#define SDA_PIN D1
#define SCL_PIN D2
#define BME_ADDR 0x76
#define LCD_ADR 0x32

#define RELAY_PIN_1 D0
#define RELAY_PIN_2 D6
#define RELAY_PIN_3 D7
#define RELAY_PIN_4 D8
int RELAY_PINS[][2]={
  {RELAY_PIN_1, 1},
  {RELAY_PIN_2, 1},
  {RELAY_PIN_3, 1},
  {RELAY_PIN_4, 1} 
};
float airHum = 0;
float airTemp = 0;
float soilTemp = 0;
float soilHum = 0;
long last_publish = 0;

bool SAMPLING = false;