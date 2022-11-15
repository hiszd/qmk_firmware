#include "raw_hid.h"
#include "rgblight.h"
#include "hiszd.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *reqtype = &(data[0]);
    uint8_t *command = &(data[1]);
    uint8_t *data1   = &(data[2]);
    uint8_t *data2   = &(data[3]);
    uint8_t *data3   = &(data[4]);
    uint8_t *data4   = &(data[5]);
    switch (*reqtype) {
        // layer functions
        case 0:
            switch (*command) {
                case 0:
                    layer_off(*data1);
                    break;
                case 1:
                    layer_on(*data1);
                    break;
            }
        // lighting functions
        case 1:
            // rgblight_set_effect_range(pos, num);
            switch (*command) {
                case 0:
                    rgblight_setrgb_at(*data1, *data2, *data3, *data4);
                    break;
                case 1:
                    rgb_matrix_set_color_all(*data1, *data2, *data3);
                    break;
            }
        case 99:
            reset_keyboard();
            break;
    }
}
