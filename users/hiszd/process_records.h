#include "../../quantum/quantum.h"

#pragma once

enum custom_keycodes {
    // Custom Macros
    WSPL = SAFE_RANGE,
    WSPR,
};

bool process_record_aux(uint16_t, keyrecord_t *);

bool process_record_secrets(uint16_t, keyrecord_t *);
bool process_record_keymap(uint16_t, keyrecord_t *);
