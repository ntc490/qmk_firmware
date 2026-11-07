// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Layer definitions
enum layers {
    _BASE,
    _NUMS,
    _FKEYS,
    _POWER
};

// Keeper (keep-awake) mode: KEEPER_TOGG keycode, PIR sensor, LED. See ../../keeper.h
// Custom keycodes for this keymap would start at KEEPER_SAFE_RANGE.
#include "keeper.h"

// Layer access keys
#define NUM_LYR MO(_NUMS)
#define FKEY_LYR MO(_FKEYS)
#define NUM_G   LT(_NUMS, KC_G)    // G tap, NUMS hold (use with right-hand numpad)
#define NUM_H   LT(_NUMS, KC_H)    // H tap, NUMS hold (use with left-hand symbols)
#define FKEY_T  LT(_FKEYS, KC_T)   // T tap, FKEYS hold (F-keys are on the right hand)
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
#define CTRL_J  LCTL_T(KC_J)
#define SHFT_K  RSFT_T(KC_K)   // Right Shift so D+K = both shifts -> Caps Word
#define ALT_L   LALT_T(KC_L)
#define GUI_SEMI LGUI_T(KC_SCLN)

// Home row mods for numbers layer - Right hand
#define CTRL_4  LCTL_T(KC_4)
#define SHFT_5  RSFT_T(KC_5)
#define ALT_6   LALT_T(KC_6)
#define GUI_QUOT LGUI_T(KC_QUOT)

// Ctrl on hold, { on tap. Mod-taps can't take shifted keycodes like KC_LCBR,
// so this is LCTL_T(KC_LBRC) with the tap swapped to { in process_record_user().
#define CTRL_LCBR LCTL_T(KC_LBRC)

// Combos (experimental): press both keys together
//   N + M -> Space
//   V + B -> Space
const uint16_t PROGMEM combo_nm[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM combo_vb[] = {KC_V, KC_B, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_nm, KC_SPC),
    COMBO(combo_vb, KC_SPC),
};

// Key overrides: Shift + Backspace -> Delete
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &delete_key_override,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer (QWERTY)
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * | ESC |  Q  |  W  |  E  |  R  | T^F |     |  Y  |  U  |  I  |  O  |  P  |  \  |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |TAB^P| A^G | S^A | D^S | F^C | G^N |     | H^N | J^C | K^S | L^A | ;^G |  '  |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |LSHFT|  Z  |  X  |  C  |  V  |  B  |     |  N  |  M  |  ,  |  .  |  /  |FKEYS|
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     *                   |BKSP |LCTRL| NUMS|     | REP | ENT | SPC |
     *                   +-----+-----+-----+     +-----+-----+-----+
     *
     * Note: ^G=GUI, ^A=ALT, ^S=SHIFT, ^C=CTRL, ^P=POWER, ^N=NUMS, ^F=FKEYS layer when held
     * REP = Repeat Key: repeats the last key pressed (with its mods)
     */
    [_BASE] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    FKEY_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        TAB_PWR, GUI_A,   ALT_S,   SHFT_D,  CTRL_F,  NUM_G,       NUM_H,   CTRL_J,  SHFT_K,  ALT_L,   GUI_SEMI,KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, FKEY_LYR,
                                   KC_BSPC, KC_LCTL, NUM_LYR,     QK_REP,  KC_ENT,  KC_SPC
    ),

    /*
     * Numbers Layer
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |  `  |     |     |  (  |  )  |     |  =  |  7  |  8  |  9  |  \  |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     |     | {^C |  }  |     |  -  | 4^C | 5^S | 6^A | '^G |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     | ESC |  [  |  ]  |     |  .  |  1  |  2  |  3  |LOCK |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     *                   |     |     |     |     |     |     |  0  |
     *                   +-----+-----+-----+     +-----+-----+-----+
     *
     * Note: Home row mods poke through where _____ is used
     * LOCK = Layer Lock: keep this layer on after releasing the layer key (tap again to unlock)
     */
    [_NUMS] = LAYOUT_split_3x6_3(
        _______, KC_GRV,  _______, _______, KC_LPRN, KC_RPRN,     KC_EQL,  KC_7,    KC_8,    KC_9,    KC_BSLS, _______,
        _______, _______, _______, _______, CTRL_LCBR, KC_RCBR,   KC_MINS, CTRL_4,  SHFT_5,  ALT_6,   GUI_QUOT,_______,
        _______, _______, _______, KC_ESC,  KC_LBRC, KC_RBRC,     KC_DOT,  KC_1,    KC_2,    KC_3,    QK_LLCK, _______,
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
        _______, _______, _______, _______, _______, _______,     KC_F10,  KC_F7,   KC_F8,   KC_F9,   KC_F13,  XXXXXXX,
        _______, _______, _______, _______, _______, _______,     KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_F14,  XXXXXXX,
        _______, _______, _______, _______, _______, _______,     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F15,  XXXXXXX,
                                   _______, _______, _______,     _______, _______, _______
    ),

    /*
     * Power-user Layer
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |AUTOC|KEEPR|     |     |     |PGDN |PGUP |     |     |     | BOOT|
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * | CAPS|CAPSW|     |     |     |     |     |LEFT |DOWN | UP  |RIGHT|     |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     * |     |     |     |     |     |     |     |NXTW |HOME | END |     |LOCK |     |
     * +-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
     *                   |     |     |     |     |     |     |     |
     *                   +-----+-----+-----+     +-----+-----+-----+
     *
     * Note: NXTW = Next Window (Cmd+Grave), HOME/END on M and comma, AUTOC = toggle autocorrect,
     *       CAPSW = Caps Word (also: hold D+K together), LOCK = Layer Lock,
     *       BOOT = Enter bootloader mode
     * KEEPR = Cycle keep-awake modes: Off → Manual (blue) → PIR-gated (red) → Off
     *   Mode 0 (Off): LED off, no tickler
     *   Mode 1 (Manual): LED blue breathing, tickle when idle 60s
     *   Mode 2 (PIR): LED red breathing, tickle only when motion detected
     */
    [_POWER] = LAYOUT_split_3x6_3(
        _______, _______, AC_TOGG, KEEPER_TOGG, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______, QK_BOOT,
        KC_CAPS, CW_TOGG, _______, _______, _______, _______,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,     NEXTWIN, KC_HOME, KC_END,  _______, QK_LLCK, _______,
                                   _______, _______, _______,     _______, _______, _______
    )
};

// Chordal Hold handedness. '*' keys are exempt from the opposite-hands rule:
//   - Thumbs, so a home row mod + a same-side thumb key still counts as a hold
//     (e.g. Shift(D) + Backspace = Delete, Ctrl(F) + Backspace).
//   - TAB_PWR, so Tab + a left-hand Power layer key (CAPS, CW, AUTOC, KEEPR)
//     works without holding Tab past the tapping term.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x6_3(
    'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R',
    '*', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R',
                   '*', '*', '*',    '*', '*', '*'
);

// Per-key tap/hold configuration - DISABLED for now to use QMK defaults
// Uncomment and re-enable TAPPING_TERM_PER_KEY in config.h if needed
/*
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GUI_A:
        case ALT_S:
        case SHFT_D:
        case CTRL_F:
        case CTRL_J:
        case SHFT_K:
        case ALT_L:
        case GUI_SEMI:
            return 200;
        default:
            return TAPPING_TERM;
    }
}
*/

// Per-key hold-on-other-key-press configuration - DISABLED for now to use QMK defaults
// Uncomment and re-enable HOLD_ON_OTHER_KEY_PRESS_PER_KEY in config.h if needed
/*
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TAB_PWR:
        case NUM_LYR:
        case FKEY_LYR:
            return true;
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
            return false;
        default:
            return false;
    }
}
*/

// Process custom keycodes (and let keeper track activity / handle KEEPER_TOGG)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!keeper_process_record(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case CTRL_LCBR:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LCBR);  // Tap: send { instead of [
                return false;
            }
            return true;  // Hold: normal Ctrl handling
    }

    return true;  // Process all other keycodes normally
}

void matrix_scan_user(void) {
    keeper_task();
}

// Force handedness write on boot when using INIT_EE_HANDS_LEFT/RIGHT
void keyboard_post_init_user(void) {
#if defined(INIT_EE_HANDS_LEFT)
    eeconfig_update_handedness(true);  // Force write LEFT
#elif defined(INIT_EE_HANDS_RIGHT)
    eeconfig_update_handedness(false); // Force write RIGHT
#endif

    keeper_init();
}
