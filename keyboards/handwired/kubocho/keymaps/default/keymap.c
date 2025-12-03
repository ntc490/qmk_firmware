// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Layer definitions
enum layers {
    _QWERTY,
    _NUMS,
    _FKEYS,
    _POWER
};

// Layer access keys
#define NUM_LYR MO(_NUMS)
#define FKEY_LYR MO(_FKEYS)
#define PWR_LYR MO(_POWER)

// Special key definitions
#define TAB_PWR LT(_POWER, KC_TAB)   // Tab normally, Power layer when held
#define NEXTWIN LGUI(KC_GRV)          // Next window (Cmd+Grave)

// Home row mods - Left hand (GASC order: GUI, ALT, SHIFT, CTRL)
#define GUI_A   LGUI_T(KC_A)
#define ALT_S   LALT_T(KC_S)
#define SHFT_D  LSFT_T(KC_D)
#define CTRL_F  LCTL_T(KC_F)

// Home row mods - Right hand (mirrored: CTRL, SHIFT, ALT, GUI)
#define CTRL_J  RCTL_T(KC_J)
#define SHFT_K  RSFT_T(KC_K)
#define ALT_L   LALT_T(KC_L)
#define GUI_SEMI RGUI_T(KC_SCLN)

// Home row mods for numbers layer - Right hand
#define CTRL_4  RCTL_T(KC_4)
#define SHFT_5  RSFT_T(KC_5)
#define ALT_6   LALT_T(KC_6)
#define GUI_QUOT RGUI_T(KC_QUOT)

// Home row mods for numbers layer - Left hand
#define CTRL_LB LCTL_T(KC_LCBR)  // Left curly brace with ctrl

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY Layer
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * | ESC |  Q  |  W  |  E  |  R  |  T  |     |  Y  |  U  |  I  |  O  |  P  |  \  |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |TAB^P| A^G | S^A | D^S | F^C |  G  |     |  H  | J^C | K^S | L^A | ;^G |  '  |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |LSHFT|  Z  |  X  |  C  |  V  |  B  |     |  N  |  M  |  ,  |  .  |  /  |FKEYS|
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     *                   |BKSP |LCTRL| NUMS|     | NUMS| ENT | SPC |
     *                   +-----+-----+-----+     +-----+-----+-----+
     *
     * Note: ^G=GUI, ^A=ALT, ^S=SHIFT, ^C=CTRL, ^P=POWER layer when held
     */
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        TAB_PWR, GUI_A,   ALT_S,   SHFT_D,  CTRL_F,  KC_G,        KC_H,    CTRL_J,  SHFT_K,  ALT_L,   GUI_SEMI,KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, FKEY_LYR,
                                   KC_BSPC, KC_LCTL, NUM_LYR,     NUM_LYR, KC_ENT,  KC_SPC
    ),

    /*
     * Numbers Layer
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |  `  | XXX |     |  (  |  )  |     |  =  |  7  |  8  |  9  |  [  |  ]  |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |CAPS |     |     |     | {^C |  }  |     |  -  | 4^C | 5^S | 6^A | '^G |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     | ESC |  [  |  ]  |     |  .  |  1  |  2  |  3  |     |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     *                   |     |     |     |     |     |     |  0  |
     *                   +-----+-----+-----+     +-----+-----+-----+
     *
     * Note: Home row mods poke through where _____ is used
     * XXX = KC.KEEP in KMK (not implemented)
     */
    [_NUMS] = LAYOUT_split_3x6_3(
        _______, KC_GRV,  KC_NO,   _______, KC_LPRN, KC_RPRN,     KC_EQL,  KC_7,    KC_8,    KC_9,    KC_LBRC, KC_RBRC,
        KC_CAPS, _______, _______, _______, CTRL_LB, KC_RCBR,     KC_MINS, CTRL_4,  SHFT_5,  ALT_6,   GUI_QUOT,_______,
        _______, _______, _______, KC_ESC,  KC_LBRC, KC_RBRC,     KC_DOT,  KC_1,    KC_2,    KC_3,    _______, _______,
                                   _______, _______, _______,     _______, _______, KC_0
    ),

    /*
     * F-Keys Layer
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     |     |     |     |     | F10 | F7  | F8  | F9  | F13 | XXX |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     |     |     |     |     | F11 | F4  | F5  | F6  | F14 | XXX |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     |     |     |     |     | F12 | F1  | F2  | F3  | F15 | XXX |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     *                   |     |     |     |     |     |     |     |
     *                   +-----+-----+-----+     +-----+-----+-----+
     */
    [_FKEYS] = LAYOUT_split_3x6_3(
        _______, _______, _______, _______, _______, _______,     KC_F10,  KC_F7,   KC_F8,   KC_F9,   KC_F13,  KC_NO,
        _______, _______, _______, _______, _______, _______,     KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_F14,  KC_NO,
        _______, _______, _______, _______, _______, _______,     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F15,  KC_NO,
                                   _______, _______, _______,     _______, _______, _______
    ),

    /*
     * Power-user Layer
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     |     |     |     |     |PGDN |PGUP |     |     |     |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     |     |     |     |     |LEFT |DOWN | UP  |RIGHT|     |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     |     |     |     |     |NXTW |     |     |     |     |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     *                   |     |     |     |     |     |     |     |
     *                   +-----+-----+-----+     +-----+-----+-----+
     *
     * Note: NXTW = Next Window (Cmd+Grave)
     */
    [_POWER] = LAYOUT_split_3x6_3(
        _______, _______, _______, _______, _______, _______,     KC_PGDN, KC_PGUP, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,     NEXTWIN, _______, _______, _______, _______, _______,
                                   _______, _______, _______,     _______, _______, _______
    )
};

// Optional: Add tap/hold configuration for better home row mod behavior
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Home row mods can have custom tapping terms
        case GUI_A:
        case ALT_S:
        case SHFT_D:
        case CTRL_F:
        case CTRL_J:
        case SHFT_K:
        case ALT_L:
        case GUI_SEMI:
            return 200;  // Match KMK's tap_time = 200
        default:
            return TAPPING_TERM;
    }
}

// Optional: Configure per-key mod-tap behavior
// This helps prevent accidental mod activation
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // For home row mods, don't activate hold on other key press
        // This matches KMK's prefer_hold = False behavior
        case GUI_A:
        case ALT_S:
        case SHFT_D:
        case CTRL_F:
        case CTRL_J:
        case SHFT_K:
        case ALT_L:
        case GUI_SEMI:
        case CTRL_4:
        case SHFT_5:
        case ALT_6:
        case GUI_QUOT:
        case CTRL_LB:
            return false;  // Don't hold on other key press (prefer_hold: False)
        default:
            return true;
    }
}
