#include "transport_sync.h"
#include <stdbool.h>
#include <stdint.h>
#include "transactions.h"
#include "crc.h"

master_to_slave_t m2s_overall;
int               ledsize   = sizeof m2s_overall.led / sizeof m2s_overall.led[0];
bool              m2s_go    = false;
bool              m2s_ready = false;
bool              syncfail  = false;
// master_to_slave_t m2s_slave;

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t* m2s = (const master_to_slave_t*)in_data;
    slave_to_master_t*       s2m = (slave_to_master_t*)out_data;
    // memset(m2s_slave, m2s, sizeof(master_to_slave_t));
    if (m2s->checksum == crc8(m2s->led, sizeof(m2s->led))) {
        for (int n = 0; n < ledsize; n++) {
            rgb_matrix_set_color(n + 43, m2s->led[n].r, m2s->led[n].g, m2s->led[n].b);
        }
        s2m->success = true;
    } else {
        s2m->success = false;
    }
}

void keyboard_post_init_transport_sync(void) {
    transaction_register_rpc(HISZD_SYNC_LIGHTS, user_sync_a_slave_handler);
}

void housekeeping_task_rgb(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (!m2s_ready) {
            for (int n = 0; n < 43; n++) {
                if (n < 48) {
                    m2s_overall.led[n] = (rgb_led){r : 0, g : 0, b : 0};
                } else {
                    m2s_overall.led[n] = (rgb_led){r : 0, g : 0, b : 0};
                }
                m2s_ready = true;
            }
        } else {
            master_to_slave_t m2s = m2s_overall;
            if ((timer_elapsed32(last_sync) > 500 && m2s_go) || syncfail == true) {
                m2s.checksum          = crc8(m2s.led, sizeof(m2s.led));
                slave_to_master_t s2m = {0};
                if (transaction_rpc_exec(HISZD_SYNC_LIGHTS, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                    last_sync = timer_read32();
                    dprintf("Slave sync success!\n");
                    // m2s_go = false;
                    if (!s2m.success) {
                        syncfail = true;
                    } else {
                        syncfail = false;
                    }
                } else {
                    dprint("Slave sync failed!\n");
                    syncfail = true;
                }
            }
        }
    }
}
