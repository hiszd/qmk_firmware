#include "hiszd.h"
#include <stdint.h>

typedef struct _leds {
    uint8_t led[86];
} leds_t;

leds_t rgleds;

void hiszd_matrix_set_color(uint8_t*, uint8_t, uint8_t, uint8_t, uint8_t);
void hiszd_matrix_set_color_all(uint8_t, uint8_t, uint8_t);
void hiszd_matrix_set_color_zone(uint8_t, uint8_t, uint8_t, uint8_t);
