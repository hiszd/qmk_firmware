#include <stdint.h>
#include "hiszd.h"
#include "oled/oled_stuff.h"
#include "secrets.h"
#include "rgb_mat.h"

__attribute__((weak)) bool matrix_scan_user_keymap(void) {
    return true;
};

#ifdef LEADER_ENABLE
bool leader_on = false;
LEADER_EXTERNS();
#endif /* LEADER_ENABLE */

void matrix_scan_user(void) {
#ifdef LEADER_ENABLE
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_LGUI) {
            reset_keyboard();
        };
        SEQ_TWO_KEYS(KC_P, KC_TAB) {
            send_string(P1);
        };
        SEQ_TWO_KEYS(KC_P, KC_1) {
            send_string(P2);
        };
    };
#endif /* LEADER_ENABLE */

#ifdef OLED_ENABLE
    matrix_scan_oled();
#endif /* OLED_ENABLE */
};

#ifdef LEADER_ENABLE
void leader_start() {
    leader_on = true;
}

void leader_end() {
    leader_on = false;
}
#endif /* LEADER_ENABLE */

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t led[1];
#if defined(LED_LAY1) && defined(LED_LAY1_COL)
    led[0] = LED_LAY1;
    if (layer_state_is(0)) {
        hiszd_matrix_set_color(led, 1, LED_LAY1_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif
#if defined(LED_LAY2) && defined(LED_LAY2_COL)
    led[0] = LED_LAY2;
    if (layer_state_is(1)) {
        hiszd_matrix_set_color(led, 1, LED_LAY2_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif
#if defined(LED_LAY3) && defined(LED_LAY3_COL)
    led[0] = LED_LAY3;
    if (layer_state_is(2)) {
        hiszd_matrix_set_color(led, 1, LED_LAY3_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif
#if defined(LED_LAY4) && defined(LED_LAY4_COL)
    led[0] = LED_LAY4;
    if (layer_state_is(3)) {
        hiszd_matrix_set_color(led, 1, LED_LAY4_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif
#if defined(LED_LAY5) && defined(LED_LAY5_COL)
    led[0] = LED_LAY5;
    if (layer_state_is(4)) {
        hiszd_matrix_set_color(led, 1, LED_LAY5_COL);
    } else {
        hiszd_matrix_set_color(led, 1, 0, 0, 0);
    }
#endif
    return;
}
