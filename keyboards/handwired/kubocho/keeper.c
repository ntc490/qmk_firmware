// Copyright 2026 Nathan Crapo
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Keeper (keep-awake) mode, shared by the Kubocho keymaps. See keeper.h.

#include "keeper.h"

#define PIR_PIN GP29          // PIR sensor on GPIO29
#define KEEPER_TIMEOUT 60000  // 60 seconds in milliseconds

enum keeper_modes {
    KEEPER_OFF,
    KEEPER_MANUAL,
    KEEPER_PIR
};

static uint8_t  keeper_mode        = KEEPER_OFF;
static uint32_t last_activity_time = 0;

// Override breathing intervals - lower = faster, higher = slower
// Values are in ~65ms ticks. 10 = ~650ms per animation step.
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {10, 10, 10, 10};

bool keeper_process_record(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keeper_mode == KEEPER_MANUAL) {
        last_activity_time = timer_read32();
    }

    if (keycode != KEEPER_TOGG) {
        return true;
    }

    if (record->event.pressed) {
        keeper_mode = (keeper_mode + 1) % 3;

        switch (keeper_mode) {
            case KEEPER_OFF:
                uprintf("Keeper: OFF\n");
                rgblight_disable();
                break;

            case KEEPER_MANUAL:
                uprintf("Keeper: MANUAL\n");
                last_activity_time = timer_read32();
                rgblight_enable();
                rgblight_sethsv(170, 255, 128);  // Blue
                rgblight_mode(RGBLIGHT_MODE_BREATHING);
                break;

            case KEEPER_PIR:
                uprintf("Keeper: PIR mode - watching GP29\n");
                rgblight_enable();
                rgblight_sethsv(0, 255, 128);  // Red
                rgblight_mode(RGBLIGHT_MODE_BREATHING);
                break;
        }
    }
    return false;  // Don't process this key further
}

// Check timer and send shift if idle too long; also check the PIR sensor
void keeper_task(void) {
    if (keeper_mode == KEEPER_MANUAL) {
        if (timer_elapsed32(last_activity_time) > KEEPER_TIMEOUT) {
            tap_code(KC_LSFT);
            last_activity_time = timer_read32();
        }
    } else if (keeper_mode == KEEPER_PIR) {
        static uint32_t pir_window_start = 0;
        static bool motion_detected_in_window = false;

        // Debug: print PIR pin state every 5 seconds
        static uint32_t last_debug_time = 0;
        if (timer_elapsed32(last_debug_time) > 5000) {
            bool pin_state = gpio_read_pin(PIR_PIN);
            uprintf("PIR pin state: %d\n", pin_state);
            last_debug_time = timer_read32();
        }

        // Initialize window timer if not started
        if (pir_window_start == 0) {
            pir_window_start = timer_read32();
            motion_detected_in_window = false;
        }

        // Check for motion during this window
        if (gpio_read_pin(PIR_PIN)) {
            if (!motion_detected_in_window) {
                uprintf("PIR: Motion detected in window!\n");
                motion_detected_in_window = true;
            }
        }

        // Check if window has elapsed
        if (timer_elapsed32(pir_window_start) > KEEPER_TIMEOUT) {
            if (motion_detected_in_window) {
                uprintf("PIR: Sending tickle (motion was detected)\n");
                tap_code(KC_LSFT);
            } else {
                uprintf("PIR: No motion in window, skipping tickle\n");
            }
            // Reset window
            pir_window_start = timer_read32();
            motion_detected_in_window = false;
        }
    }
}

void keeper_init(void) {
    // Configure PIR sensor pin as input (no pull resistor - PIR has its own pull)
    gpio_set_pin_input(PIR_PIN);
    uprintf("PIR sensor initialized on GP29\n");

    // Initialize RGB to off (will turn on when keeper is enabled)
    rgblight_disable();
}
