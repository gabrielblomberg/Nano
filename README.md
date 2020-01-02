# Nano

Source code for a small small unmanned aerial vehicle for recording flight time and distance, and control. Written in Arduino C as part of the ENGG1200 design project at the University of Queensland, 2019 semester 2 (team P03 Nano). The flight data recorded was attached to the UAV and launched with assisted takeoff. The accelerational data was to be sent to a base station used to calculate final flight distance ( a basic inertial measurement unit), and the flight time of the UAV displayed on LEDs in binary upon landing. The FDR was composed of a custom provided PCB with a Arduino Pro Mini. An MPU6050 accelerometer and RF24 transceiver were used to record and transmit acceleration.

## Assembled Flight Data Recorder
![FDR](https://raw.githubusercontent.com/Gabrblal/Nano/master/images/FDR.jpg)

## FDR Mounted in the Prototype UAV
![Mounted](https://raw.githubusercontent.com/Gabrblal/Nano/master/images/Mounted.jpg)

## FDR Electrical Schematic
![Schematic](https://raw.githubusercontent.com/Gabrblal/Nano/master/images/Electrical.png)
