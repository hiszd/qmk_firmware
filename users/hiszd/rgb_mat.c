#include "rgb_mat.h"
#include <stdbool.h>
#include <stdint.h>
#include "transport_sync.h"

void hiszd_matrix_set_color(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index > 42) {
        m2s_overall.led[index].r = red;
        m2s_overall.led[index].g = green;
        m2s_overall.led[index].b = blue;
        m2s_go                   = true;
    } else {
        rgb_matrix_set_color(index, red, green, blue);
    }
}
