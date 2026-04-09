// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Simple keymap for clearing EEPROM
// All keys are KC_NO except index finger keys which are EE_CLR
// Press either F or J key to clear EEPROM

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * EEPROM Clear Layer
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * | NO  | NO  | NO  | NO  | NO  | NO  |     | NO  | NO  | NO  | NO  | NO  | NO  |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * | NO  | NO  | NO  | NO  |EECLR| NO  |     | NO  |EECLR| NO  | NO  | NO  | NO  |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * | NO  | NO  | NO  | NO  | NO  | NO  |     | NO  | NO  | NO  | NO  | NO  | NO  |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     *                   | NO  | NO  | NO  |     | NO  | NO  | NO  |
     *                   +-----+-----+-----+     +-----+-----+-----+
     *
     * Press F or J to clear EEPROM, then reflash with left/right firmware
     */
    [0] = LAYOUT_split_3x6_3(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   EE_CLR,  KC_NO,       KC_NO,   EE_CLR,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO
    )
};
