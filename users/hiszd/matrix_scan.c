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
        SEQ_TWO_KEYS(KC_P, KC_2) {
            send_string(P3);
        };
        SEQ_THREE_KEYS(KC_P, KC_ENT, KC_TAB) {
            send_string(P1);
            SEND_STRING(SS_TAP(X_ENT));
        };
        SEQ_THREE_KEYS(KC_P, KC_ENT, KC_1) {
            send_string(P2);
            SEND_STRING(SS_TAP(X_ENT));
        };
        SEQ_THREE_KEYS(KC_P, KC_ENT, KC_2) {
            send_string(P3);
            SEND_STRING(SS_TAP(X_ENT));
        };
        if (IS_LAYER_ON(1)) {
            SEQ_ONE_KEY(KC_O) {
                SEND_STRING(SS_TAP(X_RIGHT));
            };
        } else {
            SEQ_ONE_KEY(KC_L) {
                SEND_STRING(SS_TAP(X_RIGHT));
            };
        };
        SEQ_ONE_KEY(ZZ_UNDS) {
            if (unds_unds_on) {
                unds_dash_on = true;
                unds_unds_on = false;
            } else if (unds_dash_on) {
                unds_dash_on = false;
                unds_unds_on = true;
            }
        };
        SEQ_ONE_KEY(KC_LEAD) {
            spc_unds_on = false;
            spc_dash_on = false;
        };
        SEQ_ONE_KEY(ZZ_SPC) {
            spc_unds_on = true;
            spc_dash_on = false;
        };
        SEQ_ONE_KEY(KC_ENT) {
            spc_unds_on = false;
            spc_dash_on = true;
        };
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
