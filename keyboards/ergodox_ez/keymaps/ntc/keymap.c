#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // Base qwerty
#define NUMBERS 1
#define FKEYS 2
#define POWERUSER 3
#define MOUSE 4

#define _POWERUSR MO(POWERUSER)
#define _NUMBERS MO(NUMBERS)
#define _FKEYS TG(FKEYS)
#define _MOUSE MO(MOUSE)

/* Allow single tap and then shifted-char sequence */
#define _LSHIFT LSFT_T(KC_NO)
#define _RSHIFT RSFT_T(KC_NO)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_ergodox(
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      XXXXXXX,
    _POWERUSR, KC_A,      KC_S,      KC_D,      KC_F,      KC_G,
    KC_LSHIFT, KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      XXXXXXX,
               XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
                                                       _NUMBERS, _MOUSE,
                                                       KC_LGUI,
                                                       KC_BSPACE, KC_LCTRL, KC_LALT,

    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_BSLASH,
               KC_H,      KC_J,      KC_K,      KC_L,      KC_SCOLON, KC_QUOTE,
    XXXXXXX,   KC_N,      KC_M,      KC_COMMA,  KC_DOT,    KC_SLASH,  _RSHIFT,
               XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
                  _FKEYS,    KC_ESCAPE,
                  KC_RCTRL,
                  KC_LALT,   KC_ENTER,   KC_SPACE),

[NUMBERS] = LAYOUT_ergodox(
    _______,   _______,   _______,   _______,   _______,    _______,     _______,
    KC_ESCAPE, _______,   _______,   _______,   KC_LPRN,    KC_RPRN,     _______,
    KC_CAPS,   KC_TILD,   _______,   _______,   KC_LCBR,    KC_RCBR,
    _______,   KC_GRAVE,  _______,   _______,   KC_LBRACKET,KC_RBRACKET, _______,
               _______,   _______,   _______,   _______,    _______,
                                                       _______,  _______,
                                                       _______,
                                                       _______,  _______,   _______,

    _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   KC_EQUAL,  KC_7,      KC_8,      KC_9,      KC_MINUS,  KC_MINUS,
               KC_MINUS,  KC_4,      KC_5,      KC_6,      KC_PLUS,   KC_SLASH,
    _______,   KC_DOT,    KC_1,      KC_2,      KC_3,      KC_ENTER,  _______,
               _______,   _______,   _______,   _______,   _______,
                  _______,   KC_BSPACE,
                  _______,
                  _______,   _______,   KC_0),

[FKEYS] = LAYOUT_ergodox(
    _______,   _______,   _______,   _______,   _______,   _______,   _______,
    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     _______,
    KC_F13,    KC_F14,    KC_F15,    _______,   _______,   _______,
    _______,   _______,   _______,   _______,   _______,   _______,   _______,
               _______,   _______,   _______,   _______,   _______,
                                                       _______,   _______,
                                                       _______,
                                                       _______,   _______,   _______,

    _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,
               _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,   _______,   _______,   _______,
               _______,   _______,   _______,   _______,   _______,
                  _______,   _______,
                  _______,
                  _______,   _______,   _______),

[POWERUSER] = LAYOUT_ergodox(
    _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,   _______,   ALL_T(KC_E),_______,  ALL_T(KC_T), _______,
    _______,   _______,   ALL_T(KC_S),LGUI(KC_LBRACKET),LGUI(KC_RBRACKET),ALL_T(KC_G),
    _______,   _______,   _______,   _______,   _______,   ALL_T(KC_B), _______,
               _______,   _______,   _______,   _______,   _______,
                                                       _______,   _______,
                                                       _______,
                                                       _______,   _______,   _______,

    _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   KC_PGDOWN, KC_PGUP,   ALL_T(KC_I),_______,  ALL_T(KC_P),_______,
               KC_LEFT,   KC_DOWN,   KC_UP,    KC_RIGHT,   _______,   _______,
    _______,   LGUI(KC_GRAVE),_______,_______,  LALT(KC_KP_ASTERISK), _______, _______,
               _______,   _______,   _______,   _______,   _______,
                  _______,   _______,
                  _______,
                  _______,   _______,   _______),

[MOUSE] = LAYOUT_ergodox(
    _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,   _______,   _______,   _______,
               _______,   _______,   _______,   _______,   _______,
                                                       _______,   _______,
                                                       _______,
                                                       _______,   _______,   _______,

    _______,   KC_MS_WH_UP, KC_MS_WH_DOWN, _______,   _______,   _______,   _______,
    _______,   _______,     _______,       _______,   _______,   _______,   _______,
               KC_MS_L,     KC_MS_D,       KC_MS_U,   KC_MS_R,   _______,   _______,
    _______,   KC_MS_BTN1,  KC_MS_BTN2,    _______,   _______,   _______,   _______,
               _______,     _______,       _______,   _______,   _______,
                  _______,   _______,
                  _______,
                  _______,   _______,   _______),
};


const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    // TODO: Make this relevant to the ErgoDox EZ.
    case NUMBERS:
      ergodox_right_led_1_on();
      break;
    case POWERUSER:
      ergodox_right_led_2_on();
      break;
    case FKEYS:
      ergodox_right_led_3_on();
      break;
    default:
      // none
      break;
  }

};
