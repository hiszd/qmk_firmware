#include "matrix_scan.h"

__attribute__((weak)) bool matrix_scan_user_keymap(void) {
    return true;
};

#ifdef LEADER_ENABLE
bool leader_on = false;

void leader_start_user() {
    leader_on = true;
}

void leader_end_user() {
    leader_on = false;

    if (leader_sequence_one_key(KC_LGUI)) {
        reset_keyboard();
    };

    // Pwords
    if (leader_sequence_two_keys(KC_P, KC_TAB)) {
        send_string(P1);
    };
    if (leader_sequence_two_keys(KC_P, KC_1)) {
        send_string(P2);
    };
    if (leader_sequence_two_keys(KC_P, KC_2)) {
        send_string(P3);
    };
    // Pwords with CR
    if (leader_sequence_three_keys(KC_P, KC_ENT, KC_TAB)) {
        send_string(P1);
        SEND_STRING(SS_TAP(X_ENT));
    };
    if (leader_sequence_three_keys(KC_P, KC_ENT, KC_1)) {
        send_string(P2);
        SEND_STRING(SS_TAP(X_ENT));
    };
    if (leader_sequence_three_keys(KC_P, KC_ENT, KC_2)) {
        send_string(P3);
        SEND_STRING(SS_TAP(X_ENT));
    };
    // Custom Keycodes and functionality
    if (leader_sequence_one_key(ZZ_UNWN)) {
        if (unwn_on) {
            unwn_on = false;
        } else {
            unwn_on = true;
        }
    }
    if (leader_sequence_one_key(ZZ_UNDS)) {
        if (unds_unds_on) {
            unds_dash_on = true;
            unds_unds_on = false;
        } else if (unds_dash_on) {
            unds_dash_on = false;
            unds_unds_on = true;
        }
    };
    if (leader_sequence_one_key(QK_LEAD)) {
        spc_unds_on = false;
        spc_dash_on = false;
    };
    if (leader_sequence_one_key(ZZ_SPC)) {
        spc_unds_on = true;
        spc_dash_on = false;
    };
    if (leader_sequence_one_key(KC_ENT)) {
        spc_unds_on = false;
        spc_dash_on = true;
    };
}
#endif /* LEADER_ENABLE */

// void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {}
