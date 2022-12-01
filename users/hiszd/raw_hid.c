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
    uint8_t  size    = data[2];
    uint8_t  param1  = data[3];
    uint8_t  param2  = data[4];
    uint8_t  param3  = data[5];
    uint8_t  dat[17];
    memcpy(dat, data + 6, sizeof(uint8_t[17]));
    uint8_t leddata[25] = {255};
    memset(leddata, 0xFF, sizeof(uint8_t[25]));
    memcpy(leddata, data + 6, sizeof(uint8_t[25]));
    HSV hsv = rgb_matrix_get_hsv();
    switch (*reqtype) {
        // layer functions
        case 0:
            switch (*command) {
                case 0:
                    layer_off(param1);
                    return;
                case 1:
                    layer_on(param1);
                    return;
            }
            break;
        // lighting functions
        case 1:
            switch (*command) {
                case 0:
                    rgb_matrix_sethsv_noeeprom(param1, param2, param3);
                    return;
                // This does not work on split keyboards
                case 1:
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    hiszd_matrix_set_color(leddata, size - 7, param1, param2, param3);
                    return;
                case 2:
                    rgb_matrix_sethsv_noeeprom(param1, param2, param3);
                    data[0] = hsv.h;
                    data[1] = hsv.s;
                    data[2] = hsv.v;
                    raw_hid_send(data, RAW_EPSIZE);
                    return;
                case 3:
                    hiszd_matrix_set_color_all(param1, param2, param3);
                    return;
                default:
                    return;
            }
        case 2:
            hid_msg(dat, (size - 3));
            return;
        case 99:
            reset_keyboard();
            return;
        default:
            return;
    }
    // memset(data, 0, sizeof(uint8_t[26]));
    // memset(leddata, 0, sizeof(uint8_t[26]));
    // memset(dat, 0, sizeof(uint8_t[20]));
}
