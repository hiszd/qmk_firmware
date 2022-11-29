#include "../hiszd.h"

#define UNC (94 + 0x21)

#if defined(KEYBOARD_hotdox76v2)
char oled_left[2][7];
char oled_right[2][7];

typedef struct _master_to_slave_oled_t {
    char current_slave[2][7];
} master_to_slave_oled_t;
master_to_slave_oled_t m2s;

typedef struct _slave_to_master_oled_t {
    bool success;
} slave_to_master_oled_t;
slave_to_master_oled_t s2m;
#else
char oled_left[2][7];
#endif

void housekeeping_task_oled(void);
void keyboard_post_init_oled(void);

void render_logo(void);
void render_left(void);
void render_right(void);

bool oled_task_kb(void);
