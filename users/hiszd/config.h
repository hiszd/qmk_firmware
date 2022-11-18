#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#    define TAPPING_TERM 120
#endif
#define TAPPING_TERM_PER_KEY

#ifdef LEADER_ENABLE
#    define LEADER_TIMEOUT 500
#    define LEADER_PER_KEY_TIMING
#endif

#ifdef COMBO_ENABLE
#    undef COMBO_COUNT
#    undef COMBO_TERM
#    define COMBO_COUNT 5
#    define COMBO_TERM 60
#endif

#define RAW_USAGE_PAGE 0xFF90
#define RAW_USAGE_ID 0x69

#define SPLIT_TRANSACTION_IDS_USER HISZD_SYNC_LIGHTS
