// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "swapper.h"

#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)
#define U_LANG LALT(KC_SPC)


// Define lighting layers for the internal LED
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_ORANGE}    // Light the single LED (LED 0) red when caps lock is active
);

const rgblight_segment_t PROGMEM my_capswords_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PINK}    // Light the single LED (LED 0) yellow when caps words is active
);

const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE}   // Light the single LED (LED 0) blue when layer NAV is active
);

const rgblight_segment_t PROGMEM my_media_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PURPLE} // Light the single LED (LED 0) purple when layer MEDIA is active
);

const rgblight_segment_t PROGMEM my_num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN}  // Light the single LED (LED 0) green when layer NUM is active
);

const rgblight_segment_t PROGMEM my_fun_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_WHITE}  // Light the single LED (LED 0) green when layer FUN is active
);

// Layer priority: caps lock > layer 3 > layer 2 > layer 1
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_nav_layer,    // Layer NAV: Layer NAV indicator (priority 1)
    my_media_layer,    // Layer MEDIA: Layer MEDIA indicator (priority 2)
    my_num_layer,    // Layer NUMPAD: Layer NUMPAD indicator (priority 3)
    my_fun_layer,    // Layer FUN: Layer FUN indicator (priority 4)
    my_capswords_layer,   // Layer BASE: Caps Words indicator (priority 5)
    my_capslock_layer   // Layer BASE: Caps lock indicator (highest priority)
);

bool sw_app_active = false;
bool sw_win_active = false;
bool sw_lang_active = false;

enum keycodes {
    SW_APP = SAFE_RANGE,
    SW_WIN,
    SW_LANG,
};

enum layers {
    BASE,
    NAV,
    MEDIA,
    NUMPAD,
    FUN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_GRV,  KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                               KC_6,    KC_7,         KC_8,         KC_9,         KC_0,            KC_MINS,
        KC_TAB,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                               KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            KC_EQL,
LT(MEDIA, KC_ESC),LCTL_T(KC_A),LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,                               KC_H,    RSFT_T(KC_J), RGUI_T(KC_K), LALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT,
       KC_LSFT,  KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,                               KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         KC_RSFT,
                                                             MO(NUMPAD), MO(NAV), KC_SPC,            KC_ENT, KC_BSPC, LT(FUN, KC_DEL)
    ),
    [NAV] = LAYOUT(
        SW_WIN,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        SW_APP,  XXXXXXX, XXXXXXX, XXXXXXX, U_RDO,   XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC,
        SW_LANG, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                                               KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, CW_TOGG, KC_CAPS,
        XXXXXXX, U_UND,   U_CUT,   U_CPY,   U_PST,   XXXXXXX,                                               KC_HOME,  KC_PGDN, KC_PGUP, KC_END,  KC_BSLS, KC_INS,
                                            XXXXXXX, _______, XXXXXXX,                              KC_ENT, KC_BSPC,  KC_DEL
    ),
    [MEDIA] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  KC_BRMD, KC_BRMU, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               KC_MPRV,  KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                             XXXXXXX, XXXXXXX, XXXXXXX,                             KC_MSTP, KC_MPLY,  KC_MUTE
    ),
    [NUMPAD] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               KC_PAST,  KC_7,    KC_8,    KC_9,   KC_PMNS, XXXXXXX,
        XXXXXXX,  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                                               KC_PEQL,  KC_4,    KC_5,    KC_6,   KC_PPLS, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               KC_PENT,  KC_1,    KC_2,    KC_3,   KC_PSLS, XXXXXXX,
                                             _______, XXXXXXX, XXXXXXX,                                KC_0, KC_BSPC,  KC_PDOT
    ),
    [FUN] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_F13,                                                XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_F14,                                                XXXXXXX,  KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, XXXXXXX,
        XXXXXXX,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F15,                                                XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                             XXXXXXX, XXXXXXX,  XXXXXXX,                            XXXXXXX, XXXXXXX,  XXXXXXX
    ),
};


void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    // Restore layer states from EEPROM
    rgblight_reload_from_eeprom();
}

// Enable/disable layers based on caps lock state
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(5, led_state.caps_lock);
    return true;
}

// Enable/disable layers based on layer state
layer_state_t layer_state_set_user(layer_state_t state) {
    // Clear all layer states first
    rgblight_set_layer_state(0, false);
    rgblight_set_layer_state(1, false);
    rgblight_set_layer_state(2, false);
    rgblight_set_layer_state(3, false);
    // rgblight_set_layer_state(4, false);
    rgblight_set_layer_state(5, false);

    // Set the current active layer
    switch (get_highest_layer(state)) {
        case NAV:
            rgblight_set_layer_state(0, true);  // Layer NAV = blue
            break;
        case MEDIA:
            rgblight_set_layer_state(1, true);  // Layer MEDIA = purple
            break;
        case NUMPAD:
            rgblight_set_layer_state(2, true);  // Layer NUMPAD = green
            break;
        case FUN:
            rgblight_set_layer_state(3, true);  // Layer FUN = white
            break;
        default:
            // Layer 0 - no layer color, only caps lock and caps words will show
            break;
    }
    return state;
}

// https://github.com/qmk/qmk_firmware/blob/user-keymaps-still-present/users/callum/callum.c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool is_shifted = get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT);
    update_swapper(
        &sw_win_active, KC_LGUI, KC_GRV, SW_WIN,
        keycode, record, is_shifted
    );
    update_swapper(
        &sw_app_active, KC_LGUI, KC_TAB, SW_APP,
        keycode, record, is_shifted
    );
    update_swapper(
        &sw_lang_active, KC_LOPT, KC_SPC, SW_LANG,
        keycode, record, is_shifted
    );

    return true;
}

// Enable/disable layers based on caps word state
void caps_word_set_user(bool active) {
    rgblight_set_layer_state(4, active);
}
