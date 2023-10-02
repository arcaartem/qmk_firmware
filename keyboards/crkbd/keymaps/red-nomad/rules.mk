OLED_ENABLE                  =  yes
RGBLIGHT_ENABLE              =  no
TAP_DANCE_ENABLE             =  yes
RAW_ENABLE                   =  no
DEBOUNCE_TYPE                =  sym_defer_pk
CONSOLE_ENABLE               =  no
DYNAMIC_TAPPING_TERM_ENABLE  =  no
DYNAMIC_MACRO_ENABLE = yes
RGB_MATRIX_ENABLE = yes

SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no

SRC += tap_dance_helper.c oled_helper.c
