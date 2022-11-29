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
    uint8_t *data1   = &(data[2]);
    uint8_t *data2   = &(data[3]);
    uint8_t *data3   = &(data[4]);
    uint8_t *data4   = &(data[5]);
    uint8_t *data5   = &(data[6]);
    uint8_t *data6   = &(data[7]);
    uint8_t *data7   = &(data[8]);
    uint8_t *data8   = &(data[9]);
    uint8_t *data9   = &(data[10]);
    uint8_t *data10  = &(data[11]);
    uint8_t *data11  = &(data[12]);
    leddat_t leddata = {{*data4, *data5, *data6, *data7, *data8, *data9, *data10, *data11}};
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
            // hidmsg[0] = (char)*command;
            // hidmsg[1] = (char)*data1;
            // hidmsg[2] = (char)*data2;
            // hidmsg[3] = (char)*data3;
            // hidmsg[4] = (char)*data4;
            // hidmsg[5] = (char)*data5;
            // hidmsg[6] = (char)*data6;
            hidmsg[0] = 'B';
            hidmsg[1] = 'o';
            hidmsg[2] = 'b';
            hidmsg[3] = 'b';
            hidmsg[4] = 'y';
            hidmsg[5] = ' ';
            return;
        case 99:
            reset_keyboard();
            return;
        default:
            return;
    }
}
