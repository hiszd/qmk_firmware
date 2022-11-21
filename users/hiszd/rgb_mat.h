#include "hiszd.h"
#include <stdint.h>

typedef struct _leds {
    uint8_t led[86];
} leds_t;

leds_t rgleds;

typedef struct _leddat {
    uint8_t led[8];
} leddat_t;

void hiszd_matrix_set_color(leddat_t, uint8_t, uint8_t, uint8_t);
void hiszd_matrix_set_color_all(uint8_t, uint8_t, uint8_t);
void hiszd_matrix_set_color_zone(uint8_t, uint8_t, uint8_t, uint8_t);
