#include <Arduino.h>

// Built-in LED on Pico (GPIO 25) and an external LED (GPIO 18).
// The Arduino framework automatically handles pin initialization.
const uint8_t led_pin = 25;
const uint8_t led_pin_ext = 18;

// Assertion (on) and de-assertion (off) times in microseconds (µs).
const int assert_on_time_us = 35;
const int assert_off_time_us = 489;

bool stophandshake = false;
int handshake_payload[] = {
    0x31, 0x32, 0x36, 0x0D, 0x20, 0x4D, 0x37, 0x36, 0x34, 0x20, 0x72, 0x65, 0x76, 0x20, 0x37, 0x36, 0x34, 0x30, 0x30, 0x32, 0x00
};

unsigned long handshake_timer = 0;

// This function has been renamed to avoid a conflict with the built-in Arduino bitRead() macro.
int customBitRead(int bitVal, int bitPos) {
    return (bitVal >> bitPos) & 1;
}

// Turns the LED on for assert-on, then off for the remainder of the assert-off cycle.
void assert_on() {
    digitalWrite(led_pin, HIGH);
    digitalWrite(led_pin_ext, HIGH);
    delayMicroseconds(assert_on_time_us);
    digitalWrite(led_pin, LOW);
    digitalWrite(led_pin_ext, LOW);
    delayMicroseconds(assert_off_time_us - assert_on_time_us);
}

// Turns the LED off for the entire assert-off cycle.
void assert_off() {
    digitalWrite(led_pin, LOW);
    digitalWrite(led_pin_ext, LOW);
    delayMicroseconds(assert_off_time_us);
}

// The setup() function runs once when the board is powered on or reset.
void setup() {
    Serial.begin(115200); // Initialize USB serial communication
    while (!Serial) {
        // Wait for the serial port to be ready on some boards (e.g., Leonardo, Due).
    }

    pinMode(led_pin, OUTPUT);
    pinMode(led_pin_ext, OUTPUT);

    handshake_timer = millis();
}

// The loop() function runs repeatedly after setup().
void loop() {
    if ((millis() - handshake_timer) > 1000) {
        stophandshake = false;
    }

    if (Serial.available()) {
        int receivedChar = Serial.read();

        assert_on();
        for (int i = 0; i < 8; i++) {
            if (customBitRead(receivedChar, i) == 1) {
                assert_off();
            } else {
                assert_on();
            }
        }
        
        if (receivedChar == 'U') {
            stophandshake = true;
            // Delays are needed before responding to fix sync errors
            delay(2); 
            Serial.write(0x55);
            handshake_timer = millis();
        } else if (receivedChar == 0x3F) {
        // I suspect this one caused timing issues with inconsistent delays
            delay(2); 
            Serial.write(0x3F);
            if (stophandshake == false) {
                for (int i = 0; i < 21; i++) {
                    Serial.write(handshake_payload[i]);
                }
            }
        } else {
            // Again, new delay. Increase if necessary.
            delay(2); 
            Serial.write(receivedChar);
            handshake_timer = millis();
        }
    }
}

