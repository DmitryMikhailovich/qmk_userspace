/* Copyright 2022 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// clang-format off

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    ALL_FN2,
    HOLD_CAPS
};

enum {
    TD_LSFT_CAPS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_61(
        KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,         KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,        KC_BSLS,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,                  KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,                  KC_RSFT,
        KC_LCTL, KC_LOPT,  KC_LCMD,                            KC_SPC,                             KC_RCMD,  MO(MAC_FN1), MO(ALL_FN2), KC_RCTL),

    [WIN_BASE] = LAYOUT_ansi_61(
        KC_GRV,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,         KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,        KC_BSLS,
  LT(HOLD_CAPS, 
        KC_ESC),  KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,                  KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                  KC_RSFT,
        KC_LCTL,  KC_LGUI,  KC_LALT,                            KC_SPC,                             KC_RALT,  MO(WIN_FN1), MO(ALL_FN2), KC_RCTL),

    [MAC_FN1] = LAYOUT_ansi_61(
        KC_GRV,  KC_BRID,  KC_BRIU, KC_NO,   KC_NO,   RM_VALD, RM_VALU, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  RM_NEXT,
        RM_TOGG, RM_NEXT,  RM_VALU, RM_HUEU, RM_SATU, RM_SPDU, _______, _______, _______, _______, KC_INS,   KC_PGUP,  KC_HOME,  _______,
        _______, RM_PREV,  RM_VALD, RM_HUED, RM_SATD, RM_SPDD, _______, _______, KC_UP,   KC_NO,   KC_PGDN,  KC_END,             _______,
        _______,           _______, _______, _______, _______, _______, NK_TOGG, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL,             _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

    [WIN_FN1] = LAYOUT_ansi_61(
        _______, KC_MPLY,  KC_MUTE, KC_MPRV, KC_MNXT, KC_BRID, KC_BRIU, _______, _______, _______, _______,  _______,  _______,        _______,
        _______, _______,  KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,        _______,
        _______, KC_LEFT,  KC_DOWN,KC_RIGHT, _______, _______, _______, _______, _______, _______, _______,  _______,                  _______,
        _______,           _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,                   _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,        _______),

    [ALL_FN2] = LAYOUT_ansi_61(
        KC_TILD, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,         _______,
        RM_TOGG, RM_NEXT,  RM_VALU, RM_HUEU, RM_SATU, RM_SPDU, _______, _______, _______, _______, _______,  _______,  _______,        _______,
        _______, RM_PREV,  RM_VALD, RM_HUED, RM_SATD, RM_SPDD, _______, _______, _______, _______, _______,  _______,                  _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,                  _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,        _______),
    
    [HOLD_CAPS] = LAYOUT_ansi_61(
        _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,         KC_DEL,
        _______, _______,  _______, _______, _______, _______, _______, KC_HOME, KC_END,  KC_PGUP, KC_PGDN,  _______,  _______,        _______,
        _______, _______,  _______,  KC_DEL, _______, _______, KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, _______,  _______,                  KC_INS,
        _______,           _______, _______, C(KC_C), C(KC_V), _______, _______, _______,  _______, _______,  _______,                 KC_CAPS,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,        _______)
    
};


// clang-format on