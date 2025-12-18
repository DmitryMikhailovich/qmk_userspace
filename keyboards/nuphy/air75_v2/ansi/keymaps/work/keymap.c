/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    HOLD_CAPS
};

enum m_keycodes {
    M_CAPS_LOCK = SAFE_RANGE,
};

#define KC_ARFI LGUI(LSFT(KC_4))        // Save picture of seleted area as file
#define KC_ARCL LGUI(LSFT(LCTL(KC_4)))  // Copy picture of selected area to the clipboard
#define KC_SCRE LGUI(LSFT(KC_5)) // Screenshot and recording options

static fast_timer_t caps_tap_timer = 0;
static bool caps_pressed = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// layer Mac
[MAC_BASE] = LAYOUT_75_ansi(
    KC_ESC,     KC_F1,      KC_F2,      KC_F3,        KC_F4,       KC_F5,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_ARCL,      KC_INS,        MO(MAC_FN),
    KC_GRV,     KC_1,       KC_2,       KC_3,         KC_4,       KC_5,      KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,                   KC_BSPC,       KC_PGUP,
    KC_TAB,     KC_Q,       KC_W,       KC_E,         KC_R,       KC_T,      KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,                  KC_BSLS,       KC_PGDN,
M_CAPS_LOCK,    KC_A,       KC_S,       KC_D,         KC_F,       KC_G,      KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                              KC_ENT,        KC_HOME,
    KC_LSFT,                KC_Z,       KC_X,         KC_C,       KC_V,      KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,                KC_RSFT,      KC_UP,         KC_END,
    KC_LCTL,    KC_LALT,    KC_LGUI,                                         KC_SPC,                             KC_RGUI,    KC_GLB,     KC_RCTL,                KC_LEFT,      KC_DOWN,       KC_RGHT),

// layer Mac Fn
[MAC_FN] = LAYOUT_75_ansi(
    _______,     KC_BRID,   KC_BRIU,    KC_MCTL,      MAC_SEARCH,  MAC_VOICE, MAC_DND,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_SCRE,     _______,    _______,
    _______,     LNK_BLE1,  LNK_BLE2,   LNK_BLE3,     LNK_RF,      _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,                  _______,    _______,
    _______,     _______,   _______,    _______,      _______,     _______,  _______,    _______,    _______,    _______,    _______,    DEV_RESET,  SLEEP_MODE,               BAT_SHOW,   _______,
    _______,     _______,   _______,    KC_DEL,       _______,     _______,  _______,    _______,    _______,    _______,    _______,    _______,                              _______,    _______,
    _______,                _______,    _______,      RGB_TEST,    _______,  BAT_NUM,    _______,    _______,    RGB_SPD,    RGB_SPI,    _______,                _______,      RGB_VAI,    _______,
    _______,     _______,   _______,                                         _______,                             _______,   _______,    _______,                RGB_MOD,      RGB_VAD,    RGB_HUI),

// layer win
[WIN_BASE] = LAYOUT_75_ansi(
    KC_ESC,     KC_F1,      KC_F2,      KC_F3,        KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,         KC_F10,     KC_F11,     KC_F12,     KC_PSCR,    KC_INS,     KC_DEL,
    KC_GRV,     KC_1,       KC_2,       KC_3,         KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,          KC_0,       KC_MINS,    KC_EQL,                 KC_BSPC,    KC_PGUP,
    KC_TAB,     KC_Q,       KC_W,       KC_E,         KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,          KC_P,       KC_LBRC,    KC_RBRC,                KC_BSLS,    KC_PGDN,
M_CAPS_LOCK,    KC_A,       KC_S,       KC_D,         KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,          KC_SCLN,    KC_QUOT,                            KC_ENT,     KC_HOME,
    KC_LSFT,                KC_Z,       KC_X,         KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,       KC_DOT,     KC_SLSH,                KC_RSFT,    KC_UP,      KC_END,
    KC_LCTL,    KC_LGUI,    KC_LALT,                                          KC_SPC,                             KC_RALT,       MO(WIN_FN), KC_RCTL,                KC_LEFT,    KC_DOWN,    KC_RGHT),

// layer win Fn
[WIN_FN] = LAYOUT_75_ansi(
    _______,    KC_BRID,    KC_BRIU,    _______,      _______,    _______,    _______,    KC_MPRV,    KC_MPLY,    KC_MNXT,      KC_MUTE,     KC_VOLD,    KC_VOLU,    _______,    _______,    _______,
    _______,    LNK_BLE1,   LNK_BLE2,   LNK_BLE3,     LNK_RF,     _______,    _______,    _______,    _______,    _______,      _______,     _______,    _______,                _______,    _______,
    _______,    _______,    _______,    _______,      _______,    _______,    _______,    _______,    _______,    _______,      _______,     DEV_RESET,  SLEEP_MODE,             BAT_SHOW,   _______,
    _______,    _______,    _______,    _______,      _______,    _______,    _______,    _______,    _______,    _______,      _______,     _______,                            _______,    _______,
    _______,                _______,    _______,      RGB_TEST,   _______,    BAT_NUM,    _______,    _______,    RGB_SPD,      RGB_SPI,     _______,                _______,    RGB_VAI,    _______,
    _______,    _______,    _______,                                          _______,                            _______,      _______,     _______,                RGB_MOD,    RGB_VAD,    RGB_HUI),

// hold caps layer
[HOLD_CAPS] = LAYOUT_75_ansi(
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,      XXXXXXX,     XXXXXXX,    XXXXXXX,    KC_ARFI,   XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,      XXXXXXX,     KC_DEL,     XXXXXXX,               XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX,     XXXXXXX,    XXXXXXX,    KC_HOME,    KC_PGUP,    KC_PGDN,      KC_END,      KC_CAPS,    XXXXXXX,               XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_DEL,      XXXXXXX,     XXXXXXX,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,     XXXXXXX,     KC_INS,                            XXXXXXX,    XXXXXXX,
    _______,                XXXXXXX,    XXXXXXX,     C(KC_C),     C(KC_V),    XXXXXXX,    XXXXXXX,    XXXXXXX,    SIDE_SPD,     SIDE_SPI,    KC_CAPS,                XXXXXXX,   SIDE_VAI,   XXXXXXX,
    _______,    _______,    _______,                                          _______,                            XXXXXXX,      XXXXXXX,     XXXXXXX,                SIDE_MOD,  SIDE_VAD,   SIDE_HUI)
};                                                                         /* ^^^^^^^caps word*/


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool caps_layer_active = layer_state_is(HOLD_CAPS);
    switch (keycode) {
    case M_CAPS_LOCK:
        if (record->event.pressed) {
            caps_tap_timer = timer_read_fast();
            caps_pressed = true;
            layer_on(HOLD_CAPS);
        } else {
            if (caps_pressed) {
                if(timer_elapsed_fast(caps_tap_timer) < TAPPING_TERM) {
                    tap_code(KC_ESC);
                }
                layer_off(HOLD_CAPS);
                caps_pressed = false;
            }
        }
        return false;
    case KC_SPC:
        if (record->event.pressed && caps_layer_active) {
            caps_word_toggle();
            return false;
        }
    default:
        return true;
    }
}