#include "hiszd_hid.h"

hidstore_t store;
bool       receive_complete = false;
// #define RAW_EPSIZE 8

/* The packets are arranged as such:
 * 0x00: current packet number
 * 0x01: total packets(max of 2)
 * 0x02: total packet size
 * 0x03: parameter 1
 * 0x04: parameter 2
 * 0x05: parameter 3
 * 0x06-0xFF: led array/oled characters
 */

void send_success(uint8_t val) {
    uint8_t data[32];
    data[0] = 0x00;
    data[1] = 0x01;
    data[2] = 0x01;
    data[3] = 0x04;
    data[4] = val;
    raw_hid_send(data, 32);
#ifdef CONSOLE_ENABLE
    uprintf("Sending response\n");
#endif /* CONSOLE_ENABLE */
}

void raw_hid_receive(uint8_t* data, uint8_t length) {
    // The second byte is the size of the message
    uint8_t size = data[2];
    if (data[1] == 2) {
        if (data[0] == 1) {
            memset(store.bytes, 0xFF, sizeof(uint8_t[64]));
            memcpy(store.bytes, data + 3, sizeof(uint8_t[size - 3]));
            store.length     = size - 3;
            receive_complete = false;
            // memset(data, 0xFF, sizeof(uint8_t[32]));
            return;
        } else if (data[0] == 2) {
            memcpy(store.bytes + store.length, data + 3, sizeof(uint8_t[size - 3]));
            store.length     = (store.length + size - 3);
            receive_complete = true;
#ifdef CONSOLE_ENABLE
            uprintf("Store: %u [", store.length);
            for (uint8_t i = 0; i < store.length; i++) {
                if (i != store.length - 1) {
                    uprintf("%u,", store.bytes[i]);
                } else {
                    uprintf("%u", store.bytes[i]);
                }
            }
            uprint("]\n");
#endif /* CONSOLE_ENABLE */
        }
    } else if (data[1] == 1) {
        memset(store.bytes, 0xFF, sizeof(uint8_t[64]));
        memcpy(store.bytes, data + 3, sizeof(uint8_t[size - 3]));
        store.length     = size - 3;
        receive_complete = true;
#ifdef CONSOLE_ENABLE
        uprintf("Store: %u [", store.length);
        for (uint8_t i = 0; i < store.length; i++) {
            if (i != store.length - 1) {
                uprintf("%u,", store.bytes[i]);
            } else {
                uprintf("%u", store.bytes[i]);
            }
        }
        uprint("]\n");
#endif /* CONSOLE_ENABLE */
    } else {
#ifdef CONSOLE_ENABLE
        uprintf("invalid packet total: %u\n", data[1]);
#endif /* CONSOLE_ENABLE */
        return;
    }
    uint8_t reqtype = store.bytes[0];
    uint8_t command = store.bytes[1];
#ifdef CONSOLE_ENABLE
    uprintf("reqtype: %u\n", reqtype);
    uprintf("command: %u\n", command);
#endif /* CONSOLE_ENABLE */
    __attribute__((unused)) uint8_t param1 = store.bytes[2];
    __attribute__((unused)) uint8_t param2 = store.bytes[3];
    __attribute__((unused)) uint8_t param3 = store.bytes[4];
#ifdef OLED_ENABLE
    uint8_t dat[17];
    memcpy(dat, store.bytes + 5, sizeof(uint8_t[17]));
#endif /* OLED_ENABLE */
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
    uint8_t leddata[store.length - 5];
    memset(leddata, 0xFF, sizeof(uint8_t[store.length - 5]));
    memcpy(leddata, store.bytes + 5, sizeof(uint8_t[store.length - 5]));
#    ifdef RGB_MATRIX_ENABLE
    HSV hsv = rgb_matrix_get_hsv();
#    endif /* RGB_MATRIX_ENABLE */
#endif     /* defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE) */
    switch (reqtype) {
        // layer functions
        case 0:
            switch (command) {
                case 0:
                    layer_off(param1);
                    send_success(0x01);
                    return;
                case 1:
                    layer_on(param1);
                    send_success(0x01);
                    return;
                default:
                    send_success(0x00);
                    return;
            }
                // lighting functions
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
        case 1:
            switch (command) {
                case 0:
// TODO will only work on matrix keyboards right now
#    ifdef RGB_MATRIX_ENABLE
                    rgb_matrix_sethsv_noeeprom(param1, param2, param3);
#    endif /* RGB_MATRIX_ENABLE */
                    send_success(0x01);
                    return;
                case 1:
#    ifdef RGB_MATRIX_ENABLE
                    rgb_matrix_set_flags(LED_FLAG_NONE);
#    endif /* RGB_MATRIX_ENABLE */
#    ifdef CONSOLE_ENABLE
                    uprint("setting led color\n");
#    endif /* CONSOLE_ENABLE */
                    hiszd_matrix_set_color(leddata, store.length - 5, param1, param2, param3);
                    send_success(0x01);
                    return;
                case 2:
// TODO will only work on matrix keyboards right now
#    ifdef RGB_MATRIX_ENABLE
                    rgb_matrix_sethsv_noeeprom(param1, param2, param3);
                    data[0] = hsv.h;
                    data[1] = hsv.s;
                    data[2] = hsv.v;
                    raw_hid_send(data, 32);
#    endif /* RGB_MATRIX_ENABLE */
                    send_success(0x01);
                    return;
                case 3:
                    hiszd_matrix_set_color_all(param1, param2, param3);
                    send_success(0x01);
                    return;
                default:
                    send_success(0x00);
                    return;
            }
#endif /* defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE) */
#ifdef OLED_ENABLE
        case 2:
            hid_msg(dat, (size - 3));
            send_success(0x01);
            return;
#endif /* OLED_ENABLE */
        case 99:
            reset_keyboard();
            send_success(0x01);
            return;
        default:
            send_success(0x00);
            return;
    }

    return;
}
