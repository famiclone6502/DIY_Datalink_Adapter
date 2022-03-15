# DIY Datalink Adapter
Arduino Uno based Notebook Adapter compatible with original Timex Datalink software

## Required
-  Arduino Uno
-  Arduino software to upload to an Arduino Uno
-  Software libraries for Arduino (see below)
-  RS232 TTL hat (I used Anmbest MAX3232 3.3V to 5V DB9 Male RS232 on Amazon)
-  LED (with 1k resistor on GND between LED's ground wire)
-  4 short wires with Dupont connectors that are male on one end, female on the other
-  Null modem cable to connect TTL adapter to PC
-  Windows 9x PC or virtual machine with serial port and Timex Datalink software installed (verified with 2.1d)
-  Timex Datalink watch (tested with Datalink 150)

## Libraries Used
This currently requires two Arduino libraries, add them with the Library Manager in the Arduino software.
-  AltSoftSerial (tested with version 1.4.0)
-  DigitalIO (tested with version 1.0.0)

## Connecting it all
Connect the Arduino Uno to RS232 TTL adapter using wires with Dupont connectors.
-  Connect pin 9 on the Arduino Uno to TX on the TTL adapter
-  Connect pin 8 on the Arduino Uno to RX on the TTL adapter
-  Connect 5V on the Arduino Uno to VCC on the TTL adapter
-  Connect any GND on the Arduino Uno to GND on the TTL adapter
-  Connect USB type B to power source (does not currently use USB for data/communication)
-  Connect Null modem cable between TTL adapter and PC

## How to use
Right now you need to reset the board after each usage (including watch test). Just use the reset button on the board, no need to unplug the power. Otherwise, use as you would the official Datalink Notebook Adapter, following in-app directions. 

## Special Thanks
- [Antti Huhtala][Antti]
- excsniper

## Disclaimer
 Timex, Datalink, and DATA LINK are the registered trademarks of Timex Corporation.  This project is not associated with or sponsored by Timex.
 
[Antti]: <https://github.com/ahhuhtal>
