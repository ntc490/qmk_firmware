// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Split keyboard configuration */
// The KMK version uses volume label detection (L/R suffix) for handedness
// QMK options:
//   1. Use EE_HANDS and flash different EEPROM to each side (recommended)
//   2. Use SPLIT_HAND_PIN with a pin tied high/low differently on each side
//   3. Use MASTER_RIGHT (uncomment line below to hardcode right as master)
// #define MASTER_RIGHT
#define EE_HANDS  // Use EEPROM to store handedness

/* Serial/UART configuration for split communication */
// RP2040 uses PIO-based serial driver
// Full-duplex mode: GP0 (TX) and GP1 (RX) on both halves
// Cable has crossover on slave side: Master Pin1→Slave Pin1, Master Pin4→Slave Pin4
// This allows both KMK and QMK to work with the same hardware
#define SERIAL_PIO_USE_PIO0         // Use PIO0 peripheral
#define SERIAL_USART_FULL_DUPLEX    // Enable full-duplex communication
#define SERIAL_USART_TX_PIN GP0     // Transmit on GP0
#define SERIAL_USART_RX_PIN GP1     // Receive on GP1

/*
 * Tapping configuration for home row mods (see docs/tap_hold.md)
 */
#define TAPPING_TERM 220     // Hold this long and it's always a mod
#define PERMISSIVE_HOLD      // Mod + another key pressed AND released inside the term -> mod
#define CHORDAL_HOLD         // ...but only if that other key is on the opposite hand
#define FLOW_TAP_TERM 150    // Mod-tap pressed <150ms after a letter is always a tap (fast typing)
// #define QUICK_TAP_TERM 120   // Tap-then-hold within 120ms auto-repeats the letter; slower -> mod
// #define SPECULATIVE_HOLD     // Send Shift/Ctrl immediately on keydown (snappier Shift+click)

/*
 * Caps Word: hold both Shift home row mods (D + K) to capitalize until the end
 * of the word. Needs exactly Left Shift + Right Shift, so K is RSFT_T.
 */
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

/*
 * RGB LED configuration (Neopixel on GP23)
 * One LED on RIGHT side only for keeper status indication
 */
#define WS2812_PIO_USE_PIO1     // Use PIO1 (PIO0 is used for serial)
#define WS2812_DI_PIN GP23      // Data pin for neopixel
#define RGBLIGHT_LED_COUNT 1    // One LED on master (right) side only
// Note: RGBLED_SPLIT and RGBLIGHT_SPLIT are NOT defined - LED only on master

// Enable breathing effect for keeper indicator
#define RGBLIGHT_EFFECT_BREATHING

/*
 * Feature disable options
 * These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
