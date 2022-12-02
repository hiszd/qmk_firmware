#pragma once
#include "hiszd.h"

enum custom_keycodes {
    // Custom Macros
    WSPL = SAFE_RANGE,
    WSPR,
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
