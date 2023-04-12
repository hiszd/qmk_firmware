/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_RSTLNE] = LAYOUT_ansi_69_wrapper(
        KC_GRV,  __________________NUM_LEFT____________________,       __________________NUM_RIGHT___________________,   KC_MINS,  KC_EQL,  KC_RGUI, KC_DEL,
        KC_TAB,  __________________RSTLNE_L1___________________,       __________________RSTLNE_R1___________________,   KC_LBRC,  KC_RBRC, KC_BSLS, KC_PGUP,
        MT_CTL,  __________________RSTLNE_L2___________________,       __________________RSTLNE_R2___________________,   KC_QUOT,  KC_BSPC,          KC_PGDN,
        SC_LSPO, __________________RSTLNE_L3___________________, KC_B, __________________RSTLNE_R3___________________,   SC_RSPC,           KC_UP,
        KC_LCTL, KC_LALT,  KC_LGUI,           ZZ_SPC,           QK_LEAD,  KC_RGUI,          KC_ENT,            MO(_NUMPAD),        KC_LEFT, KC_DOWN, KC_RGHT),

    [_QWERTY] = LAYOUT_ansi_69_wrapper(
        KC_GRV,  __________________NUM_LEFT____________________,       __________________NUM_RIGHT___________________,   KC_MINS,  KC_EQL,  KC_RGUI, KC_DEL,
        KC_TAB,  __________________QWERTY_L1___________________,       __________________QWERTY_R1___________________,   KC_LBRC,  KC_RBRC, KC_BSLS, KC_PGUP,
        MT_CTL,  __________________QWERTY_L2___________________,       __________________QWERTY_R2___________________,   KC_QUOT,  KC_BSPC,          KC_PGDN,
        SC_LSPO, __________________QWERTY_L3___________________, KC_B, __________________QWERTY_R3___________________,   SC_RSPC,           KC_UP,
        KC_LCTL, KC_LALT,  KC_LGUI,           ZZ_SPC,           QK_LEAD,  KC_RGUI,          KC_ENT,            MO(_NUMPAD),        KC_LEFT, KC_DOWN, KC_RGHT),

    [_NUMPAD] = LAYOUT_ansi_69_wrapper(
        QK_BOOT,   KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,          _______,
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          KC_HOME,
        _______, _______,  _______,  _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______,          KC_END,
        _______,           _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______, TG_RST,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            WSPL,    TG_GAM,  WSPR),

    [_GAMING] = LAYOUT_ansi_69_wrapper(
        KC_ESC,  _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        KC_LCTL, _______,  _______,  _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______)

    // [_FN1] = LAYOUT_ansi_69(
    //     KC_GRV,  KC_BRID,  KC_BRIU,  KC_NO,   KC_NO,   RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          _______,
    //     RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    //     _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    //     _______,           _______,  _______, _______, _______, _______,  _______, NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
    //     _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),
    //
    // [_FN2] = LAYOUT_ansi_69(
    //     KC_GRV,  KC_BRID,  KC_BRIU,  KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          _______,
    //     RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    //     _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    //     _______,           _______,  _______, _______, _______, _______,  _______, NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
    //     _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),
    //
    // [_FN3] = LAYOUT_ansi_69(
    //     KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,          _______,
    //     RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    //     _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    //     _______,           _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
    //     _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______)
};
