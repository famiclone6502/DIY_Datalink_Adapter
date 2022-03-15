// A working Arduino Uno based replacement for the Notebook Adapter kit
// to use with the original software
// may require RS232 TTL hat, 1k resistor, and LED. 

// Note: Need to reset board after each usage to reset handshake. Need to fix this!

// Update: It works!! Sync with watch successful!
// Software finishes synchronization without error
// Watch is responding thanks to Antti's comment on the 9th bit period!
// Also thanks for the correction regarding initial bit period!
// After that, timing needed adjusting, too.

// Special thanks to Antti Huhtala and excsniper for their troubleshooting help!

// AltSoftSerial always uses these pins:
//
// Board          Transmit  Receive   PWM Unusable
// -----          --------  -------   ------------
// Arduino Uno        9         8         10

#include <DigitalIO.h> // uncomment to test digital IO for LED
#include <AltSoftSerial.h> // trying more time sensitive serial library

AltSoftSerial mySerial;
DigitalPin<12> pinled; // digital LED testing

boolean stophandshake = false; // after initial handshake, don't repeat string during actual sync (requires board reset every sync attempt)

void setup()
{
  mySerial.begin(9600);
  pinled.mode(OUTPUT); // switching back to digital, using a 1k resistor to control brightness
}

void loop()
{
  int receivedChar = mySerial.read();
  if (receivedChar != -1)
  {
    // for each bit in the byte, blink accordingly according to Antti Huhtala's blogger

    // Antti points out it has 9 bit periods, with the first always being 0 (1 means stay off)
        pinled.write(HIGH);
        delayMicroseconds(35);
        pinled.write(LOW);
        delayMicroseconds(460);
    for (int i = 0; i < 8; i++) {
      if (bitRead(receivedChar, i) == 1)
      {
        //assert off 490us
        pinled.write(LOW);
        delayMicroseconds(490);
      }
      else
      {
        //assert on 30us, 460us off
        pinled.write(HIGH);
        delayMicroseconds(35);
        pinled.write(LOW);
        delayMicroseconds(460);
      }
    }

    if (receivedChar == 'U') // moved this up to see if it would help timing
    {
      stophandshake = true; // hm, how do I reset this at the end of transmission?
      mySerial.write('U');
    }
    else if (receivedChar == 'x')
    {
      //mySerial.print('x'); // doesn't work! why?!
      mySerial.write('x');
    }
    else if (receivedChar == 0x3F) // "?"
    {
      mySerial.write(0x3F);   // ?

      if (stophandshake == false) { // send only the following during initial handshake
        // why? it really picky about how it was sent.
        // just happy it worked. I can revisit this later to simplify.
        mySerial.write(0x31);   // 1
        mySerial.write(0x32);   // 2
        mySerial.write(0x36);   // 6
        mySerial.write(0x0D);   // (carriage return)
        mySerial.write(0x20);   // (space)
        mySerial.write(0x4D);   // M
        mySerial.write(0x37);   // 7
        mySerial.write(0x36);   // 6
        mySerial.write(0x34);   // 4
        mySerial.write(0x20);   // (space)
        mySerial.write(0x72);   // r
        mySerial.write(0x65);   // e
        mySerial.write(0x76);   // v
        mySerial.write(0x20);   // (space)
        mySerial.write(0x37);   // 7
        mySerial.write(0x36);   // 6
        mySerial.write(0x34);   // 4
        mySerial.write(0x30);   // 0
        mySerial.write(0x30);   // 0
        mySerial.write(0x32);   // 2
        mySerial.write((byte)0);// (null)
      }
    }
    else {
      mySerial.write(receivedChar); // repeat everything back to make software happy
    }
  }
}