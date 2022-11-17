#include "raw_hid.h"
#include <stdint.h>
#include "color.h"
#include "stdint.h"
#include "hiszd.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *reqtype = &(data[0]);
    uint8_t *command = &(data[1]);
    uint8_t *data1   = &(data[2]);
    uint8_t *data2   = &(data[3]);
    uint8_t *data3   = &(data[4]);
    uint8_t *data4   = &(data[5]);
    HSV      hsv     = rgb_matrix_get_hsv();
    uint8_t  dat[RAW_EPSIZE];
    switch (*reqtype) {
        // layer functions
        case 0:
            switch (*command) {
                case 0:
                    layer_off(*data1);
                    return;
                case 1:
                    layer_on(*data1);
                    return;
            }
            break;
        // lighting functions
        case 1:
            switch (*command) {
                case 0:
                    rgb_matrix_sethsv_noeeprom(*data1, *data2, *data3);
                    return;
                case 1:
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_set_color(*data4, *data1, *data2, *data3);
                    return;
                case 2:
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    matrix_set_color_all(0xFF, 0x00, 0x00);
                    return;
                case 3:
                    rgb_matrix_sethsv_noeeprom(*data1, *data2, *data3);
                    dat[0] = hsv.h;
                    dat[1] = hsv.s;
                    dat[2] = hsv.v;
                    raw_hid_send(dat, RAW_EPSIZE);
                default:
                    return;
            }
        case 99:
            reset_keyboard();
            return;
        default:
            return;
    }
}
