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
          SEND_STRING(SS_DOWN(KC_LCTL));
          SEND_STRING(SS_DOWN(KC_LGUI));
          SEND_STRING(SS_TAP(KC_LEFT));
          SEND_STRING(SS_UP(KC_LGUI));
          SEND_STRING(SS_UP(KC_LCTL));
        } else {
        }
        break;
    case WSPR:
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(KC_LCTL));
          SEND_STRING(SS_DOWN(KC_LGUI));
          SEND_STRING(SS_TAP(KC_RGHT));
          SEND_STRING(SS_UP(KC_LGUI));
          SEND_STRING(SS_UP(KC_LCTL));
        } else {
        }
        break;
    }

    return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
}
