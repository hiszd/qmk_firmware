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
    uint8_t  dat[20];
    // memset(dat, 0x00, sizeof(uint8_t[20]));
    memcpy(dat, data + 3, sizeof(uint8_t[20]));
    uint8_t leddata[25] = {255};
    memcpy(leddata, data + 6, sizeof(uint8_t[25]));
    HSV hsv = rgb_matrix_get_hsv();
    switch (*reqtype) {
        // layer functions
        case 0:
            switch (*command) {
                case 0:
                    layer_off(dat[1]);
                    return;
                case 1:
                    layer_on(dat[1]);
                    return;
            }
            break;
        // lighting functions
        case 1:
            switch (*command) {
                case 0:
                    rgb_matrix_sethsv_noeeprom(dat[1], dat[2], dat[3]);
                    return;
                // This does not work on split keyboards
                case 1:
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    hiszd_matrix_set_color(leddata, size - 7, dat[1], dat[2], dat[3]);
                    return;
                case 2:
                    rgb_matrix_sethsv_noeeprom(dat[1], dat[2], dat[3]);
                    data[0] = hsv.h;
                    data[1] = hsv.s;
                    data[2] = hsv.v;
                    raw_hid_send(data, RAW_EPSIZE);
                    return;
                case 3:
                    hiszd_matrix_set_color_all(dat[1], dat[2], dat[3]);
                    return;
                default:
                    return;
            }
        case 2:
            hid_msg(dat, (size - 3), 0);
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
