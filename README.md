# DIY Datalink Adapter
<img src="DIY_Datalink_photo.png" width="476"><br>
This is a working Arduino Uno based replacement for the [Notebook Adapter kit][Adapter_Wiki] used by the [Timex Datalink][Watch_Wiki] watch.<br>
It's compatible with the original software (and PC hardware), and completely eliminates the need for syncing the watch with a CRT monitor.<br>
It even works with a virtual machine, but you still need some kind of USB to serial adapter (or a DB9 port on your PC).<br>

## Requirements
-  [Arduino Uno][ArduinoUno] (this should be compatible with other Arduino boards or similar microcontrollers, but it's only been tested on an Uno R3)
-  [Arduino software][ArduinoSoft] to upload the .ino file to an Arduino Uno
-  Software libraries for Arduino (see below)
-  [RS232 TTL hat][TTL_Hat] (I used Anmbest MAX3232 3.3V to 5V DB9 Male RS232 on Amazon)
-  [Red LED][LEDs] (with [1k resistor][ResistorKit] on GND between LED's ground wire)
-  4-6 short [wires with Dupont connectors][DupontWire] that are male on one end, female on the other
-  [Null modem cable][NullModem] to connect TTL adapter to PC
-  Windows 9x PC or virtual machine with serial port and Timex Datalink software installed (verified with 2.1d). Windows 3.x or even [Wine][Wine] may also work, but are untested.
-  [Timex Datalink watch][Watch_Wiki] (tested with Datalink 150)
-  <b>Optional</b>: [USB to serial adapter][USB_Serial] for use with a virtual machine. It doesn't have to involve a DB9 connector, you can use a [USB to TTL][TTL_Direct] adapter directly without TTL hat. But you'll need additional [Dupont wires][DupontWire] with male on both ends.

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
-  If you're using a virtual machine, pass through the COM port to your VM. It's better not to pass through the USB to serial device directly. This is verified to work in [VMWare Workstation][VMWare]. 

## How to use
Use as you would the official Datalink Notebook Adapter, following in-app directions.<br><br>
You may need to shield the watch sensor from interference, like modern LED lightbulbs or even monitors. <br><br>
<b>Update</b>: You no longer need to reset the board after each usage. It should behave now just like the official adapter, but it's possible you may need to adjust the the inactivity timeout if it keeps failing after a successful first use.

## To-Do List

The project as-is primarily works as a direct replacement for the original hardware, but a compact board that has a built-in red LED and uses just one USB cable would be ideal. <br>
-  Right now, directly using the Arduino USB for serial communication won't work. The official software does not parse the responses from the Arduino's hardware serial. It only responds to the software serial library's write command, not even serial print. For modern usage, eliminating the TTL adapter or DB9 would be more convenient and cheaper to build, but I have yet to get this to work. 
-  Once hardware serial works, I would also like to test this on a smaller board that has a built-in red LED for even more convenience. 

## Special Thanks
- [Antti Huhtala][Antti]
- excsniper on the Arduino Discord 🦆

## Disclaimer
 I am not a professional programmer. This is my first Github project. Please be kind. 😬<br><br>
 Timex, Datalink, and DATA LINK are the registered trademarks of Timex Corporation.  This project is not associated with or sponsored by Timex.
 
[Antti]: <https://github.com/ahhuhtal>
[Watch_Wiki]: <https://en.wikipedia.org/wiki/Timex_Datalink>
[Adapter_Wiki]: <https://en.wikipedia.org/wiki/Timex_Datalink#Notebook_adapter>
[ArduinoUno]: <https://store-usa.arduino.cc/products/arduino-uno-rev3/>
[ArduinoSoft]: <https://www.arduino.cc/en/software/>
[LEDs]: <https://smile.amazon.com/eBoot-Pieces-Emitting-Diodes-Assorted/dp/B06XPV4CSH>
[ResistorKit]: <https://smile.amazon.com/Elegoo-Values-Resistor-Assortment-Compliant/dp/B072BL2VX1/>
[DupontWire]: <https://smile.amazon.com/SIM-NAT-Breadboard-Arduino-Raspberry/dp/B07RX78T9L/>
[NullModem]: <https://smile.amazon.com/StarTech-com-10-Feet-RS232-Serial-SCNM9FF/dp/B00006B8BJ>
[USB_Serial]: <https://smile.amazon.com/dp/B0753HBT12>
[TTL_Hat]: <https://smile.amazon.com/Anmbest-Converter-Connector-Raspberry-Microcontrollers/dp/B07LBDZ9WG/>
[TTL_Direct]: <https://www.sparkfun.com/products/17831>
[Wine]: <https://www.winehq.org/>
[VMWare]: <https://www.vmware.com/products/workstation-player/workstation-player-evaluation.html>
