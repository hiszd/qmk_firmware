#include "../../quantum/quantum.h"
#include "secrets.h"
#include "rgb_mat.h"
#include <stdint.h>

#pragma once

#ifdef LEADER_ENABLE
extern bool leader_on;
#endif /* LEADER_ENABLE */

void matrix_scan_aux(void);

bool matrix_scan_user_keymap(void);

void rgb_matrix_indicators_advanced_user(uint8_t, uint8_t);
