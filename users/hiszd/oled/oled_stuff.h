#include "../hiszd.h"

#define UNC (94 + 0x21)

typedef struct _master_to_slave_oled_t {
    bool leader_on;
} master_to_slave_oled_t;

extern master_to_slave_oled_t oled_m2s;
void                          hid_msg(uint8_t[20], uint8_t, uint8_t);

bool process_record_oled(uint16_t, keyrecord_t *);
void matrix_scan_oled(void);

void housekeeping_task_oled(void);
void keyboard_post_init_oled(void);

void render_logo(void);
void render_left(void);
void render_right(void);

bool oled_task_kb(void);
