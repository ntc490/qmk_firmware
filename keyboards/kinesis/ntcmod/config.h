#ifndef NTCMOD_CONFIG_H
#define NTCMOD_CONFIG_H

#include "../config.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001

/* key matrix size */
#define MATRIX_ROWS 16
#define MATRIX_COLS  8

#define MATRIX_ROW_PINS { B6, B5, B4, B3, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN }

#define MATRIX_COL_PINS { F0, F1, F2, F3, F4, F5, F6, F7 }

#define DIODE_DIRECTION COL2ROW

#endif
