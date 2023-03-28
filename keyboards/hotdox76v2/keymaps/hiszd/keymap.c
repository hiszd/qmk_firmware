// Copyright 2021 JasonRen(biu)
// Copyright 2022 Drashna Jael're (@Drashna Jael're)
// Copyright 2022 Zion Koyl (hiszd)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "hiszd.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
     * ┌──────┬───┬───┬───┬───┬───┬───┐                     ┌───┬───┬───┬───┬───┬───┬──────┐
     * │ `    │ 1 │ 2 │ 3 │ 4 │ 5 │WSL│                     │WSR│ 6 │ 7 │ 8 │ 9 │ 0 │    - │
     * ├──────┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼──────┤
     * │ Tab  │ Q │ W │ E │ R │ T │ ; │                     │   │ Y │ U │ I │ O │ P │    \ │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │EscCtl│ A │ S │ D │ F │ G ├───┤                     ├───┤ H │ J │ K │ L │ ; │    ' │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │Shift(│ Z │ X │ C │ V │ B │   │                     │Gam│ N │ M │ , │ . │ / │Shift)│
     * └──┬───┼───┼───┼───┼───┼───┴───┘ ┌───┬───┐ ┌───┬───┐ └───┴───┼───┼───┼───┼───┼───┬──┘
     *    │ ` │DEL│UP │DWN│ADV│         │HOM│END│ │PgU│PgD│         │ ] │ ← │ → │   │GUI│
     *    └───┴───┴───┴───┴───┘     ┌───┼───┼───┤ ├───┼───┼───┐     └───┴───┴───┴───┴───┘
     *                              │   │   │   │ │Cap│   │   │
     *                              │Spc│ _ ├───┤ ├───┤Bks│Ent│
     *                              │   │   │Gui│ │RST│   │   │
     *                              └───┴───┴───┘ └───┴───┴───┘
     */
    [_QWERTY] = LAYOUT_ergodox_pretty_wrapper(
        KC_EQL, __________________NUM_LEFT____________________,  WSPL,            WSPR,   __________________NUM_RIGHT___________________,KC_MINS,
        KC_TAB, __________________QWERTY_L1___________________,KC_EQL,            KC_TRNS,__________________QWERTY_R1___________________,KC_BSPC,
        MT_CTL, __________________QWERTY_L2___________________,                           __________________QWERTY_R2___________________,KC_QUOT,
        KC_LSPO,__________________QWERTY_L3___________________,KC_MINS,           TG_GAM, __________________QWERTY_R3___________________,KC_RSPC,
                _____________MOD_LEFT_____________,                                                   _____________MOD_RIGHT____________,
                                                     KC_HOME, KC_END,             KC_PGUP, KC_PGDN,
                                                              KC_TRNS,            KC_CAPS,
                                            KC_SPC,  ZZ_UNDS, KC_LGUI,            KC_LEAD,  KC_BSLS, KC_ENT
    ),
    /*
     * ┌──────┬───┬───┬───┬───┬───┬───┐                     ┌───┬───┬───┬───┬───┬───┬──────┐
     * │      │   │   │   │   │   │   │                     │   │   │   │   │   │   │      │
     * ├──────┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼──────┤
     * │      │ Q │ W │ D │ F │ Z │ ; │                     │   │ ; │ U │ K │ Y │ P │      │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │      │ A │ S │ E │ R │ L ├───┤                     ├───┤ H │ N │ I │ O │ T │      │
     * ├──────┼───┼───┼───┼───┼───┤ - │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │      │ G │ X │ C │ V │ / │   │                     │   │ B │ J │ M │ , │ . │      │
     * └──┬───┼───┼───┼───┼───┼───┴───┘ ┌───┬───┐ ┌───┬───┐ └───┴───┼───┼───┼───┼───┼───┬──┘
     *    │   │   │   │   │   │         │   │   │ │   │   │         │   │   │   │   │   │
     *    └───┴───┴───┴───┴───┘     ┌───┼───┼───┤ ├───┼───┼───┐     └───┴───┴───┴───┴───┘
     *                              │   │   │   │ │   │   │   │
     *                              │   │   ├───┤ ├───┤   │   │
     *                              │   │   │   │ │   │   │   │
     *                              └───┴───┴───┘ └───┴───┴───┘
     */
    [_RSTLNE] = LAYOUT_ergodox_pretty_wrapper(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS, __________________RSTLNE_L1___________________,KC_SCLN,            KC_TRNS, __________________RSTLNE_R1___________________,KC_TRNS,
        KC_TRNS, __________________RSTLNE_L2___________________,                             __________________RSTLNE_R2___________________,KC_TRNS,
        KC_TRNS, __________________RSTLNE_L3___________________,KC_TRNS,            KC_TRNS, __________________RSTLNE_R3___________________,KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                       KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
                                                                KC_TRNS,            KC_TRNS,
                                              KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /*
     * ┌──────┬───┬───┬───┬───┬───┬───┐                     ┌───┬───┬───┬───┬───┬───┬──────┐
     * │      │F1 │F2 │F3 │F4 │F5 │   │                     │   │ F6│ F7│ F8│ F9│F10│  F11 │
     * ├──────┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼──────┤
     * │      │   │   │   │   │   │   │                     │   │   │ 7 │ 8 │ 9 │   │  F12 │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │      │   │   │   │   │   ├───┤                     ├───┤   │ 4 │ 5 │ 6 │   │      │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │      │   │   │   │   │   │   │                     │   │   │ 1 │ 2 │ 3 │   │ N.LCK│
     * └──┬───┼───┼───┼───┼───┼───┴───┘ ┌───┬───┐ ┌───┬───┐ └───┴───┼───┼───┼───┼───┼───┬──┘
     *    │   │   │   │   │   │         │   │   │ │   │   │         │ 0 │ . │ 0 │   │   │
     *    └───┴───┴───┴───┴───┘     ┌───┼───┼───┤ ├───┼───┼───┐     └───┴───┴───┴───┴───┘
     *                              │   │   │   │ │   │   │   │
     *                              │   │   ├───┤ ├───┤   │   │
     *                              │   │   │   │ │   │   │   │
     *                              └───┴───┴───┘ └───┴───┴───┘
     */
    [_NUMPAD] = LAYOUT_ergodox_pretty_wrapper(
        __________________________FUNC_LEFT__________________________,            __________________________FUNC_RIGHT_________________________,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, _____________________NUMPAD_1_______________________,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              _____________________NUMPAD_2_______________________,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, _____________________NUMPAD_3_______________________,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       _____________________NUMPAD_4_______________________,
                                                     KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
                                                              KC_TRNS,            KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /*
     * ┌──────┬───┬───┬───┬───┬───┬───┐                     ┌───┬───┬───┬───┬───┬───┬──────┐
     * │ ESC  │   │   │   │   │   │   │                     │   │   │   │   │   │   │      │
     * ├──────┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼──────┤
     * │      │   │   │   │   │   │   │                     │   │   │   │   │   │   │      │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │ CTRL │   │   │   │   │   ├───┤                     ├───┤   │   │   │   │   │      │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │      │   │   │   │   │   │   │                     │   │   │   │   │   │   │      │
     * └──┬───┼───┼───┼───┼───┼───┴───┘ ┌───┬───┐ ┌───┬───┐ └───┴───┼───┼───┼───┼───┼───┬──┘
     *    │   │   │   │   │   │         │   │   │ │   │   │         │   │   │   │   │   │
     *    └───┴───┴───┴───┴───┘     ┌───┼───┼───┤ ├───┼───┼───┐     └───┴───┴───┴───┴───┘
     *                              │   │   │   │ │   │   │   │
     *                              │   │   ├───┤ ├───┤   │   │
     *                              │   │   │   │ │   │   │   │
     *                              └───┴───┴───┘ └───┴───┴───┘
     */
    [_GAMING] = LAYOUT_ergodox_pretty_wrapper(
        KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                     KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
                                                              KC_TRNS,            KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /*
     * ┌──────┬───┬───┬───┬───┬───┬───┐                     ┌───┬───┬───┬───┬───┬───┬──────┐
     * │      │   │   │   │   │   │   │                     │   │   │   │   │   │   │      │
     * ├──────┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼──────┤
     * │      │   │   │   │   │   │   │                     │   │   │   │   │   │   │      │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │      │   │   │   │   │   ├───┤                     ├───┤   │   │   │   │   │      │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │      │   │   │   │   │   │   │                     │   │   │   │   │   │   │      │
     * └──┬───┼───┼───┼───┼───┼───┴───┘ ┌───┬───┐ ┌───┬───┐ └───┴───┼───┼───┼───┼───┼───┬──┘
     *    │   │   │   │   │   │         │   │   │ │   │   │         │   │   │   │   │   │
     *    └───┴───┴───┴───┴───┘     ┌───┼───┼───┤ ├───┼───┼───┐     └───┴───┴───┴───┴───┘
     *                              │   │   │   │ │   │   │   │
     *                              │   │   ├───┤ ├───┤   │   │
     *                              │   │   │   │ │   │   │   │
     *                              └───┴───┴───┘ └───┴───┴───┘
     */
      /*
    [10] = LAYOUT_ergodox_pretty_wrapper(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                     KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
                                                              KC_TRNS,            KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
    )
    */
    // clang-format on
};
