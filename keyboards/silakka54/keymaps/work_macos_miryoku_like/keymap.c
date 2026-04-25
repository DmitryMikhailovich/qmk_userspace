// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)
#define U_LANG LALT(KC_SPC)

enum layers {
    BASE,
    NAV,
    MEDIA,
    // NUM,
    // SYM,
    FUN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_GRV,  KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                               KC_6,    KC_7,         KC_8,         KC_9,         KC_0,            KC_MINS,
        KC_TAB,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                               KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            KC_EQL,
        KC_ESC,  LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,                               KC_H,    LSFT_T(KC_J), LGUI_T(KC_K), LALT_T(KC_L), LCTL_T(KC_SCLN), KC_QUOT,
        KC_LBRC, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,                               KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         KC_RBRC,
                                                     LT(MEDIA, KC_BSLS), LT(NAV, KC_ESC), KC_SPC,    KC_ENT, KC_BSPC, LT(FUN, KC_DEL)
    ),                                                                                              //LT(SYM, KC_ENT), LT(NUM, KC_BSPC), LT(FUN, KC_DEL)
    [NAV] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               U_RDO,    U_PST,   U_CPY,   U_CUT,   U_UND,   XXXXXXX,
        U_LANG,   KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                                               KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, CW_TOGG,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               KC_HOME,  KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_CAPS,
                                             XXXXXXX, XXXXXXX, XXXXXXX,                              KC_ENT, KC_BSPC,  KC_DEL
    ),
    [MEDIA] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                                               KC_MPRV,  KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                             XXXXXXX, XXXXXXX, XXXXXXX,                             KC_MSTP, KC_MPLY,  KC_MUTE
    ),
    // [NUM] = LAYOUT(
    //     XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX,  KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX,  KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                                                XXXXXXX,  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
    //     XXXXXXX,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_SLSH,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //                                          KC_DOT,  KC_0,  KC_MINS,                               XXXXXXX, XXXXXXX,  XXXXXXX
    // ),
    // [SYM] = LAYOUT(
    //     XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX,  KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX,  KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                                               XXXXXXX,  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
    //     XXXXXXX,  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //                                          KC_LPRN, KC_RPRN, KC_UNDS,                             XXXXXXX, XXXXXXX,  XXXXXXX
    // ),
    [FUN] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  KC_F11,  KC_F4,   KC_F5,   KC_F6,   XXXXXXX,                                               XXXXXXX,  KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, XXXXXXX,
        XXXXXXX,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                             XXXXXXX, KC_SPC,  KC_TAB,                              XXXXXXX, XXXXXXX,  XXXXXXX
    ),
};
