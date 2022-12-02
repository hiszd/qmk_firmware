#include <stdint.h>
#include <stdbool.h>
#include "../../quantum/quantum.h"
#ifdef SPLIT_KEYBOARD
#    include "transport_sync.h"
#endif /* SPLIT_KEYBOARD */

void hiszd_matrix_set_color(uint8_t*, uint8_t, uint8_t, uint8_t, uint8_t);
void hiszd_matrix_set_color_all(uint8_t, uint8_t, uint8_t);
// void hiszd_matrix_set_color_zone(uint8_t, uint8_t, uint8_t, uint8_t);
