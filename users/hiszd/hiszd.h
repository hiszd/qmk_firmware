/* Copyright 2019 @ninjonas
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
#pragma once
#include <stdint.h>
#include "../../quantum/quantum.h"
#include "matrix_scan.h"

#ifdef SPLIT_KEYBOARD
#    include "transport_sync.h"
#endif /* SPLIT_KEYBOARD */

#ifdef RAW_ENABLE
#    include "raw_hid.h"
#    include "hiszd_hid.h"
#endif // RAW_ENABLE

#ifdef OLED_ENABLE
#    define NOIZ_LOGO
#    include "oled/oled_stuff.h"
#endif

#include "process_records.h"

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#    include "rgb_mat.h"
#endif // defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)

#ifdef TAP_DANCE_ENABLE
// #    include "tap_dances.h"
#endif

#if defined(KEYBOARD_lily58_rev1) & defined(PROTOCOL_LUFA)
#    include "lufa.h"
#    include "split_util.h"
#endif

#ifdef ENCODER_ENABLE
bool     left_encoder_rotated;
bool     right_encoder_rotated;
uint16_t encoder_rotated_timer;
#endif

// #define SPLIT_TRANSACTION_IDS_USER HISZD_SYNC_LIGHTS

#define _QWERTY 0
#define _RSTLNE 1
#define _NUMPAD 2
#define _GAMING 3

// Shortcut Keys
#define K_LOCK LGUI(LCTL(KC_Q)) // Locks screen on MacOS

// Layer Keys
#define TT_NUM TT(_NUMPAD)
#define TG_GAM TG(_GAMING)
#define TG_RST TG(_RSTLNE)

// Mod-Tap Keys
#define MT_CTL MT(MOD_LCTL, KC_ESC)

// Layout blocks
#define __________________QWERTY_L1___________________ KC_Q, KC_W, KC_E, KC_R, KC_T
#define __________________QWERTY_L2___________________ KC_A, KC_S, KC_D, KC_F, KC_G
#define __________________QWERTY_L3___________________ KC_Z, KC_X, KC_C, KC_V, KC_B

#define __________________QWERTY_R1___________________ KC_Y, KC_U, KC_I, KC_O, KC_P
#define __________________QWERTY_R2___________________ KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define __________________QWERTY_R3___________________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH

#define __________________RSTLNE_L1___________________ KC_Q, KC_W, KC_D, KC_F, KC_Z
#define __________________RSTLNE_L2___________________ KC_A, KC_S, KC_E, KC_R, KC_T
#define __________________RSTLNE_L3___________________ KC_G, KC_X, KC_C, KC_V, KC_SLSH

#define __________________RSTLNE_R1___________________ KC_SCLN, KC_U, KC_K, KC_L, KC_P
#define __________________RSTLNE_R2___________________ KC_H, KC_N, KC_I, KC_O, KC_Y
#define __________________RSTLNE_R3___________________ KC_B, KC_J, KC_M, KC_COMM, KC_DOT

#define __________________NUM_LEFT____________________ KC_1, KC_2, KC_3, KC_4, KC_5
#define __________________NUM_RIGHT___________________ KC_6, KC_7, KC_8, KC_9, KC_0

#define __________________________FUNC_LEFT__________________________ KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS
#define __________________________FUNC_RIGHT_________________________ KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11

#define _____________________NUMPAD_1_______________________ KC_TRNS, KC_P7, KC_P8, KC_P9, KC_TRNS, KC_F12
#define _____________________NUMPAD_2_______________________ KC_TRNS, KC_P4, KC_P5, KC_P6, KC_TRNS, RESET
#define _____________________NUMPAD_3_______________________ KC_TRNS, KC_P1, KC_P2, KC_P3, KC_TRNS, KC_NUM
#define _____________________NUMPAD_4_______________________ KC_P0, KC_DOT, KC_P0, KC_TRNS, KC_TRNS

#define _____________MOD_LEFT_____________ KC_GRV, KC_DEL, KC_UP, KC_DOWN, LALT_T(KC_RBRC)
#define _____________MOD_RIGHT____________ KC_LBRC, KC_LEFT, KC_RGHT, TG_RST, TT(_NUMPAD)

// Layout wrappers
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
// #define LAYOUT_ergodox_wrapper(...) LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...) LAYOUT_ergodox_pretty(__VA_ARGS__)
