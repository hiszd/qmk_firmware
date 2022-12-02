#include "../../../quantum/quantum.h"
#include "../matrix_scan.h"
#include "oled_driver.h"
#include "transactions.h"
#include <stdint.h>
#include <string.h>
#define NOIZ_LOGO
#include "noiz_logo.h"

#define UNC (94 + 0x21)

#ifndef M2SOLED
typedef struct _master_to_slave_oled_t {
    bool leader_on;
} master_to_slave_oled_t;
#    define M2SOLED
#endif /* M2SOLED */

extern master_to_slave_oled_t oled_m2s;

void hid_msg(uint8_t[17], uint8_t);

bool process_record_oled(uint16_t, keyrecord_t *);
void matrix_scan_oled(void);

void housekeeping_task_oled(void);
void keyboard_post_init_oled(void);

void render_logo(void);
void render_left(void);
void render_right(void);

bool oled_task_kb(void);
