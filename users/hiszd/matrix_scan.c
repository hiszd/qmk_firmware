#include "matrix_scan.h"

__attribute__((weak)) bool matrix_scan_user_keymap(void) {
    return true;
};

#ifdef LEADER_ENABLE
bool leader_on = false;
LEADER_EXTERNS();
#endif /* LEADER_ENABLE */

void matrix_scan_aux(void) {
#ifdef LEADER_ENABLE
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_LGUI) {
            reset_keyboard();
        };
        SEQ_ONE_KEY(KC_RGUI) {
            reset_keyboard();
        };
        SEQ_TWO_KEYS(KC_P, KC_TAB) {
            send_string(P1);
        };
        SEQ_TWO_KEYS(KC_P, KC_1) {
            send_string(P2);
        };
#    ifdef KEYBOARD_fancytech_fancyalice66
        SEQ_ONE_KEY(KC_UP) {
            send_string(TG_RST);
        };
        SEQ_ONE_KEY(KC_DOWN) {
            send_string(TG_GAM);
        };
#    endif
    };
#endif /* LEADER_ENABLE */
};

#ifdef LEADER_ENABLE
void leader_start() {
    leader_on = true;
}

void leader_end() {
    leader_on = false;
}
#endif /* LEADER_ENABLE */

// void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {}
