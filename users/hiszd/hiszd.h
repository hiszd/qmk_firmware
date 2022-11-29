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
#include "process_records.h"
#include "raw_hid.h"

#ifdef OLED_ENABLE
#    define NOIZ_LOGO
#    include "oled/noiz_logo.h"
#    include "oled/drashna_font.h"
#endif

#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
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
#define K_LOCK LGUI(LCTL(KC_Q))       // Locks screen on MacOS
#define K_CSCN LGUI(LCTL(LSFT(KC_4))) // Copy a portion of the screen to the clipboard
#define K_CPRF LGUI(LSFT(KC_M))       //  Cmd + Shift + M. Used for switching Google Chrome profiles
#define K_MDSH LSFT(LALT(KC_MINS))

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
#define __________________RSTLNE_L2___________________ KC_A, KC_S, KC_E, KC_R, KC_L
#define __________________RSTLNE_L3___________________ KC_G, KC_X, KC_C, KC_V, KC_SLSH

#define __________________RSTLNE_R1___________________ KC_SCLN, KC_U, KC_K, KC_Y, KC_P
#define __________________RSTLNE_R2___________________ KC_H, KC_N, KC_I, KC_O, KC_T
#define __________________RSTLNE_R3___________________ KC_B, KC_J, KC_M, KC_COMM, KC_DOT

#define __________________NUM_LEFT____________________ KC_1, KC_2, KC_3, KC_4, KC_5
#define __________________NUM_RIGHT___________________ KC_6, KC_7, KC_8, KC_9, KC_0

#define __________________________FUNC_LEFT__________________________ KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS
#define __________________________FUNC_RIGHT_________________________ KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11

#define _____________________LOWER_L1_______________________ M_XXX2, M_XXX3, _________MEDIA_1_________, K_CSCN
#define _____________________LOWER_L2_______________________ M_XXX4, M_XXX5, _________MEDIA_2_________, XXXXXXX
#define _____________________LOWER_L3_______________________ KC_LSFT, M_SHFT, _________MEDIA_3_________, T_LBRC

#define _____________________LOWER_R1_______________________ _______________NAV_1______________, XXXXXXX, K_MDSH
#define _____________________LOWER_R2_______________________ _______________NAV_2______________, K_LOCK, XXXXXXX
#define _____________________LOWER_R3_______________________ T_RBRC, KC_M, M_TERM, M_CODE, M_XXX1, M_PYNV

#define _____________________ADJUST_L1______________________ M_MAKE, EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#    define _____________________ADJUST_L2______________________ M_VRSN, M_MALL, RGB_SPI, RGB_SAI, RGB_HUI, RGB_VAI
#    define _____________________ADJUST_L3______________________ M_FLSH, XXXXXXX, RGB_SPD, RGB_SAD, RGB_HUD, RGB_VAD
#else
#    define _____________________ADJUST_L2______________________ M_VRSN, M_MALL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#    define _____________________ADJUST_L3______________________ M_FLSH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#endif

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#    define _____________________ADJUST_R1______________________ RGB_TOG, XXXXXXX, XXXXXXX, COLEMAK, DVORAK, QWERTY
#    define _____________________ADJUST_R3______________________ RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#else
#    define _____________________ADJUST_R1______________________ XXXXXXX, XXXXXXX, XXXXXXX, COLEMAK, DVORAK, QWERTY
#    define _____________________ADJUST_R3______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#endif
#define _____________________ADJUST_R2______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________NUMPAD_1_______________________ KC_TRNS, KC_P7, KC_P8, KC_P9, KC_TRNS, KC_F12
#define _____________________NUMPAD_2_______________________ KC_TRNS, KC_P4, KC_P5, KC_P6, KC_TRNS, KC_TRNS
#define _____________________NUMPAD_3_______________________ KC_TRNS, KC_P1, KC_P2, KC_P3, KC_TRNS, KC_NUM
#define _____________________NUMPAD_4_______________________ KC_P0, KC_DOT, KC_P0, KC_TRNS, KC_TRNS

#define _____________MOD_LEFT_____________ KC_GRV, KC_DEL, KC_UP, KC_DOWN, LALT_T(KC_RBRC)
#define _____________MOD_RIGHT____________ KC_LBRC, KC_LEFT, KC_RGHT, KC_TRNS, TT(_NUMPAD)

#define _________MEDIA_1_________ KC_BRIU, KC_MPLY, KC_MUTE
#define _________MEDIA_2_________ KC_BRID, KC_MFFD, KC__VOLUP
#define _________MEDIA_3_________ XXXXXXX, KC_MRWD, KC__VOLDOWN

// Layout wrappers
// #define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
// #define LAYOUT_ergodox_wrapper(...) LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...) LAYOUT_ergodox_pretty(__VA_ARGS__)
