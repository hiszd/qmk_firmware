// Copyright 2021 JasonRen(biu)
// Copyright 2022 Drashna Jael're (@Drashna Jael're)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define TOG_OLED KC_F13
#define UNC (94 + 0x21)

#if defined(OLED_ENABLE) && defined(ALPA_SYNC)

static const char PROGMEM code_to_name[0xFF] = {
    //   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    UNC, UNC,  UNC, UNC, 'a',  'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', // 0x
    'm', 'n',  'o', 'p', 'q',  'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', // 1x
    '3', '4',  '5', '6', '7',  '8', '9', '0', UNC, UNC, UNC, UNC, UNC, '-', '=', '[', // 2x
    ']', '\\', '#', ';', '\'', '`', ',', '.', '/', UNC, UNC, UNC, UNC, UNC, UNC, UNC, // 3x
    UNC, UNC,  UNC, UNC, UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // 4x
    UNC, UNC,  UNC, UNC, '/',  '*', '-', '+', UNC, '1', '2', '3', '4', '5', '6', '7', // 5x
    '8', '9',  '0', '.', UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // 6x
    UNC, UNC,  UNC, UNC, UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // 7x
    UNC, UNC,  UNC, UNC, UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // 8x
    UNC, UNC,  UNC, UNC, UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // 9x
    UNC, UNC,  UNC, UNC, UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // Ax
    UNC, UNC,  UNC, UNC, UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // Bx
    UNC, UNC,  UNC, UNC, UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // Cx
    UNC, UNC,  UNC, UNC, UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // Dx
    UNC, UNC,  'A', 'W', UNC,  'S', UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, // Ex
    UNC, UNC,  UNC, UNC, UNC,  UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC, UNC       // Fx
};

void render_logo(void);
void render_left_helper_fun(uint8_t, const char *, uint8_t, uint8_t);
void render_right_helper_fun(uint8_t, const char *, uint8_t, uint8_t);

#endif
