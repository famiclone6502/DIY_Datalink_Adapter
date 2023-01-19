#include "pico/stdlib.h"
#include <stdio.h>

int main()  {
    stdio_init_all();                     // Initialize usb serial
    const uint led_pin = 25;              // Original Pico users: Built in led on Pico (original model)
    const uint led_pin_ext = 18;          // For simultaneous external LED (with 1k resistor between GND) mainly for Pico W
    gpio_init(led_pin);                   // Initialize LED pin on original Pico (does not work on Pico W)
    gpio_set_dir(led_pin, GPIO_OUT);      // Additional initialization for LED pin on original Pico
    gpio_init(led_pin_ext);               // Initialize external LED pin
    gpio_set_dir(led_pin_ext, GPIO_OUT);  // Additional initialization for external LED pin

    bool stophandshake = false;           // Handshake will only occur on initial boot and after serial inactivity. 
    int handshake_payload[] = {0x31, 0x32, 0x36, 0x0D, 0x20, 0x4D, 0x37, 0x36, 0x34, 0x20, 0x72, 0x65, 0x76, 0x20, 0x37, 0x36, 0x34, 0x30, 0x30, 0x32, 0x00}; // Changed null from (byte)0
    int assert_on_time = 35;              // Adjust timing in microseconds if you're not getting a sync signal or it fails transmission.
    int assert_off_time = 489;            // Adjusted according to scope measurements.
    unsigned long handshake_timer = to_ms_since_boot(get_absolute_time()); // Start timer variable.

    int bitRead(int bitVal, int bitPos) { // bitRead function similar to Arduino's
        int x = bitVal & (1 << bitPos);
        return x == 0 ? 0 : 1;
    }

    void assert_on() {
        gpio_put(led_pin, true);          // Turn on LED on original Pico
        gpio_put(led_pin_ext, true);      // Turn on external LED
        busy_wait_us(assert_on_time);     // Short assertion of LED on.
        gpio_put(led_pin, false);         // Turn off LED on original Pico
        gpio_put(led_pin_ext, false);     // Turn off external LED
        busy_wait_us(assert_off_time - assert_on_time); // Stay off for remainder of bit period.
    }

    void assert_off() {
        gpio_put(led_pin, false);
        gpio_put(led_pin_ext, false);
        busy_wait_us(assert_off_time);    // Stay off entire bit period.
    }

    while(true) { // Main loop
        if ((to_ms_since_boot(get_absolute_time())-handshake_timer)>1000) {
            stophandshake = false;        // Handshake needed again after inactivity.
        }
        int receivedChar = getchar_timeout_us(0);
        if (receivedChar != -1) {
            assert_on();                  // There are 9 bit periods, with the initial period always treated as a 0.
            for (int i = 0; i < 8; i++) { // The remaining 8 bit periods follow the bits in the byte received.
                if (bitRead(receivedChar, i) == 1) {
                    assert_off();         // For every 1 received: assert LED off for entire bit period.
                }
                else
                {
                    assert_on();          // For any 0 recieved: assert a short LED on, and then off during this bit period.
                }
            }
            if (receivedChar == 'U') {    // Handshake requirement is over whenever U received.
                stophandshake = true; 
                putchar(0x55);            //printf("U"); // Echo 'U'.
                handshake_timer = to_ms_since_boot(get_absolute_time()); // Keep resetting inactivity timer after test pattern activity.
            }
            else if (receivedChar == 0x3F) {        // If ASCII '?' received...
                putchar(0x3F);  //printf("?");      // Always at least echo '?'...
                if (stophandshake == false) {       // But send only the following during initial handshake...
                    for (int i = 0; i < 21; i++) {  // Send one at a time, because the software is picky about how it's sent.
                    putchar(handshake_payload[i]);  // Reply with "126\r M764 rev 764002(null)" during handshake.
                    }
                }
            }
            else {
                putchar_raw(receivedChar);          // Always echo any other characters received verbatim (use raw for Pico), or transmission fails.
                handshake_timer = to_ms_since_boot(get_absolute_time()); // Keep resetting inactivity timer after sync mode activity.
            }
    }
    }
}



