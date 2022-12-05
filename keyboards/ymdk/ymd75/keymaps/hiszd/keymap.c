/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2018 Wayne K Jones <github.com/WarmCatUK>

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
#include "hiszd.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /* 0: Main Layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │CAPS │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │PRSCR│ DEL │ FN  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
     * │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │ BACKSPACE │HOME │
     * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
     * │  ESC   │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │   \    │ END │
     * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
     * │  CTL    │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │    RETURN   │PG_UP│
     * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────┬─────┼─────┤
     * │   LSHIFT(  │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │  RSHIFT) │ UP  │PG_DN│
     * ├──────┬─────┴┬────┴─┬───┴─────┴─────┴─────┴─────┴─────┴────┬┴─────┴─┬───┴────┬─────┼─────┼─────┤
     * │LCTRL │L_GUI │L_ALT │                SPACE                 │ R_ALT  │ R_CTRL │LEFT │DOWN │RIGHT│
     * └──────┴──────┴──────┴──────────────────────────────────────┴────────┴────────┴─────┴─────┴─────┘
     */
    [_QWERTY] = LAYOUT_wrapper(
        KC_CAPS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   TG_RST,   KC_LEAD,   KC_DEL,
        KC_GRV,   __________________NUM_LEFT____________________,   __________________NUM_RIGHT___________________,   KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
        KC_TAB,   __________________QWERTY_L1___________________,   __________________QWERTY_R1___________________,   KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP,
        MT_CTL,   __________________QWERTY_L2___________________,   __________________QWERTY_R2___________________,   KC_QUOT,       KC_ENT,                  KC_PGDN,
        KC_LSPO,  __________________QWERTY_L3___________________,   __________________QWERTY_R3___________________,   KC_RSPC,                      KC_UP,    KC_END,
        KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 KC_NO,    KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    /* _RSTLNE: Layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │           │     │
     * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
     * │        │     │     │     │     │     │     │     │     │     │     │     │     │        │     │
     * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
     * │         │     │     │     │     │     │     │     │     │     │     │     │             │     │
     * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────┬─────┼─────┤
     * │            │     │     │     │     │     │     │     │     │     │     │          │     │     │
     * ├──────┬─────┴┬────┴─┬───┴─────┴─────┴─────┴─────┴─────┴────┬┴─────┴─┬───┴────┬─────┼─────┼─────┤
     * │      │      │      │                                      │        │        │     │     │     │
     * └──────┴──────┴──────┴──────────────────────────────────────┴────────┴────────┴─────┴─────┴─────┘
     */
    [_RSTLNE] = LAYOUT_wrapper(
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  __________________RSTLNE_L1___________________,   __________________RSTLNE_R1___________________,   KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  __________________RSTLNE_L2___________________,   __________________RSTLNE_R2___________________,   KC_TRNS,       KC_TRNS,                 KC_TRNS,
        KC_TRNS,  __________________RSTLNE_L3___________________,   __________________RSTLNE_R3___________________,   KC_TRNS,                      KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS
    ),

    /* _GAMING: Layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │           │     │
     * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
     * │        │     │     │     │     │     │     │     │     │     │     │     │     │        │     │
     * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
     * │         │     │     │     │     │     │     │     │     │     │     │     │             │     │
     * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────┬─────┼─────┤
     * │            │     │     │     │     │     │     │     │     │     │     │          │     │     │
     * ├──────┬─────┴┬────┴─┬───┴─────┴─────┴─────┴─────┴─────┴────┬┴─────┴─┬───┴────┬─────┼─────┼─────┤
     * │      │      │      │                                      │        │        │     │     │     │
     * └──────┴──────┴──────┴──────────────────────────────────────┴────────┴────────┴─────┴─────┴─────┘
     */
    [_GAMING] = LAYOUT_wrapper(
        KC_ESC,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_LCTL,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_TRNS,                 KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,
        KC_CAPS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS
    )

    /* BLANK: Layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │           │     │
     * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
     * │        │     │     │     │     │     │     │     │     │     │     │     │     │        │     │
     * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
     * │         │     │     │     │     │     │     │     │     │     │     │     │             │     │
     * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────┬─────┼─────┤
     * │            │     │     │     │     │     │     │     │     │     │     │          │     │     │
     * ├──────┬─────┴┬────┴─┬───┴─────┴─────┴─────┴─────┴─────┴────┬┴─────┴─┬───┴────┬─────┼─────┼─────┤
     * │      │      │      │                                      │        │        │     │     │     │
     * └──────┴──────┴──────┴──────────────────────────────────────┴────────┴────────┴─────┴─────┴─────┘
     */
    // [_BLANK] = LAYOUT_wrapper(
    //     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    //     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
    //     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS  ,KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
    //     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_TRNS,                 KC_TRNS,
    //     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,
    //     KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS
    // ),
    // clang-format on
};
