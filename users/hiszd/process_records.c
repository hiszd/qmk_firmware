#include "process_records.h"
#include "matrix_scan.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool spc_dash_on = false;
bool spc_unds_on = false;

bool unds_dash_on = false;
bool unds_unds_on = true;

bool unwn_on = false;

bool process_record_aux(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WSPL:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL));
                SEND_STRING(SS_DOWN(X_LGUI));
                SEND_STRING(SS_TAP(X_LEFT));
                SEND_STRING(SS_UP(X_LGUI));
                SEND_STRING(SS_UP(X_LCTL));
            } else {
            }
            break;
        case WSPR:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL));
                SEND_STRING(SS_DOWN(X_LGUI));
                SEND_STRING(SS_TAP(X_RGHT));
                SEND_STRING(SS_UP(X_LGUI));
                SEND_STRING(SS_UP(X_LCTL));
            } else {
            }
            break;
        case ZZ_UNWN:
            if (record->event.pressed) {
                if (!leader_on) {
                    if (unwn_on) {
                        register_code16(KC_UNDS);
                    } else {
                        register_code(KC_RGUI);
                    }
                }
            } else {
                if (!leader_on) {
                    if (unwn_on) {
                        unregister_code16(KC_UNDS);
                    } else {
                        unregister_code(KC_RGUI);
                    }
                }
            }
            break;
        case ZZ_UNDS:
            if (record->event.pressed) {
                if (!leader_on) {
                    if (unds_dash_on) {
                        register_code(KC_MINS);
                    } else if (unds_unds_on) {
                        register_code16(KC_UNDS);
                    }
                }
            } else {
                if (!leader_on) {
                    if (unds_dash_on) {
                        unregister_code(KC_MINS);
                    } else if (unds_unds_on) {
                        unregister_code16(KC_UNDS);
                    }
                }
            }
        case ZZ_SPC:
            if (record->event.pressed) {
                if (!leader_on) {
                    if (spc_dash_on) {
                        register_code(KC_MINS);
                    } else if (spc_unds_on) {
                        register_code16(KC_UNDS);
                    } else {
                        register_code(KC_SPC);
                    }
                }
            } else {
                if (!leader_on) {
                    if (spc_dash_on) {
                        unregister_code(KC_MINS);
                    } else if (spc_unds_on) {
                        unregister_code16(KC_UNDS);
                    } else {
                        unregister_code(KC_SPC);
                    }
                }
            }
        default:
            break;
    }

    return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
}
