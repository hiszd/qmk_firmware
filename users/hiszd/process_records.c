#include "hiszd.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
    }

    return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
}
