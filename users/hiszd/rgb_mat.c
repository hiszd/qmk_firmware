#include "rgb_mat.h"
#include <stdbool.h>

#ifdef SPLIT_ENABLE
#    include "transport_sync.h"
#endif /* SPLIT_ENABLE */

void hiszd_matrix_set_color(uint8_t *leds, uint8_t ledslen, uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t index = 0; index < ledslen; index++) {
#ifdef SPLIT_ENABLE
        if (leds[index] >= RGB_MATRIX_SPLIT[1] && leds[index] < DRIVER_LED_TOTAL) {
            m2s_overall.led[leds[index] - 43] = (rgb_led){r : red, g : green, b : blue};
            hasplit                           = true;
        } else {
#endif /* SPLIT_ENABLE */
// TODO will only work on matrix keyboards right now
#ifdef RGB_MATRIX_ENABLE
            rgb_matrix_set_color(leds[index], red, green, blue);
#endif /* RGB_MATRIX_ENABLE */
#ifdef SPLIT_ENABLE
        }
#endif /* SPLIT_ENABLE */
    }
#ifdef SPLIT_ENABLE
    m2s_go = true;
#endif /* SPLIT_ENABLE */
}

void hiszd_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
#ifdef SPLIT_ENABLE
    for (uint8_t i = 0; i < RGB_MATRIX_SPLIT[1]; i++) {
        m2s_overall.led[i] = (rgb_led){r : red, g : green, b : blue};
        m2s_go             = true;
    }
#endif /* SPLIT_ENABLE */
// TODO will only work on matrix keyboards right now
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(red, green, blue);
#endif /* RGB_MATRIX_ENABLE */
}
