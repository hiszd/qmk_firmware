#include "../../quantum/quantum.h"
#include "transactions.h"
#include <stdint.h>
#include <stdbool.h>
#include "crc.h"

#ifndef RGBLEDDEF
typedef struct _rgb_led {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_led;
#    define RGBLEDDEF
#endif /* !RGBLEDDEF */

#ifndef M2SDEF
typedef struct _master_to_slave_t {
    rgb_led led[43];
    uint8_t checksum;
} master_to_slave_t;
#    define M2SDEF
#endif /* !M2SDEF */

#ifndef S2MDEF
typedef struct _slave_to_master_t {
    bool success;
} slave_to_master_t;
#    define S2MDEF
#endif /* !S2MDEF */

extern master_to_slave_t m2s_overall;
extern bool              m2s_go;

void user_sync_a_slave_handler(uint8_t, const void*, uint8_t, void*);

void keyboard_post_init_transport_sync(void);

void housekeeping_task_rgb(void);
