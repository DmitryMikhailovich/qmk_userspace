// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

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
    my_num_layer,    // Layer NUM: Layer NUM indicator (priority 3)
    my_fun_layer,    // Layer FUN: Layer FUN indicator (priority 4)
    my_capswords_layer,   // Layer BASE: Caps Words indicator (priority 5)
    my_capslock_layer   // Layer BASE: Caps lock indicator (highest priority)
);

enum layers {
    BASE,
    NAV,
    MEDIA,
    NUM,
    FUN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_GRV,  KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                               KC_6,    KC_7,         KC_8,         KC_9,         KC_0,            KC_MINS,
        KC_TAB,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                               KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            KC_EQL,
        KC_ESC,  LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,                               KC_H,    RSFT_T(KC_J), RGUI_T(KC_K), LALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT,
LT(MEDIA,KC_LBRC), KC_Z,       KC_X,         KC_C,         KC_V,         KC_B,                               KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         KC_RBRC,
                                                                MO(NUM), MO(NAV), KC_SPC,            KC_ENT, KC_BSPC, LT(FUN, KC_DEL)
    ),                                                                                              //LT(SYM, KC_ENT), LT(NUM, KC_BSPC), LT(FUN, KC_DEL)
    [NAV] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, U_RDO,   XXXXXXX, /*TODO: do I need undo and clipboard here?->*/U_UND,    U_PST,   U_CPY,   U_CUT,   KC_LBRC, KC_RBRC,
        U_LANG,   KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                                               KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, CW_TOGG, KC_CAPS,
        XXXXXXX,  U_UND,   U_CUT,   U_CPY,   U_PST,   XXXXXXX,                                               KC_HOME,  KC_PGDN, KC_PGUP, KC_END,  KC_BSLS, KC_INS,
                                             XXXXXXX, _______, XXXXXXX,                              KC_ENT, KC_BSPC,  KC_DEL
    ),
    [MEDIA] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               KC_MPRV,  KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                             XXXXXXX, XXXXXXX, XXXXXXX,                             KC_MSTP, KC_MPLY,  KC_MUTE
    ),
    [NUM] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               KC_LBRC,  KC_7,    KC_8,    KC_9,    KC_RBRC, XXXXXXX,
        XXXXXXX,  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                                               KC_MINS,  KC_4,    KC_5,    KC_6,    KC_EQL,  XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               KC_SCLN,  KC_1,    KC_2,    KC_3,    KC_SLSH, XXXXXXX,
                                             XXXXXXX, XXXXXXX, XXXXXXX,                             KC_COMM, KC_0, KC_DOT
    ),
    [FUN] = LAYOUT(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  KC_F11,  KC_F4,   KC_F5,   KC_F6,   XXXXXXX,                                               XXXXXXX,  KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, XXXXXXX,
        XXXXXXX,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   XXXXXXX,                                               XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
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
        case NUM:
            rgblight_set_layer_state(2, true);  // Layer NUM = green
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

// Enable/disable layers based on caps word state
void caps_word_set_user(bool active) {
    rgblight_set_layer_state(4, active);
}
