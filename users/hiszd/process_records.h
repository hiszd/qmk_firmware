#include "../../quantum/quantum.h"

#pragma once

enum custom_keycodes {
    // Custom Macros
    WSPL    = SAFE_RANGE,
    WSPR    = SAFE_RANGE + 1,
    ZZ_SPC  = SAFE_RANGE + 2,
    ZZ_UNDS = SAFE_RANGE + 3,
    ZZ_UNWN = SAFE_RANGE + 4,
};

extern bool spc_unds_on;
extern bool spc_dash_on;

extern bool unds_unds_on;
extern bool unds_dash_on;

extern bool unwn_on;

bool process_record_aux(uint16_t, keyrecord_t *);

bool process_record_secrets(uint16_t, keyrecord_t *);
bool process_record_keymap(uint16_t, keyrecord_t *);
