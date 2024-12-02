#include "pico/stdlib.h"
#include <stdio.h>

int main() {
    stdio_init_all();                    // Initialize USB serial
    sleep_ms(100);                       // Allow time for USB to initialize

    const uint led_pin = 25;             // Built-in LED on original Pico
    const uint led_pin_ext = 18;         // External LED for Pico W

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_init(led_pin_ext);
    gpio_set_dir(led_pin_ext, GPIO_OUT);

    bool stophandshake = false;
    int handshake_payload[] = {0x31, 0x32, 0x36, 0x0D, 0x20, 0x4D, 0x37, 0x36, 0x34, 0x20, 0x72, 0x65, 0x76, 0x20, 0x37, 0x36, 0x34, 0x30, 0x30, 0x32, 0x00};
    int assert_on_time = 35;
    int assert_off_time = 489;
    unsigned long handshake_timer = to_ms_since_boot(get_absolute_time());

    int bitRead(int bitVal, int bitPos) {
        int x = bitVal & (1 << bitPos);
        return x == 0 ? 0 : 1;
    }

    void assert_on() {
        gpio_put(led_pin, true);
        gpio_put(led_pin_ext, true);
        busy_wait_us(assert_on_time);
        gpio_put(led_pin, false);
        gpio_put(led_pin_ext, false);
        busy_wait_us(assert_off_time - assert_on_time);
    }

    void assert_off() {
        gpio_put(led_pin, false);
        gpio_put(led_pin_ext, false);
        busy_wait_us(assert_off_time);
    }

    while (true) {
        if ((to_ms_since_boot(get_absolute_time()) - handshake_timer) > 1000) {
            stophandshake = false;
        }
        int receivedChar = getchar_timeout_us(0);
        if (receivedChar != PICO_ERROR_TIMEOUT) {      // Handle no input case properly
            // printf("Received: 0x%02X\n", receivedChar);  // Debug print
            assert_on();
            for (int i = 0; i < 8; i++) {
                if (bitRead(receivedChar, i) == 1) {
                    assert_off();
                } else {
                    assert_on();
                }
            }
            if (receivedChar == 'U') {
                stophandshake = true;
                putchar(0x55);
                handshake_timer = to_ms_since_boot(get_absolute_time());
            } else if (receivedChar == 0x3F) {
                putchar(0x3F);
                if (stophandshake == false) {
                    for (int i = 0; i < 21; i++) {
                        putchar(handshake_payload[i]);
                    }
                }
            } else {
                putchar_raw(receivedChar);
                handshake_timer = to_ms_since_boot(get_absolute_time());
            }
        }
    }
}
