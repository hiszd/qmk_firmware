#pragma once
#include "hiszd.h"

enum custom_keycodes {
  // Custom Macros
  WSPL = SAFE_RANGE,
  WSPR,
  M_XXX1,
  M_XXX2,
  M_XXX3,
  M_XXX4,
  M_XXX5,
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
