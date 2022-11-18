#include <stdint.h>
#include "hiszd.h"

typedef struct _rgb_led {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_led;

typedef struct _master_to_slave_t {
    rgb_led led[43];
} master_to_slave_t;

typedef struct _slave_to_master_t {
    rgb_led led[43];
} slave_to_master_t;

extern master_to_slave_t m2s_overall;
extern bool              m2s_go;

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data);

void keyboard_post_init_transport_sync(void);

void housekeeping_task_user(void);
