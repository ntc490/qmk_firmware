#include "quantum.h"
#include "keyboard.ioh"

void all_led_off(void)
{
    scroll_lock_led_off();
    keypad_led_off();
    num_lock_led_off();
    caps_lock_led_off();
}

void all_led_on(void)
{
    scroll_lock_led_on();
    keypad_led_on();
    num_lock_led_on();
    caps_lock_led_on();
}

void blink_all_leds(void)
{
    all_led_on();
    _delay_ms(500);

    all_led_off();
    _delay_ms(100);

    caps_lock_led_on();
    _delay_ms(100);

    num_lock_led_on();
    _delay_ms(100);

    scroll_lock_led_on();
    _delay_ms(100);

    keypad_led_on();
    _delay_ms(100);

    // back

    scroll_lock_led_on();
    _delay_ms(100);

    num_lock_led_on();
    _delay_ms(100);

    caps_lock_led_on();
    _delay_ms(100);

    all_led_off();
}

void matrix_init_kb(void) {
    blink_all_leds();
    matrix_init_user();
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & 1 << USB_LED_NUM_LOCK) {
        num_lock_led_on();
    } else {
        num_lock_led_off();
    }
    if (usb_led & 1 << USB_LED_CAPS_LOCK) {
        caps_lock_led_on();
    } else {
        caps_lock_led_off();
    }
    if (usb_led & 1 << USB_LED_SCROLL_LOCK) {
        scroll_lock_led_on();
    } else {
        scroll_lock_led_off();
    }

    led_set_user(usb_led);
}
