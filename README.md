# DIY Datalink Adapter
<img src="DIY_Datalink_photo.png" width="476"><br>
This is a working Arduino Uno based replacement for the Notebook Adapter kit.<br>
It's compatible with the original software (and PC hardware), while eliminating the need for a CRT monitor.<br>
It even works with a virtual machine, but you still need a USB to serial adapter (or a DB9 port on your PC). Right now, directly using the Arduino USB for serial communication won't work.<br>

## Requirements
-  Arduino Uno (this should be compatible with other Arduino boards or similar microcontrollers, but it's only been tested on an Uno R3)
-  Arduino software to upload the .ino file to an Arduino Uno
-  Software libraries for Arduino (see below)
-  RS232 TTL hat (I used Anmbest MAX3232 3.3V to 5V DB9 Male RS232 on Amazon)
-  Red LED (with 1k resistor on GND between LED's ground wire)
-  4 short wires with Dupont connectors that are male on one end, female on the other
-  Null modem cable to connect TTL adapter to PC
-  Windows 9x PC or virtual machine with serial port and Timex Datalink software installed (verified with 2.1d). Win3.x may also work.
-  Timex Datalink watch (tested with Datalink 150)
-  <b>Optional</b>: USB to serial adapter for use with a virtual machine.

## Libraries Used
This currently requires three Arduino libraries, add them with the Library Manager in the Arduino software.
-  AltSoftSerial (tested with version 1.4.0)
-  DigitalIO (tested with version 1.0.0)
-  SafeString (for millisDelay, tested with version 4.1.15)

## Connecting it all
Connect the Arduino Uno to RS232 TTL adapter using wires with Dupont connectors. Add an LED with 1k resistor. Power the Arduino Uno via USB. Connect null modem cable from the PC to the TTL adapter.<br><br>
<img src="DIY_Datalink_Breadboard.png" width="340" height="577"><br>
-  Connect pin 9 on the Arduino Uno to TX on the TTL adapter
-  Connect pin 8 on the Arduino Uno to RX on the TTL adapter
-  Connect 5V on the Arduino Uno to VCC on the TTL adapter (<b>Warning</b>: some TTL adapters may accept or even require connecting 3V instead)
-  Connect any GND on the Arduino Uno to GND on to serialthe TTL  directlyadapter
-  Connect pin 12 on the Arduino, Uno to the postive/longer leg on the red LED
-  Connect any GND on the Arduino Uno to a 1k resistor and other end of resistor to the negative/short end on the red LED (you can just twist these together in a pinch)
-  Connect USB type B to power source (does not currently use USB for data/communication)
-  Connect null modem cable between TTL adapter and PC
-  If you're using a virtual machine, pass through the COM port to your VM. It's better not to pass through the USB to serial device directly. This is verified to work in VMWare Workstation. 

## How to use
Use as you would the official Datalink Notebook Adapter, following in-app directions.<br><br>
<b>Update</b>: You no longer need to reset the board after each usage.

## Special Thanks
- [Antti Huhtala][Antti]
- excsniper on the Arduino Discord 🦆

## Disclaimer
 Timex, Datalink, and DATA LINK are the registered trademarks of Timex Corporation.  This project is not associated with or sponsored by Timex.
 
[Antti]: <https://github.com/ahhuhtal>
