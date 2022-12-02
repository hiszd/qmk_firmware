/* Copyright 2022 @hiszd
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
#include "hiszd.h"

typedef union {
    uint32_t raw;
    struct {
        bool rstlne_enable : 1;
    };
} user_config_t;

user_config_t user_config;

bool init = 0;

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif
void keyboard_post_init_user() {
    user_config.raw = eeconfig_read_user();

    if (user_config.rstlne_enable) {
        layer_on(_RSTLNE);
    }

#ifdef SPLIT_KEYBOARD
    keyboard_post_init_transport_sync();
#endif /* SPLIT_KEYBOARD */

#ifdef RGBLIGHT_ENABLE
    // Cycles through the entire hue wheel and resetting to default color
    uint16_t default_hue = rgblight_config.hue;
    rgblight_enable_noeeprom();
    layer_state_set_user(layer_state);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    for (uint16_t i = 255; i > 0; i--) {
        rgblight_sethsv_noeeprom((i + default_hue) % 255, rgblight_config.sat, rgblight_config.val);
        matrix_scan();
        wait_ms(10);
    }
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
    rgb_matrix_set_flags(LED_FLAG_NONE);
#endif
    layer_state_set_user(layer_state);

#ifdef OLED_ENABLE
    keyboard_post_init_oled();
#endif

    init = 1;
}

void housekeeping_task_user(void) {
#ifdef SPLIT_KEYBOARD
    housekeeping_task_rgb();
#    ifdef OLED_ENABLE
    housekeeping_task_oled();
#    endif /* OLED_ENABLE */
#endif     /* SPLIT_KEYBOARD */
    return;
}

void matrix_scan_user(void) {
    matrix_scan_aux();
#ifdef OLED_ENABLE
    matrix_scan_oled();
#endif /* OLED_ENABLE */
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_aux(keycode, record);
#ifdef OLED_ENABLE
    process_record_oled(keycode, record);
#endif /* OLED_ENABLE */
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (IS_LAYER_ON_STATE(state, _RSTLNE)) {
        user_config.rstlne_enable = 1;
        eeconfig_update_user(user_config.raw);
    } else if (IS_LAYER_OFF_STATE(state, _RSTLNE) && init) {
        user_config.rstlne_enable = 0;
        eeconfig_update_user(user_config.raw);
    }

    uint8_t led[1];
#if defined(LED_LAY1) && defined(LED_LAY1_COL)
    led[0] = LED_LAY1;
    if (IS_LAYER_ON_STATE(state, 0)) {
        hiszd_matrix_set_color(led, 1, LED_LAY1_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif
#if defined(LED_LAY2) && defined(LED_LAY2_COL)
    led[0] = LED_LAY2;
    if (IS_LAYER_ON_STATE(state, 1)) {
        hiszd_matrix_set_color(led, 1, LED_LAY2_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif
#if defined(LED_LAY3) && defined(LED_LAY3_COL)
    led[0] = LED_LAY3;
    if (IS_LAYER_ON_STATE(state, 2)) {
        hiszd_matrix_set_color(led, 1, LED_LAY3_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif
#if defined(LED_LAY4) && defined(LED_LAY4_COL)
    led[0] = LED_LAY4;
    if (IS_LAYER_ON_STATE(state, 3)) {
        hiszd_matrix_set_color(led, 1, LED_LAY4_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif
#if defined(LED_LAY5) && defined(LED_LAY5_COL)
    led[0] = LED_LAY5;
    if (IS_LAYER_ON_STATE(state, 4)) {
        hiszd_matrix_set_color(led, 1, LED_LAY5_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif

    return state;
};

void eeconfig_init_user(void) { // EEPROM is getting reset!
    user_config.raw           = 0;
    user_config.rstlne_enable = 0;
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
};
