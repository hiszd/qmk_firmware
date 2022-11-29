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
#define OLED_MESG_CONST "Message: "

#if defined(KEYBOARD_hotdox76v2)
char oled_left[2][7];
char oled_right[2][7];

typedef struct _master_to_slave_oled_t {
    char current_slave[2][7];
} master_to_slave_oled_t;
master_to_slave_oled_t m2s;

typedef struct _slave_to_master_oled_t {
    char current_slave[2][7];
} slave_to_master_oled_t;
slave_to_master_oled_t s2m;
#else
char oled_left[2][7];
#endif

char hidmsg[7];

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
        render_logo();
        render_left();
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

void render_left_helper_fun(uint8_t start_col) {
    //                                        base + logo_w(32) + gap_w(12) +l*font_w(12)+current_byte_index
    oled_set_cursor(start_col, 0);
    oled_write_P(PSTR(OLED_LAYER_CONST), false);
    oled_write_P(IS_LAYER_ON(1) ? PSTR("2") : PSTR(" "), false);
    oled_write_P(IS_LAYER_ON(2) ? PSTR(" 3") : PSTR("  "), false);
    oled_write_P(IS_LAYER_ON(3) ? PSTR(" 4") : PSTR("  "), false);
    oled_write_P(PSTR("]"), false);
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(start_col, 1);
    oled_write_P(PSTR(OLED_INDS_CONST), false);
    oled_write_P(led_state.num_lock ? PSTR("N") : PSTR(" "), false);
    oled_write_P(led_state.caps_lock ? PSTR(" C") : PSTR("  "), false);
    oled_write_P(leader_on ? PSTR(" L") : PSTR("  "), false);
    oled_write_P(PSTR("]"), false);
}

void render_right_helper_fun(uint8_t start_col, const char *data, uint8_t max_col) {
    oled_set_cursor(start_col, 0);
    oled_write_P(PSTR(OLED_MESG_CONST), false);
    oled_set_cursor(start_col, 1);
    oled_write(data, false);
}

void render_right(void) {
    memcpy(oled_right[0], (const char *)hidmsg, 7);
    if (is_keyboard_master()) {
        render_right_helper_fun(0, (const char *)(oled_right[0]), 12);
        // render_right_helper_fun(0, (const char *)(oled_right[1]), 12);
    } else {
        oled_set_cursor(0, 1);
        oled_write(oled_right[0], false);
        // render_right_helper_fun(0, (const char *)(s2m.current_slave[0]), 12);
        // render_right_helper_fun(0, (const char *)(oled_right[1]), 12);
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
    const master_to_slave_oled_t *m2s = (const master_to_slave_oled_t *)in_data;
    memcpy(s2m.current_slave[0], m2s->current_slave[0], 7);
    memcpy(s2m.current_slave[1], m2s->current_slave[1], 7);
}

void keyboard_post_init_oled(void) {
    transaction_register_rpc(NOIZ_OLED_SYNC, noiz_sync_slave_handler);
}

void housekeeping_task_oled(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 400ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > oled_scan) {
            if (is_keyboard_left()) {
                // m2s.current_slave = oled_right;
                memcpy(s2m.current_slave[0], oled_right[0], 7);
                memcpy(s2m.current_slave[1], oled_right[1], 7);
            } else {
                // m2s.current_slave = oled_left;
                memcpy(s2m.current_slave[0], oled_left[0], 7);
                memcpy(s2m.current_slave[1], oled_left[1], 7);
            }
            if (transaction_rpc_exec(NOIZ_OLED_SYNC, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprint("Slave sync succeded!\n");
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
