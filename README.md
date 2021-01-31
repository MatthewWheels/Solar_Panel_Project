# Solar_Panel_Project

Created by Matthew Wheeler on 11/19/2020

This mimics the brightness of the sun with an LED and then saves it on to a SD card.



The way this works is by first reading the voltage output from the Analog 0 pin (A Solar Panel) once a minute until the end of the hour. It then takes the average of all of the values and stores that into an array for each hour every day. This also then sends the hour average to the SD card to be stored in a text file (DATA.txt). Once a day completes, the program will take the average of all available days (up to the past week) and calculate the average for each hour in the day. It will then set the LED brightness to mimic the overall hour average.

### Components:
+ Solar Panel
+ Arduino or related microcontroller
+ Wiring
+ LED and resistor with relative Ohmage
+ SD card and SD card port
+ Power Supply for Arduino

### Wiring
+ Solar Panel (A0, GRND)
+ 220 Ohm Resistor (D9, LED Anode)
+ LED Diode (Resister, GRND)
+ SD Card Reader
+ + Power (5v Pin)
+ + CS (D10)
+ + MOSI (D11)
+ + MISO (D12)
+ + SCK (D13)



### Notes: 
+ using ints as much as possible to convserve memory
+ Data storade reads "Day: (Days Since Start), Hour: (Hour During the day since launch), Intensity Value: (voltage from A0)

### Things still needed to be fixed/added:
+ correction to lighting system to better resemble sunlight (adjust LED output)
+ attempt to lower memory usage since almost all is being used
