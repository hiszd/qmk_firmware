// #include "raw_hid.h"
#include <stdint.h>
#include "color.h"
#include "stdint.h"
#include "hiszd.h"
#include "oled/oled_stuff.h"
#include "transactions.h"
#include "transport_sync.h"
#include "rgb_mat.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *reqtype = &(data[0]);
    uint8_t *command = &(data[1]);
    uint8_t *dat     = {0};
    strncpy((char *)dat, (const char *)&data + 2, 15);
    uint8_t *data1   = &(data[2]);
    uint8_t *data2   = &(data[3]);
    uint8_t *data3   = &(data[4]);
    leddat_t leddata = {{dat[4], dat[5], dat[6], dat[7], dat[8], dat[9], dat[10], dat[11]}};
    HSV      hsv     = rgb_matrix_get_hsv();
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
                // This does not work on split keyboards
                case 1:
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    hiszd_matrix_set_color(leddata, *data1, *data2, *data3);
                    return;
                case 2:
                    rgb_matrix_sethsv_noeeprom(*data1, *data2, *data3);
                    data[0] = hsv.h;
                    data[1] = hsv.s;
                    data[2] = hsv.v;
                    raw_hid_send(data, RAW_EPSIZE);
                    return;
                case 3:
                    hiszd_matrix_set_color_all(*data1, *data2, *data3);
                    return;
                default:
                    return;
            }
        case 2:
            hid_msg(data, 0);
            return;
        case 99:
            reset_keyboard();
            return;
        default:
            return;
    }
}
