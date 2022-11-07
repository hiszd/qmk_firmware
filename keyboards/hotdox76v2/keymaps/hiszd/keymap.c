// Copyright 2021 JasonRen(biu)
// Copyright 2022 Drashna Jael're (@Drashna Jael're)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "hiszd.h"

#define _QWERTY 0
#define _RSTLNE 1
#define _NUM 2
#define _GAMING 3

enum custom_keycodes {
    WSPL = SAFE_RANGE,
    WSPR,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case WSPL:
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(KC_LCTL));
          SEND_STRING(SS_DOWN(KC_LGUI));
          SEND_STRING(SS_TAP(KC_LEFT));
          SEND_STRING(SS_UP(KC_LGUI));
          SEND_STRING(SS_UP(KC_LCTL));
        } else {
        }
        break;
    case WSPR:
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(KC_LCTL));
          SEND_STRING(SS_DOWN(KC_LGUI));
          SEND_STRING(SS_TAP(KC_RGHT));
          SEND_STRING(SS_UP(KC_LGUI));
          SEND_STRING(SS_UP(KC_LCTL));
        } else {
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
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
    [_QWERTY] = LAYOUT_ergodox_pretty(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    WSPL,               WSPR,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_EQL,             KC_TRNS, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        LCTL_T(KC_ESC),KC_A,KC_S,  KC_D,    KC_F,    KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_TRNS,            TG(_GAMING),KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
        KC_GRV,  KC_DEL,  KC_UP,   KC_DOWN, LALT_T(KC_RBRC),                                        KC_LBRC, KC_LEFT, KC_RGHT, KC_TRNS, TT(_NUM),
                                                     KC_HOME, KC_END,             KC_PGUP, KC_PGDN,
                                                              KC_TRNS,            KC_CAPS,
                                            KC_SPC,  KC_UNDS, KC_LGUI,            TG(_RSTLNE),KC_BSPC,KC_ENT
    )
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
    [_RSTLNE] = LAYOUT_ergodox_pretty(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_Q,    KC_W,    KC_D,    KC_F,    KC_Z,    KC_SCLN,            KC_TRNS, KC_SCLN, KC_U,    KC_K,    KC_Y,    KC_P,    KC_TRNS,
        KC_TRNS, KC_A,    KC_S,    KC_E,    KC_R,    KC_L,                                 KC_H,    KC_N,    KC_I,    KC_O,    KC_T,    KC_TRNS,
        KC_TRNS, KC_G,    KC_X,    KC_C,    KC_V,    KC_SLSH, KC_TRNS,            KC_TRNS, KC_B,    KC_J,    KC_M,    KC_COMM, KC_DOT,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                     KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
                                                              KC_TRNS,            KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
    )
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
    [_NUM] = LAYOUT_ergodox_pretty(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,            KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_TRNS, KC_F12,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_TRNS, KC_NUM,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                KC_P0,   KC_DOT,  KC_P0,   KC_TRNS, KC_TRNS,
                                                     KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
                                                              KC_TRNS,            KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
    )
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
    [_GAMING] = LAYOUT_ergodox_pretty(
        KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                     KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
                                                              KC_TRNS,            KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
    )
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
    [10] = LAYOUT_ergodox_pretty(
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
};
