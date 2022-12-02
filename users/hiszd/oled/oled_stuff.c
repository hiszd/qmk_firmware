#include "oled_stuff.h"

#define OLED_LAYER_CONST "Layer ["
#define OLED_INDS_CONST "Inds  ["
#define OLED_MESG_CONST "Message: "

#if defined(KEYBOARD_hotdox76v2)
uint8_t oled_left[2][17];
uint8_t oled_right[2][17];

typedef struct _slave_to_master_oled_t {
    bool leader_on;
} slave_to_master_oled_t;
slave_to_master_oled_t s2m;
#else
uint8_t oled_left[2][17];
#endif

master_to_slave_oled_t oled_m2s;

static uint16_t message_timeout = 4000;
static uint32_t message_timer;

static uint16_t oled_timeout = OLED_TIMEOUT;
static uint32_t oled_timer;
uint32_t        oled_scan;

extern master_to_slave_oled_t oled_m2s;

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

void render_right_helper_fun(uint8_t start_col) {
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
    if (is_keyboard_master()) {
#ifdef LEADER_ENABLE
        oled_write_P(leader_on ? PSTR(" L") : PSTR("  "), false);
#else
        oled_write_P(PSTR("  "), false);
#endif /* LEADER_ENABLE */
    } else {
#ifdef LEADER_ENABLE
        oled_write_P(s2m.leader_on ? PSTR(" L") : PSTR("  "), false);
#else
        oled_write_P(PSTR("  "), false);
#endif /* LEADER_ENABLE */
    }
    oled_write_P(PSTR("]"), false);
}

void render_left_helper_fun(uint8_t start_col, uint8_t max_col) {
    if (oled_left[0][0] != 0x00) {
        oled_set_cursor(start_col, 0);
        oled_write_P(PSTR(OLED_MESG_CONST), false);
        oled_set_cursor(start_col, 1);
        oled_write((const char *)oled_left[0], false);
    } else {
        oled_set_cursor(start_col, 0);
        oled_write_P(PSTR("                 "), false);
        oled_set_cursor(start_col, 1);
        oled_write_P(PSTR("                 "), false);
    }
}

void render_right(void) {
    render_right_helper_fun(0);
}

void hid_msg(uint8_t data[17], uint8_t size) {
    memcpy(oled_left[0], data, sizeof(uint8_t[size]));
    message_timer = timer_read32();
}

void render_left() {
    render_left_helper_fun(5, 12);
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
            oled_scan = 200;
        } else {
            oled_on();
            oled_scan = 200;
        }
        oled_timer = timer_read32();
    }
    return true;
}

void matrix_scan_oled(void) {
#if defined(OLED_TIMEOUT) && !defined(OLED_SCROLL_TIMEOUT)
    if (is_oled_on() && timer_elapsed32(oled_timer) > oled_timeout) {
        oled_off();
    }
#endif
#if defined(OLED_TIMEOUT) && defined(OLED_SCROLL_TIMEOUT)
    if (is_oled_on() && timer_elapsed32(oled_timer) > oled_timeout) {
        oled_scan = 1000;
    }
#endif
    if (timer_elapsed32(message_timer) > message_timeout) {
        memset(oled_left[0], 0x00, sizeof(uint8_t[17]));
    }
}

void noiz_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    const master_to_slave_oled_t *m2s = (const master_to_slave_oled_t *)in_data;
    slave_to_master_oled_t *      s2m = (slave_to_master_oled_t *)out_data;
    s2m->leader_on                    = m2s->leader_on;
}

void keyboard_post_init_oled(void) {
    transaction_register_rpc(NOIZ_OLED_SYNC, noiz_sync_slave_handler);
}

void housekeeping_task_oled(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 400ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > oled_scan) {
#ifdef LEADER_ENABLE
            oled_m2s.leader_on = leader_on;
#else
            oled_m2s.leader_on = false;
#endif /* LEADER_ENABLE */
            if (transaction_rpc_exec(NOIZ_OLED_SYNC, sizeof(oled_m2s), &oled_m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprint("Slave sync succeded!\n");
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
