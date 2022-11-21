#include "rgb_mat.h"
#include <stdbool.h>
#include "transport_sync.h"

void hiszd_matrix_set_color(leddat_t leds, uint8_t red, uint8_t green, uint8_t blue) {
    bool hasplit;
    for (int index = 0; index < 8; index++) {
        if (leds.led[index] >= 43 && leds.led[index] < DRIVER_LED_TOTAL) {
            m2s_overall.led[leds.led[index] - 43] = (rgb_led){r : red, g : green, b : blue};
            hasplit                               = true;
        } else {
            rgb_matrix_set_color(leds.led[index], red, green, blue);
        }
    }
    if (hasplit) {
        m2s_go = true;
    }
}

void hiszd_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = 0; i < 43; i++) {
        m2s_overall.led[i] = (rgb_led){r : red, g : green, b : blue};
        m2s_go             = true;
    }
    rgb_matrix_set_color_all(red, green, blue);
}
