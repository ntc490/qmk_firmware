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
#define SERIAL_PIO_USE_PIO0         // Use PIO0 peripheral

/*
 * Tapping configuration for home row mods
 * These settings handle bilateral combinations (two home row mods pressed quickly)
 */
#define TAPPING_TERM 200                    // Tapping term (ms) - matches KMK tap_time
#define IGNORE_MOD_TAP_INTERRUPT            // Prevent MT+MT from activating mods prematurely

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
