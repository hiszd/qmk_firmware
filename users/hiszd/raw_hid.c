#include "raw_hid.h"
#include "hiszd.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *reqtype = &(data[0]);
    uint8_t *command = &(data[1]);
    uint8_t *data1   = &(data[2]);
    // uint8_t *data2   = &(data[3]);
    // uint8_t *data3   = &(data[4]);
    switch (*reqtype) {
        // layer functions
        case 0:
            if (*command == 0) {
                    layer_off(*data1);
                    break;
            }else if (*command == 1) {
                    layer_on(*data1);
                    break;
            }
            break;
        // lighting functions
        case 1:
            if (*command == 0) {
                    break;
            }else if (*command == 1) {
                    rgb_matrix_sethsv_noeeprom(HSV_GREEN);
                    break;
            }
            break;
        case 99:
            reset_keyboard();
            break;
    }
}
