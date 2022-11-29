#include "oled_stuff.h"
#include "oled_driver.h"
#include "transactions.h"
#include <stdint.h>
#include <string.h>
#define NOIZ_LOGO
#include "noiz_logo.h"
#include "ext_big_font.h"

bool oled_task_user(void) {
    oled_set_cursor(0, 0);
#ifdef SPLIT_KEYBOARD
    if (is_keyboard_left()) {
        render_logo();
        // oled_write_ln_P(PSTR("ZION"), false);
        // render_left();
    } else {
        // render_right();
        // oled_write_ln_P(logo_noiz, false);
    }
#else
    // oled_write_ln_P(logo_noiz, false);
    // render_left();
#endif
    return false;
}

void render_logo(void) {
    oled_set_cursor(0, 0);
    uint8_t page = 0;
    for (int s = 0; s < sizeof(logo_noiz); s++) {
        oled_write_raw(&logo_noiz[s], 1);
        // oled_write(logo_noiz, false);
        if (s > ((sizeof(logo_noiz) / 4) * page)) {
            page++;
            oled_set_cursor(0, page);
        }
    }
}

void render_left_helper_fun(uint8_t start_line, const char *data, uint8_t gap_w, uint8_t l) {
    uint8_t j = 0, k = 0;
    for (j = 0; j < l; ++j) {      // font index
        for (k = 0; k < 12; ++k) { // font byte index
            //                                        base + logo_w(32) + gap_w(12) +l*font_w(12)+current_byte_index
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[pgm_read_byte(&data[j]) - 0x21][k]), start_line * 2 * 128 + 32 + gap_w + j * 12 + k);
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[pgm_read_byte(&data[j]) - 0x21][k + 12]), start_line * 2 * 128 + 128 + 32 + gap_w + j * 12 + k);
        }
    }
    for (j = 0; j < gap_w; ++j) {
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line * 2 * 128 + 32 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line * 2 * 128 + 32 + gap_w + l * 12 + j);

        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line * 2 * 128 + 128 + 32 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line * 2 * 128 + 128 + 32 + gap_w + l * 12 + j);
    }
}

void render_right_helper_fun(uint8_t start_line, const char *data, uint8_t gap_w, uint8_t l) {
    uint8_t j = 0, k = 0;
    for (j = 0; j < l; ++j) {      // font index
        for (k = 0; k < 12; ++k) { // font byte index
            //                                        base + logo_w(0) + gap_w(12) +l*font_w(12)+current_byte_index
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[data[j] - 0x21][k]), start_line * 2 * 128 + gap_w + j * 12 + k);
            oled_write_raw_byte(pgm_read_byte(&ext_big_font[data[j] - 0x21][12 + k]), start_line * 2 * 128 + 128 + gap_w + j * 12 + k);
        }
    }
    for (j = 0; j < gap_w; ++j) {
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line * 2 * 128 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line * 2 * 128 + gap_w + l * 12 + j);

        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line * 2 * 128 + 128 + j);
        oled_write_raw_byte(pgm_read_byte(&blank_block), start_line * 2 * 128 + 128 + gap_w + l * 12 + j);
    }
}

void render_right(void) {
    if (is_keyboard_master()) {
        render_right_helper_fun(0, (const char *)(oled_right[0]), 12, 6);
        render_right_helper_fun(1, (const char *)(oled_right[1]), 12, 6);
    } else {
        render_right_helper_fun(0, (const char *)(oled_right[0]), 12, 6);
        render_right_helper_fun(1, (const char *)(oled_right[1]), 12, 6);
    }
    return;
}

void render_left() {
    uint8_t layer = get_highest_layer(layer_state);
    render_left_helper_fun(0, PSTR("LAYER:"), 12, 6);
    switch (layer) {
        case 0:
            render_left_helper_fun(1, PSTR("1:HOME"), 12, 6);
            break;
        case 1:
            render_left_helper_fun(1, PSTR("2:CODE"), 12, 6);
            break;
        case 2:
            render_left_helper_fun(1, PSTR("3:OFFICE"), 0, 8);
            break;
        case 3:
        default:
            render_left_helper_fun(1, PSTR("4:OTHERS"), 0, 8);
            break;
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    strcpy((char *)(oled_left[0]), "[    ]");
    oled_left[0][0] = UNC;
    oled_left[0][1] = UNC;
    oled_left[0][2] = UNC;
    oled_left[0][3] = UNC;
    oled_left[0][4] = UNC;
    oled_left[0][5] = UNC;
    oled_left[0][6] = UNC;
    strcpy((char *)(oled_left[1]), "[    ]");
    oled_left[1][0] = UNC;
    oled_left[1][1] = UNC;
    oled_left[1][2] = UNC;
    oled_left[1][3] = UNC;
    oled_left[1][4] = UNC;
    oled_left[1][5] = UNC;
    oled_left[1][6] = UNC;

#if defined(KEYBOARD_hotdox76v2)
    strcpy((char *)(oled_right[0]), "[    ]");
    oled_right[0][0] = UNC;
    oled_right[0][1] = UNC;
    oled_right[0][2] = UNC;
    oled_right[0][3] = UNC;
    oled_right[0][4] = UNC;
    oled_right[0][5] = UNC;
    oled_right[0][6] = UNC;
    strcpy((char *)(oled_right[1]), "[    ]");
    oled_right[1][0] = UNC;
    oled_right[1][1] = UNC;
    oled_right[1][2] = UNC;
    oled_right[1][3] = UNC;
    oled_right[1][4] = UNC;
    oled_right[1][5] = UNC;
    oled_right[1][6] = UNC;
#endif

#if defined(SPLIT_KEYBOARD)
    if (is_keyboard_left()) {
        return OLED_ROTATION_180;
    } else {
        return OLED_ROTATION_0;
    }
#else
    return OLED_ROTATION_180;
#endif
}

void noiz_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    s2m.success = true;
}

void keyboard_post_init_oled(void) {
    transaction_register_rpc(NOIZ_OLED_SYNC, noiz_sync_slave_handler);
}

void housekeeping_task_oled(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 200ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 200) {
            if (transaction_rpc_exec(NOIZ_OLED_SYNC, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprint("Slave sync successed!\n");
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
