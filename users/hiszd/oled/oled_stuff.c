#include "oled_stuff.h"
#include "matrix_scan.h"
#include "oled_driver.h"
#include "transactions.h"
#include <stdint.h>
#include <string.h>
#define NOIZ_LOGO
#include "noiz_logo.h"
#include "ext_big_font.h"

#define OLED_LAYER_CONST "Layer ["
#define OLED_INDS_CONST "Inds  ["

static uint32_t oled_timeout;
uint32_t        oled_scan;

bool oled_task_user(void) {
    oled_set_cursor(5, 0);
    if (is_oled_on()) {
#ifdef SPLIT_KEYBOARD
        if (is_keyboard_left()) {
            render_logo();
            render_left();
        } else {
            render_logo();
            render_right();
        }
#else
        // oled_write_ln_P(logo_noiz, false);
        // render_left();
#endif
    }
    return false;
}

void render_logo(void) {
    uint8_t i = 0, j = 0;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 32; ++j) {
            if (is_keyboard_left()) {
                oled_write_raw_byte(pgm_read_byte(&logo_noiz[i * 32 + j]), i * 128 + j);
            } else {
                oled_write_raw_byte(pgm_read_byte(&logo_noiz[i * 32 + j]), i * 128 + j + 96);
            }
        }
    }
}

void render_left_helper_fun(uint8_t start_line) {
    //                                        base + logo_w(32) + gap_w(12) +l*font_w(12)+current_byte_index
    oled_set_cursor(start_line, 0);
    oled_write_P(PSTR(OLED_LAYER_CONST), false);
    oled_write_P(IS_LAYER_ON(1) ? PSTR("2") : PSTR(" "), false);
    oled_write_P(IS_LAYER_ON(2) ? PSTR(" 3") : PSTR("  "), false);
    oled_write_P(IS_LAYER_ON(3) ? PSTR(" 4") : PSTR("  "), false);
    oled_write_P(PSTR("]"), false);
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(start_line, 1);
    oled_write_P(PSTR(OLED_INDS_CONST), false);
    oled_write_P(led_state.num_lock ? PSTR("N") : PSTR(" "), false);
    oled_write_P(led_state.caps_lock ? PSTR(" C") : PSTR("  "), false);
    oled_write_P(leader_on ? PSTR(" L") : PSTR("  "), false);
    oled_write_P(PSTR("]"), false);
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
    render_left_helper_fun(5);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
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

bool process_record_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (is_oled_on()) {
            oled_scan = 400;
        } else {
            oled_on();
        }
        oled_timeout = timer_read32();
    }
    return true;
}

void matrix_scan_oled(void) {
#if defined(OLED_TIMEOUT) && !defined(OLED_SCROLL_TIMEOUT)
    if (is_oled_on() && timer_elapsed32(oled_timeout) > OLED_TIMEOUT) {
        oled_off();
    }
#endif
#if defined(OLED_TIMEOUT) && defined(OLED_SCROLL_TIMEOUT)
    if (is_oled_on() && timer_elapsed32(oled_timeout) > OLED_TIMEOUT) {
        oled_scan = 5000;
    }
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
        // Interact with slave every 400ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > oled_scan) {
            if (transaction_rpc_exec(NOIZ_OLED_SYNC, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprint("Slave sync succeded!\n");
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
