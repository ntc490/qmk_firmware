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
 * Tapping configuration for home row mods
 * These settings handle bilateral combinations (two home row mods pressed quickly)
 */
#define TAPPING_TERM 200                    // Tapping term (ms) - matches KMK tap_time
#define IGNORE_MOD_TAP_INTERRUPT            // Prevent MT+MT from activating mods prematurely

/*
 * RGB LED configuration (Neopixel on GP23)
 * One LED on RIGHT side only for keeper status indication
 */
#define WS2812_PIO_USE_PIO1     // Use PIO1 (PIO0 is used for serial)
#define RGB_DI_PIN GP23         // Data pin for neopixel
#define RGBLED_NUM 1            // One LED on master (right) side only
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
