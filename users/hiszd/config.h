#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY

#ifdef LEADER_ENABLE
#    define LEADER_TIMEOUT 150
#    define LEADER_PER_KEY_TIMING
#endif

#ifdef COMBO_ENABLE
#    undef COMBO_COUNT
#    undef COMBO_TERM
#    define COMBO_COUNT 5
#    define COMBO_TERM 60
#endif

#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 5000
#    define OLED_UPDATE_INTERVAL 400
#    define OLED_FADE_OUT
#    define OLED_FADE_OUT_INTERVAL 0
#endif

#ifdef HISZD_HID
#    define RAW_USAGE_PAGE 0xFF60
#    define RAW_USAGE_ID 0x69
#endif

#if defined(SPLIT_KEYBOARD)

#    define SPLIT_TRANSACTION_IDS_USER HISZD_SYNC_LIGHTS, NOIZ_OLED_SYNC

#    if defined(RGB_MATRIX_ENABLE)
// Master to slave:
#        define RPC_M2S_BUFFER_SIZE 132
// Slave to master:
#        define RPC_S2M_BUFFER_SIZE 132
#    else
// Master to slave:
#        define RPC_M2S_BUFFER_SIZE 64
// Slave to master:
#        define RPC_S2M_BUFFER_SIZE 64
#    endif // SPLIT_KEYBOARD
#endif     // SPLIT_KEYBOARD
