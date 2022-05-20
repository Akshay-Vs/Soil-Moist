# Soil-Moist
An Arduino based soil moisture monitor

Meterials Required
------------------
Arduino UNO
16x2 LCD
Moisture Sensor
Relay connected to a water pump

Pin outs
--------
LCD pinouts: 
  rs LCD to 12 UNO,
  en LCD to 11 UNO,
  d4 LCD to 5 UNO,
  d5 LCD to 4 UNO,
  d6 LCD to 3 UNO,
  d7 LCD to 2 UNO,
  A LCD to 13 UNO

Sensor output(A0) to A0 UNO

Relay to 10 UNO

Features
--------

- Read and Display soil humidity
- Turn on the water pump when the soil humidity is low
- Save Minimun Humidity, Maximum Humidity, and Total Motor spins in to EEPROM

Circuit Diagram
---------------
<img src="https://github.com/Akshay-Vs/Soil-Moist/blob/main/Circuit.PNG">
