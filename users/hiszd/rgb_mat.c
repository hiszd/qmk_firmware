#include "rgb_mat.h"
#include <stdbool.h>
#include <stdint.h>
#include "transport_sync.h"

void hiszd_matrix_set_color(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= 43) {
        m2s_overall.led[index - 43] = (rgb_led){r : red, g : green, b : blue};
        // m2s_overall.led[index - 43].r = red;
        // m2s_overall.led[index - 43].g = green;
        // m2s_overall.led[index - 43].b = blue;
        m2s_go = true;
    } else {
        rgb_matrix_set_color(index, red, green, blue);
    }
}
