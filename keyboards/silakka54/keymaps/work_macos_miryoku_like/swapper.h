// https://github.com/qmk/qmk_firmware/blob/user-keymaps-still-present/users/callum/swapper.h
#pragma once

#include QMK_KEYBOARD_H

// Implements cmd-tab like behaviour on a single key. On first tap of trigger
// cmdish is held and tabish is tapped -- cmdish then remains held until
// end_trigger is released. For example:
//
//     nav down, trigger, trigger, nav up -> cmd down, tab, tab, cmd up
//
// This behaviour is useful for more than just cmd-tab, hence: cmdish, tabish.
void update_swapper(
    bool *active,
    bool *shifted,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t end_trigger,
    uint16_t keycode,
    keyrecord_t *record,
    bool is_shifted);
