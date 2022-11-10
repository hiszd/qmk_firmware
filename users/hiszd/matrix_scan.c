#include "hiszd.h"

__attribute__((weak)) bool matrix_scan_user_keymap(void) {
    return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_LGUI) {
      reset_keyboard();
    }
  }
}
