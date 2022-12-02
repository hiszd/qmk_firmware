// #include "raw_hid.h"
#include <stdint.h>
#include "stdint.h"
#include "hiszd.h"
#include "string.h"
#ifdef OLED_ENABLE
#    include "oled/oled_stuff.h"
#endif /* OLED_ENABLE */
#ifdef SPLIT_ENABLE
#    include "transactions.h"
#    include "transport_sync.h"
#endif /* SPLIT_ENABLE */
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#    include "rgb_mat.h"
#    include "color.h"
#endif /* defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE) */
#ifdef SPLIT_ENABLE
#    include "transactions.h"
#    include "transport_sync.h"
#endif /* SPLIT_ENABLE */
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#    include "rgb_mat.h"
#    include "color.h"
#endif /* defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE) */

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *                       reqtype = &(data[0]);
    uint8_t *                       command = &(data[1]);
    __attribute__((unused)) uint8_t size    = data[2];
    __attribute__((unused)) uint8_t param1  = data[3];
    __attribute__((unused)) uint8_t param2  = data[4];
    __attribute__((unused)) uint8_t param3  = data[5];
#ifdef OLED_ENABLE
    uint8_t dat[17];
    memcpy(dat, data + 6, sizeof(uint8_t[17]));
#endif /* OLED_ENABLE */
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
    uint8_t leddata[25] = {255};
    memset(leddata, 0xFF, sizeof(uint8_t[25]));
    memcpy(leddata, data + 6, sizeof(uint8_t[25]));
#    ifdef RGB_MATRIX_ENABLE
    HSV hsv = rgb_matrix_get_hsv();
#    endif /* RGB_MATRIX_ENABLE */
#endif     /* defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE) */
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
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
        case 1:
            switch (*command) {
                case 0:
// TODO will only work on matrix keyboards right now
#    ifdef RGB_MATRIX_ENABLE
                    rgb_matrix_sethsv_noeeprom(param1, param2, param3);
#    endif /* RGB_MATRIX_ENABLE */
                    return;
                    // This does not work on split keyboards
                case 1:
// TODO will only work on matrix keyboards right now
#    ifdef RGB_MATRIX_ENABLE
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    hiszd_matrix_set_color(leddata, size - 7, param1, param2, param3);
#    endif /* RGB_MATRIX_ENABLE */
                    return;
                case 2:
// TODO will only work on matrix keyboards right now
#    ifdef RGB_MATRIX_ENABLE
                    rgb_matrix_sethsv_noeeprom(param1, param2, param3);
                    data[0] = hsv.h;
                    data[1] = hsv.s;
                    data[2] = hsv.v;
                    raw_hid_send(data, RAW_EPSIZE);
#    endif /* RGB_MATRIX_ENABLE */
                    return;
// TODO will only work on matrix keyboards right now
#    ifdef RGB_MATRIX_ENABLE
                case 3:
                    hiszd_matrix_set_color_all(param1, param2, param3);
                    return;
#    endif /* RGB_MATRIX_ENABLE */
                default:
                    return;
            }
#endif /* defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE) */
#ifdef OLED_ENABLE
        case 2:
            hid_msg(dat, (size - 3));
            return;
#endif /* OLED_ENABLE */
        case 99:
            reset_keyboard();
            return;
        default:
            return;
    }
}
