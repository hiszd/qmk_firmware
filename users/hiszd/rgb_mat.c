#include "rgb_mat.h"

void hiszd_matrix_set_color(uint8_t *leds, uint8_t ledslen, uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t index = 0; index < ledslen; index++) {
#ifdef SPLIT_KEYBOARD
        uint8_t ledsplit[2] = RGB_MATRIX_SPLIT;
        if (leds[index] >= ledsplit[1] && leds[index] < DRIVER_LED_TOTAL) {
            m2s_overall.led[leds[index] - 43] = (rgb_led){r : red, g : green, b : blue};
        } else {
#endif /* SPLIT_KEYBOARD */
// TODO will only work on matrix keyboards right now
#ifdef RGB_MATRIX_ENABLE
            rgb_matrix_set_color(leds[index], red, green, blue);
#endif /* RGB_MATRIX_ENABLE */
#ifdef RGBLIGHT_ENABLE
            rgblight_setrgb_at(red, green, blue, leds[index]);
#endif /* RGBLIGHT_ENABLE */
#ifdef SPLIT_KEYBOARD
        }
#endif /* SPLIT_KEYBOARD */
    }
#ifdef SPLIT_KEYBOARD
    m2s_go = true;
#endif /* SPLIT_KEYBOARD */
}

void hiszd_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
#ifdef CONSOLE_ENABLE
    uprintf("Setting all colors to: %u, %u, %u\n", red, green, blue);
#endif /* CONSOLE_ENABLE */
#ifdef SPLIT_KEYBOARD
    uint8_t ledsplit[2] = RGB_MATRIX_SPLIT;
    for (uint8_t i = 0; i < ledsplit[1]; i++) {
        m2s_overall.led[i] = (rgb_led){r : red, g : green, b : blue};
        m2s_go             = true;
    }
#endif /* SPLIT_KEYBOARD */
// TODO will only work on matrix keyboards right now
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(red, green, blue);
#endif /* RGB_MATRIX_ENABLE */
#ifdef RGBLIGHT_ENABLE
    rgblight_setrgb_range(red, green, blue, 0, RGBLED_NUM);
#endif /* RGBLIGHT_ENABLE */
}
