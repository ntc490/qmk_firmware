#include "kinesis.h"

#define BASE 0 // Base qwerty
#define NUMBERS 1
#define FKEYS 2
#define POWERUSER 3

/****************************************************************************************************
*
* Keymap: Default Layer in Qwerty
*
* ,-------------------------------------------------------------------------------------------------------------------.
* | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |  FN0 |  BOOT  |
* |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
* | =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | -_     |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | \|     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Caps   |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |  ;:  | '"     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Shift  |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |  ,.  |  .>  |  /?  | Shift  |
* `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
*          | `~   | INS  | Left | Right|                                         | Up   | Down |  [{  |  ]}  |
*          `---------------------------'                                         `---------------------------'
*                                        ,-------------.         ,-------------.
*                                        | Ctrl | Alt  |         | Gui  | Ctrl |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      | Home |         | PgUp |      |      |
*                                 | BkSp | Del  |------|         |------|Return| Space|
*                                 |      |      | End  |         | PgDn |      |      |
*                                 `--------------------'         `--------------------'
*/

#if 1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = KEYMAP(
           KC_ESC, KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8,
           KC_EQL, KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,
           KC_TAB, KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,
           KC_CAPS,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,
           KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,
                   KC_GRV ,KC_INS ,KC_LEFT,KC_RGHT,
			   KC_LCTL,KC_LALT,
                                    KC_HOME,
                           KC_BSPC,KC_DEL ,KC_END ,
    KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_PSCR ,KC_SLCK  ,KC_PAUS, KC_FN0, KC_1,
	KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,
	KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_BSLS,
	KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
	KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,
		KC_UP  ,KC_DOWN,KC_LBRC,KC_RBRC,
           KC_RGUI,KC_RCTL,
           KC_PGUP,
           KC_PGDN,KC_ENTER ,KC_SPC
    )
};

#else
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = ERGODOX_KEYMAP(
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      XXXXXXX,
  MO(POWERUSER), KC_A,      KC_S,      KC_D,      KC_F,      KC_G,
    KC_LSHIFT, KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      XXXXXXX,
               XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
                                                       MO(NUMBERS), XXXXXXX,
                                                       KC_LGUI,
                                                       KC_SPACE, CTL_T(KC_NO), KC_LALT,

    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_BSLASH,
               KC_H,      KC_J,      KC_K,      KC_L,      KC_SCOLON, KC_QUOTE,
    XXXXXXX,   KC_N,      KC_M,      KC_COMMA,  KC_DOT,    KC_SLASH,  KC_RSHIFT,
               XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
                  KC_LGUI,   MO(FKEYS),
                  RCTL_T(KC_NO),
                  KC_LALT,   KC_ENTER,   KC_SPACE),

[NUMBERS] = ERGODOX_KEYMAP(
    _______,   _______,   _______,   _______,   _______,   _______,   _______,
    KC_ESCAPE, _______,   _______,   _______,   KC_LPRN,   KC_RPRN,   _______,
    _______,   KC_TILD,   _______,   _______,   KC_LCBR,   KC_RCBR,
    _______,   KC_GRAVE,  _______,   _______,   KC_LBRACKET,KC_RBRACKET,_______,
               _______,   _______,   _______,   _______,   _______,
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

[FKEYS] = ERGODOX_KEYMAP(
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

[POWERUSER] = ERGODOX_KEYMAP(
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
};
#endif

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {
}
