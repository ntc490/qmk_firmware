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
#define SERIAL_USART_FULL_DUPLEX    // Enable full duplex operation
#define SERIAL_USART_TX_PIN GP1     // UART TX pin (matches KMK data_pin)
#define SERIAL_USART_RX_PIN GP0     // UART RX pin (matches KMK data_pin2)

/*
 * Serial driver configuration - RP2040 uses PIO-based serial
 * The "vendor" driver in info.json enables the RP2040 PIO implementation
 */
#define SERIAL_USART_DRIVER PIO     // Use PIO for serial communication
#define SERIAL_PIO_USE_PIO0         // Use PIO0 peripheral
#define SERIAL_USART_TIMEOUT 100    // USART driver timeout (ms)
#define SERIAL_USART_SPEED 38400    // Baud rate for serial communication

/*
 * For RP2040 PIO-based serial, we may need to specify which PIO state machine to use
 * Uncomment if needed:
 * #define SERIAL_USART_TX_PAL_MODE 0
 */

/* USB polling interval */
#define USB_POLLING_INTERVAL_MS 1

/* Debounce reduces chatter (unintended double-presses) */
#define DEBOUNCE 5

/* Matrix configuration - handled by direct pins in info.json */
#define MATRIX_ROWS 8  // 4 rows per side
#define MATRIX_COLS 6  // 6 columns per side

/*
 * Tapping configuration for home row mods
 * These settings improve the behavior of mod-tap keys
 */
#define TAPPING_TERM 200                    // Default tapping term (ms) - matches KMK tap_time
#define PERMISSIVE_HOLD                     // Makes tap/hold more predictable
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY     // Allow per-key hold behavior (defined in keymap.c)
#define TAPPING_TERM_PER_KEY                // Allow per-key tapping term (defined in keymap.c)

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
