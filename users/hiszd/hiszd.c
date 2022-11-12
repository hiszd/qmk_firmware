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
    layer_state_set_user(layer_state);

    init = 1;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (IS_LAYER_ON_STATE(state, _RSTLNE)) {
        user_config.rstlne_enable = 1;
        eeconfig_update_user(user_config.raw);
    } else if(IS_LAYER_OFF_STATE(state, _RSTLNE) && init) {
        user_config.rstlne_enable = 0;
        eeconfig_update_user(user_config.raw);
    }

    return state;
};

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 0;
  user_config.rstlne_enable = 0;
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
};
