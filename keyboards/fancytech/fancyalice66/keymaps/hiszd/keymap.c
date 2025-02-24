/* Copyright 2022 chent7 <https://github.com/chent7>
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
#include "hiszd.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

    /*
     *    ┌───┬───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┬───────┐  ┌───┐ Vol-  Vol+
     *    │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │   │ 7 │ 8 │ 9 │ 0 │ - │ = │Backsp │  │Del│
     *   ┌┴───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘ ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┴┐ └┬──┴┐
     *   │ Tab │ Q │ W │ E │ R │ T │    │ Y │ U │ I │ O │ P │ [ │ ] │  \   │  │PgD│
     *  ┌┴─────┼───┼───┼───┼───┼───┤    └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──────┴┐ └┬──┴┐
     *  │ Caps │ A │ S │ D │ F │ G │     │ H │ J │ K │ L │ ; │ ' │  Enter   │  │PgU│
     * ┌┴──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    └─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┬─┬┴──┼───┘
     * │ Shift  │ Z │ X │ C │ V │ B │      │ N │ M │ , │ . │ / │  Shift  │ │Up │
     * ├─────┬──┴───┼───┴─┬─┴───┴─┬─┴─┐  ┌─┴───┴───┴┬──┴──┬┴───┴───────┬─┴─┼───┼───┐
     * │ Ctl │      │ Alt │       │FN │  │          │ Alt │            │Lft│Dwn│Rgt│
     * └─────┘      └─────┴───────┴───┘  └──────────┴─────┘            └───┴───┴───┘
     */

    [_QWERTY] = LAYOUT_wrapper(
        KC_TILD, __________________NUM_LEFT____________________,       __________________NUM_RIGHT___________________, KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  _______, _______,
        KC_TAB,  __________________QWERTY_L1___________________,       __________________QWERTY_R1___________________, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        MT_CTL,  __________________QWERTY_L2___________________,       __________________QWERTY_R2___________________, KC_QUOT, KC_ENT,           KC_PGDN,
        SC_LSPO, __________________QWERTY_L3___________________,       __________________QWERTY_R3___________________, SC_RSPC,          KC_UP,
      MO(_NUMPAD),       KC_LALT,                 QK_LEAD,    ZZ_SPC,  KC_ENT,                KC_RGUI,                          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_RSTLNE] = LAYOUT_wrapper(
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, __________________RSTLNE_L1___________________,       __________________RSTLNE_R1___________________, _______, _______, _______, _______,
        _______, __________________RSTLNE_L2___________________,       __________________RSTLNE_R2___________________, _______, _______,          _______,
        _______, __________________RSTLNE_L3___________________,       __________________RSTLNE_R3___________________, _______,          _______,
	    _______,          _______,                  _______,    _______, _______,               _______,                          _______, _______, _______
    ),

    [_NUMPAD] = LAYOUT_wrapper(
        QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,          _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,          KC_END,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,          TG_RST,
	    _______,          _______,                  _______,    _______, _______,               _______,                        WSPL,   TG_GAM, WSPR
    ),

    [_GAMING] = LAYOUT_wrapper(
        KC_ESC,  _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,          _______,
	    _______,          _______, _______,                   _______, _______,                 _______,                       _______, _______, _______
    )

    /*
     *    ┌───┬───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┬───────┐  ┌───┐ Vol-  Vol+
     *    │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │   │ 7 │ 8 │ 9 │ 0 │ - │ = │Backsp │  │Del│
     *   ┌┴───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘ ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┴┐ └┬──┴┐
     *   │ Tab │ Q │ W │ E │ R │ T │    │ Y │ U │ I │ O │ P │ [ │ ] │  \   │  │PgD│
     *  ┌┴─────┼───┼───┼───┼───┼───┤    └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──────┴┐ └┬──┴┐
     *  │ Caps │ A │ S │ D │ F │ G │     │ H │ J │ K │ L │ ; │ ' │  Enter   │  │PgU│
     * ┌┴──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    └─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┬─┬┴──┼───┘
     * │ Shift  │ Z │ X │ C │ V │ B │      │ N │ M │ , │ . │ / │  Shift  │ │Up │
     * ├─────┬──┴───┼───┴─┬─┴───┴─┬─┴─┐  ┌─┴───┴───┴┬──┴──┬┴───┴───────┬─┴─┼───┼───┐
     * │ Ctl │      │ Alt │       │FN │  │          │ Alt │            │Lft│Dwn│Rgt│
     * └─────┘      └─────┴───────┴───┘  └──────────┴─────┘            └───┴───┴───┘
     */
/*
    [] = LAYOUT_wrapper(
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,          _______,
	    _______,          _______, _______,                   _______, _______,                   _______,                   _______, _______, _______
    )
*/
};
