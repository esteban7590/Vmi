# Vmi

Platformio files. 

Arduino code for NodeMCU V3 or Arduino uno.

Sets time using compilation time (error +/- 30 s), then sets an alarm at the specified time. The microcontroller is turned off while 
the alarm hasnt been triggered (using a transistor, relay and a 5V Output battery). When triggered, microcontroller turns on and calculates
the amount of pallets (given height of the pallet, height to floor and tolerance) using an ultrasonic sensor and stadistic calculations.
Then the value is sent to Ubidots IOT platform using a Quectel M95 shield. Before shutting down again a new alarm is set.
