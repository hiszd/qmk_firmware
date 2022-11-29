#include "../hiszd.h"

#define UNC (94 + 0x21)

extern char hidmsg[7];

bool process_record_oled(uint16_t, keyrecord_t *);
void matrix_scan_oled(void);

void housekeeping_task_oled(void);
void keyboard_post_init_oled(void);

void render_logo(void);
void render_left(void);
void render_right(void);

bool oled_task_kb(void);
