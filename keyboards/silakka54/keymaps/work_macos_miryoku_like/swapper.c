// https://github.com/qmk/qmk_firmware/blob/user-keymaps-still-present/users/callum/swapper.c
#include "swapper.h"

void update_swapper(
    bool *active,
    bool *shifted,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t end_trigger,
    uint16_t keycode,
    keyrecord_t *record,
    bool is_shifted
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }

            // A custom keycode does not automatically inherit the held
            // home-row Shift modifier. Register a modded switch key instead.
            *shifted = is_shifted;
            if (*shifted) {
                register_code16(S(tabish));
            } else {
                register_code(tabish);
            }
        } else {
            if (*shifted) {
                unregister_code16(S(tabish));
                *shifted = false;
            } else {
                unregister_code(tabish);
            }
            // Keep cmdish held until the designated layer key is released.
        }
    } else if (*active && keycode == end_trigger && !record->event.pressed) {
        unregister_code(cmdish);
        *active = false;
        *shifted = false;
    }
}
