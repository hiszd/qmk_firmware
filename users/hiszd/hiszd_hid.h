#include "../../quantum/quantum.h"
#include "raw_hid.h"
#include <stdint.h>
#include "string.h"
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#    include "rgb_mat.h"
#    include "color.h"
#endif /* defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE) */
#ifdef OLED_ENABLE
#    include "oled/oled_stuff.h"
#endif /* OLED_ENABLE */
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

#ifndef HIDSTRDEF
typedef struct _hidstore_t {
    uint8_t bytes[64];
    uint8_t length;
} hidstore_t;
#    define HIDSTRDEF
#endif /* !HIDSTRDEF */
