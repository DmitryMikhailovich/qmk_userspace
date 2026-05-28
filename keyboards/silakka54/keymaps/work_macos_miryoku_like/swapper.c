// https://github.com/qmk/qmk_firmware/blob/user-keymaps-still-present/users/callum/swapper.c
#include "swapper.h"

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record,
    bool is_shifted
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                // if (is_shifted) {
                //     register_code(LSFT(cmdish));
                // } else {
                    register_code(cmdish);
                // }
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active) {
        unregister_code(cmdish);
        *active = false;
    }
}
