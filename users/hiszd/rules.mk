BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = no       # Audio control and System control(+450)
TAP_DANCE_ENABLE = no      # Enable Tap Dance.
COMBO_ENABLE = no           # Enable Combos
LEADER_ENABLE = yes         # Enable Leader Key
RAW_ENABLE = yes
GRAVE_ESC_ENABLE = no
# CONSOLE_ENABLE = yes
# OLED_ENABLE = no

ifneq ($(PLATFORM),CHIBIOS)
    ifneq ($(strip $(LTO_SUPPORTED)), no)
        LTO_ENABLE        = yes
    endif
endif

SRC += $(USER_PATH)/hiszd.c \
       $(USER_PATH)/process_records.c \
       $(USER_PATH)/matrix_scan.c

ifeq ($(strip $(RAW_ENABLE)), yes)
    SRC += $(USER_PATH)/hiszd_hid.c
endif

ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
    SRC += $(USER_PATH)/transport_sync.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += $(USER_PATH)/rgb_mat.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += $(USER_PATH)/rgb_mat.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += $(USER_PATH)/oled/oled_stuff.c
endif

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
    SRC += $(USER_PATH)/secrets.c
endif
