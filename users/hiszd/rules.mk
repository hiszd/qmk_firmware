BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
TAP_DANCE_ENABLE = yes      # Enable Tap Dance.
COMBO_ENABLE = no           # Enable Combos
LEADER_ENABLE = yes         # Enable Leader Key

SRC += hiszd.c \
       process_records.c \
       tap_dances.c \
			 matrix_scan.c

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
    SRC += secrets.c
endif
