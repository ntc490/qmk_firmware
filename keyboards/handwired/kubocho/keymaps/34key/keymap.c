// Copyright 2026 Nathan Crapo
// SPDX-License-Identifier: GPL-2.0-or-later
//
// 34-key layout for the Kubocho: 3x5 per side + 2 thumbs per side.
// The outer columns and outer thumb keys are KC_NO, so this can be tried on a
// full Kubocho before moving to a real 34-key board.
//
// Keeper/PIR/handedness code is copied from keymaps/default - keep them in sync.

#include QMK_KEYBOARD_H

// Layer definitions
enum layers {
    _BASE,
    _NUMS,
    _FKEYS,
    _POWER
};

// Keeper mode states
enum keeper_modes {
    KEEPER_OFF,
    KEEPER_MANUAL,
    KEEPER_PIR
};

// Custom keycodes
enum custom_keycodes {
    KEEPER_TOGG = SAFE_RANGE,  // Cycle keeper modes: Off -> Manual -> PIR-gated -> Off
};

// Layer-taps
#define NUM_G   LT(_NUMS, KC_G)     // G tap, NUMS hold (use with right-hand numpad)
#define NUM_H   LT(_NUMS, KC_H)     // H tap, NUMS hold (use with left-hand symbols)
#define FKEY_T  LT(_FKEYS, KC_T)    // T tap, FKEYS hold (F-keys are on the right hand)
#define TAB_PWR LT(_POWER, KC_TAB)  // Tab tap, POWER hold (left thumb) - same as default keymap

#define NEXTWIN LGUI(KC_GRV)        // Next window (Cmd+Grave)

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

// PIR sensor configuration
#define PIR_PIN GP29  // PIR sensor on GPIO29

// Keeper (keep-awake) state
static uint8_t keeper_mode = KEEPER_OFF;
static uint32_t last_activity_time = 0;
#define KEEPER_TIMEOUT 60000  // 60 seconds in milliseconds


// Combos: press both keys together
//   C + V -> Tab (experimental)
//   V + B -> Esc
//   N + M -> Esc
const uint16_t PROGMEM combo_cv[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_vb[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM combo_nm[] = {KC_N, KC_M, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_cv, KC_TAB),
    COMBO(combo_vb, KC_ESC),
    COMBO(combo_nm, KC_ESC),
};

// Key overrides: Shift + Backspace -> Delete
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &delete_key_override,
};

// Override breathing intervals - lower = faster, higher = slower
// Values are in ~65ms ticks. 10 = ~650ms per animation step.
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {10, 10, 10, 10};

// XXXXXXX = key not present on a 34-key board
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |  Q  |  W  |  E  |  R  | T^F |     |  Y  |  U  |  I  |  O  |  P  |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       | A^G | S^A | D^S | F^C | G^N |     | H^N | J^C | K^S | L^A | ;^G |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |  Z  |  X  |  C  |  V  |  B  |     |  N  |  M  |  ,  |  .  |  /  |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *                   |BKSP |TAB^P|                 | ENT | SPC |
     *                   +-----+-----+                 +-----+-----+
     *
     * ^G=GUI ^A=ALT ^S=SHIFT ^C=CTRL ^N=NUMS ^F=FKEYS ^P=POWER (on hold)
     * Combos: C+V=Tab, V+B=Esc, N+M=Esc
     */
    [_BASE] = LAYOUT_split_3x6_3(
        XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    FKEY_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    XXXXXXX,
        XXXXXXX, GUI_A,   ALT_S,   SHFT_D,  CTRL_F,  NUM_G,       NUM_H,   CTRL_J,  SHFT_K,  ALT_L,   GUI_SEMI,XXXXXXX,
        XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
                                   KC_BSPC, TAB_PWR, XXXXXXX,     XXXXXXX, KC_ENT,  KC_SPC
    ),

    /*
     * Numbers Layer (hold G for the right side, H for the left side)
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |  `  |     |     |  (  |  )  |     |  =  |  7  |  8  |  9  |  \  |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |     |     |     | {^C |  }  |     |  -  | 4^C | 5^S | 6^A | '^G |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |     |     | ESC |  [  |  ]  |     |  .  |  1  |  2  |  3  |LOCK |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *                   |     |     |                 |     |  0  |
     *                   +-----+-----+                 +-----+-----+
     *
     * Blank left home row = home row mods poke through from the base layer.
     * LOCK = Layer Lock: keep this layer on after releasing G (tap again to unlock)
     */
    [_NUMS] = LAYOUT_split_3x6_3(
        XXXXXXX, KC_GRV,  _______, _______, KC_LPRN, KC_RPRN,     KC_EQL,  KC_7,    KC_8,    KC_9,    KC_BSLS, XXXXXXX,
        XXXXXXX, _______, _______, _______, CTRL_LCBR, KC_RCBR,   KC_MINS, CTRL_4,  SHFT_5,  ALT_6,   GUI_QUOT,XXXXXXX,
        XXXXXXX, _______, _______, KC_ESC,  KC_LBRC, KC_RBRC,     KC_DOT,  KC_1,    KC_2,    KC_3,    QK_LLCK, XXXXXXX,
                                   _______, _______, XXXXXXX,     XXXXXXX, _______, KC_0
    ),

    /*
     * F-Keys Layer (hold T)
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |     |     |     |     |     |     | F10 | F7  | F8  | F9  | F13 |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |     |     |     |     |     |     | F11 | F4  | F5  | F6  | F14 |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |     |     |     |     |     |     | F12 | F1  | F2  | F3  | F15 |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     */
    [_FKEYS] = LAYOUT_split_3x6_3(
        XXXXXXX, _______, _______, _______, _______, _______,     KC_F10,  KC_F7,   KC_F8,   KC_F9,   KC_F13,  XXXXXXX,
        XXXXXXX, _______, _______, _______, _______, _______,     KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_F14,  XXXXXXX,
        XXXXXXX, _______, _______, _______, _______, _______,     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F15,  XXXXXXX,
                                   _______, _______, XXXXXXX,     XXXXXXX, _______, _______
    ),

    /*
     * Power-user Layer (hold left thumb Tab)
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |     |AUTOC|KEEPR|     |     |     |PGDN |PGUP |     |     |BOOT |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       | CAPS|CAPSW|     |     |     |     |LEFT |DOWN | UP  |RIGHT|     |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *       |     |     |     |     |     |     |NXTW |HOME | END |     |LOCK |
     *       +-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+
     *
     * CAPSW = Caps Word (also: hold D+K together), LOCK = Layer Lock
     * KEEPR = Cycle keep-awake modes: Off → Manual (blue) → PIR-gated (red) → Off
     *   Mode 0 (Off): LED off, no tickler
     *   Mode 1 (Manual): LED blue breathing, tickle when idle 60s
     *   Mode 2 (PIR): LED red breathing, tickle only when motion detected
     */
    [_POWER] = LAYOUT_split_3x6_3(
        XXXXXXX, _______, AC_TOGG, KEEPER_TOGG, _______, _______, KC_PGDN, KC_PGUP, _______, _______, QK_BOOT, XXXXXXX,
        XXXXXXX, KC_CAPS, CW_TOGG, _______, _______, _______,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, XXXXXXX,
        XXXXXXX, _______, _______, _______, _______, _______,     NEXTWIN, KC_HOME, KC_END,  _______, QK_LLCK, XXXXXXX,
                                   _______, _______, XXXXXXX,     XXXXXXX, _______, _______
    )
};

// Chordal Hold handedness. Thumbs are '*' so a home row mod + a same-side
// thumb key (e.g. Ctrl(F) + Backspace) still counts as a hold.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x6_3(
    'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R',
                   '*', '*', '*',    '*', '*', '*'
);

// Process custom keycodes and track activity for keeper
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keeper_mode == KEEPER_MANUAL) {
        last_activity_time = timer_read32();
    }

    switch (keycode) {
        case CTRL_LCBR:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LCBR);  // Tap: send { instead of [
                return false;
            }
            return true;  // Hold: normal Ctrl handling

        case KEEPER_TOGG:
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

    return true;  // Process all other keycodes normally
}

// Keeper: Check timer and send shift if idle too long
// Also check the PIR sensor
void matrix_scan_user(void) {
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

// Force handedness write on boot when using INIT_EE_HANDS_LEFT/RIGHT
void keyboard_post_init_user(void) {
#if defined(INIT_EE_HANDS_LEFT)
    eeconfig_update_handedness(true);  // Force write LEFT
#elif defined(INIT_EE_HANDS_RIGHT)
    eeconfig_update_handedness(false); // Force write RIGHT
#endif

    // Configure PIR sensor pin as input (no pull resistor - PIR has its own pull)
    gpio_set_pin_input(PIR_PIN);
    uprintf("PIR sensor initialized on GP29\n");

    // Initialize RGB to off (will turn on when keeper is enabled)
    rgblight_disable();
}
