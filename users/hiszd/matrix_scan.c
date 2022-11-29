#include <stdint.h>
#include "hiszd.h"
#include "secrets.h"
#include "rgb_mat.h"

bool leader_on = false;

__attribute__((weak)) bool matrix_scan_user_keymap(void) {
    return true;
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
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
};

void leader_start() {
    leader_on = true;
}

void leader_end() {
    leader_on = false;
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    leddat_t LED = {{255, 255, 255, 255, 255, 255, 255, 255}};
#if defined(LED_LAY1) && defined(LED_LAY1_COL)
    LED.led[0] = LED_LAY1;
    if (layer_state_is(0)) {
        hiszd_matrix_set_color(LED, LED_LAY1_COL);
    } else {
        hiszd_matrix_set_color(LED, 0, 0, 0);
    }
#endif
#if defined(LED_LAY2) && defined(LED_LAY2_COL)
    LED.led[0] = LED_LAY2;
    if (layer_state_is(1)) {
        hiszd_matrix_set_color(LED, LED_LAY2_COL);
    } else {
        hiszd_matrix_set_color(LED, 0, 0, 0);
    }
#endif
#if defined(LED_LAY3) && defined(LED_LAY3_COL)
    LED.led[0] = LED_LAY3;
    if (layer_state_is(2)) {
        hiszd_matrix_set_color(LED, LED_LAY3_COL);
    } else {
        hiszd_matrix_set_color(LED, 0, 0, 0);
    }
#endif
#if defined(LED_LAY4) && defined(LED_LAY4_COL)
    LED.led[0] = LED_LAY4;
    if (layer_state_is(3)) {
        hiszd_matrix_set_color(LED, LED_LAY4_COL);
    } else {
        hiszd_matrix_set_color(LED, 0, 0, 0);
    }
#endif
#if defined(LED_LAY5) && defined(LED_LAY5_COL)
    LED.led[0] = LED_LAY5;
    if (layer_state_is(4)) {
        hiszd_matrix_set_color(LED, LED_LAY5_COL);
    } else {
        hiszd_matrix_set_color(LED, 0, 0, 0);
    }
#endif
    return;
}
