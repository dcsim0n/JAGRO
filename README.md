# JAGRO: Just Another Garden RObot
Extendable, Scalable. Data powered automation for your garden.

## Features

+ Remote monitoring of sensor data (Temperature, Moisture, Lighting, Pumps Control)
+ Create schedules for regular tasks (Lighting)
+ Create triggers to regulate environment (Temperature, Soil Moisture)
+ Remote control (Control relays via mobile app)


## Bill of Materials 

These are the parts necessary to build a basic JAGRO node
+ NodeMCU ESP8266 Microcontroller
+ BLE280 Temperature, Humidity, Pressure sensor (air temperature, humidity)
+ Capacitive Soil Humidity sensor (soil moisture)
+ DS18B20 Water proof temperature sensor (soil temperature)
+ 4x 5v Relay Control modules
+ ATX Switching power supply
+ 12v / 5v water pump
+ Lighting / Ventilation of your choice (DC or AC powered)

## NodeMCU Module design specs

### Pinouts

D# pin | description / assignment
---------------------------------
D0     | Relay #1 / Lighting
D1     | I2C SDA (BME, LCD interface)
D2     | I2C SCL (BME, LCD interface)
D3     | Button 1 (Light_BTN)
D4     | Button 3 (Emergency Stop)
D5     | One wire data (Dallas OneWire interface)
D6     | Relay #2 / Water pump
D7     | Relay #3 / Fan, ventilation
D8     | Relay #4 / Aux
D9     | Button 2 (WATER_BTN)
A0     | Soil humidity sensor

## Building and uploading to NodeMCU microcontroller

Pre-reqs
+ arduino-cli
+ nodemcuv2 board definition
+ Arduion libraries defined in `JAGRO.ini`
**Requires `nodemcuv2` board definition has been installed**
+ To compile project and generate .elf binary file: `$ ./compile.sh`.
+ To upload to a connected NodeMCU board
  + Find the com port with `$ arduino-cli board list`
  + Upload to the board with `$ ./upload.sh COM#`
