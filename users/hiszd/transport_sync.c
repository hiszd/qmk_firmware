#include "transport_sync.h"
#include <stdbool.h>
#include <stdint.h>
#include "transactions.h"

master_to_slave_t m2s_overall;
bool              m2s_go = false;

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t* m2s = (const master_to_slave_t*)in_data;
    for (int n = 0; n < 43; n++) {
        rgb_matrix_set_color(n + 43, m2s->led[n].r, m2s->led[n].g, m2s->led[n].b);
        // rgb_matrix_set_color(43, m2s->led[1].r, m2s->led[1].g, m2s->led[1].b);
    }
}

void keyboard_post_init_transport_sync(void) {
    transaction_register_rpc(HISZD_SYNC_LIGHTS, user_sync_a_slave_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500 && m2s_go) {
            if (transaction_rpc_send(HISZD_SYNC_LIGHTS, sizeof(m2s_overall), &m2s_overall)) {
                last_sync = timer_read32();
                dprintf("Slave sync success!\n");
                // m2s_go = false;
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
