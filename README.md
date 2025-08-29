# DIY Datalink Adapter
Timex Datalink Notebook Adapter Emulator

<img src="DIY_Datalink_pico_software.jpg" width="476"><br>

- This is a modern microcontroller based replacement for the [Notebook Adapter kit][Adapter_Wiki] used by the [Timex Datalink][Watch_Wiki] watch, an adapter that eliminates the need for a CRT monitor to sync the watch.
- You can use either a new Windows 11 machine with Raspberry Pi Pico microcontrollers and [winevdm], or use the original hardware with the Arduino version.
- Use just as you would with the official Datalink Notebook Adapter, following in-app directions (choosing to sync with the Notebook adapter).<br>
- Note: You may need to shield the watch sensor from outside interference, like modern lightbulbs or monitors. <br>

## USB Raspberry Pi Pico version
<img src="DIY_Datalink_pico_watch.jpg" width="476"><br>
- Hold the reset button and plug in the microcontroller, then drag and drop the appropriate .uf2 file.
- If using Pico W or W2, it requires an external LED (GPIO pin 18 connected to 1k resistor on GND). Otherwise, the onboard LED will work.
- Install [winevdm] and then run setup for the Timex Datalink softare (2.1d), then run the program as usual making sure to choose the notebook adapter to sync.
- You can also pass through the device to a virtual machine running a legacy Windows version.
- A 3D printable case is available to help shield the sensor from interference.

## DB9 Serial Arduino Uno version
<img src="DIY_Datalink_Breadboard.png" width="340" height="577"><br>
Connect the Arduino Uno to RS232 TTL adapter using wires with Dupont connectors. Add an LED with 1k resistor. Power the Arduino Uno via USB. Connect null modem cable from the PC to the TTL adapter.<br>
-  Connect GND to GND, pin 9 to TX, pin 8 to RX (RX and TX are sometimes swapped), 5V to VCC (<b>Warning</b>: some TTL adapters may require 3V), pin 12 to the postive/longer leg on the LED, GND to a 1k resistor, the other end of resistor to the negative/short end on the red LED.
-  Connect USB type B to power source (does not use USB for data/communication)
-  Connect null modem cable between TTL adapter and PC
-  If you're using a virtual machine, pass through the COM port to your VM. It's better not to pass through the USB to serial device directly. This is verified to work in [VMWare Workstation][VMWare]. 

# Troubleshooting

### Error: Could not load 'VBRUN300.DLL' required by 'TIMEXDL', error=2
If you receive an error about VBRUN300.DLL missing, you may need to manually extract the file from the installer using something like [7-zip]. 
1. Right click on TDL21D.EXE and under 7-zip > click Open archive.
2. Right click on SETUP.EXE and click Open Inside.
3. Drag and drop VBRUN300.DLL into C:\DATALINK
4. Try again

If you only have SETUP.EXE (i.e. the floppy version), you can just right click on it, and under 7-zip click Open archive, then drag and drop VBRUN300.DLL into C:\DATALINK and try again. 

## 3D Printed Case 
-  [Shilbo][Shilbo] has [designed][3DPrint] and [printed][3DPrintPics] a case that not only holds the watch and Pico at the right distance, but also shields the light from interference from modern LED lighting!

# Special Thanks
- [Antti Huhtala][Antti]
- excsniper on the Arduino Discord
- Selzby and leandromarceddu on the unofficial Pico Discord for their hints and encouragement
- PhiLho on a Processing.org forum post for their bitwise info
- [Shilbo][Shilbo] for providing a 3D printable case for the Pico version
- [MuddledBox] for providing step-by-step instructions in VMware Workstation

# Disclaimer
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
[3DPrint]: <https://github.com/Shilbo/Datalink/>
[Shilbo]: <https://github.com/Shilbo>
[3DPrintPics]: <https://github.com/famiclone6502/DIY_Datalink_Adapter/issues/3#issuecomment-1541557457>
[MuddledBox]: <https://github.com/MuddledBox>
[winevdm]: <https://github.com/otya128/winevdm>
[7-zip]: <https://www.7-zip.org/download.html>
