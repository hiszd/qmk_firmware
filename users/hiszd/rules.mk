BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = no       # Audio control and System control(+450)
TAP_DANCE_ENABLE = no      # Enable Tap Dance.
COMBO_ENABLE = no           # Enable Combos
LEADER_ENABLE = yes         # Enable Leader Key
RAW_ENABLE = yes

SRC += hiszd.c \
       process_records.c \
       matrix_scan.c

ifeq ($(strip $(RAW_ENABLE)), yes)
    SRC += raw_hid.c
endif

ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
    SRC += transport_sync.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb_mat.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_mat.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled/oled_stuff.c
endif

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
    SRC += secrets.c
endif
