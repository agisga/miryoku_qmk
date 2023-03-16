RGBLIGHT_ENABLE = no
# FIXME: for some reason RGB_MATRIX_ENABLE doesn't work when enabled from config.h conditionally for blok (and disabled for pro-micro), but only works when enabled here from rules.mk
RGB_MATRIX_ENABLE = yes

MIRYOKU_KLUDGE_THUMBCOMBOS=yes

# for saving firmware size (https://github.com/qmk/qmk_firmware/blob/master/docs/squeezing_avr.md):
LTO_ENABLE = yes
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
# for saving extra firmware size (https://github.com/qmk/qmk_firmware/blob/master/docs/squeezing_avr.md):
#MAGIC_ENABLE = no
#CONSOLE_ENABLE = no
#COMMAND_ENABLE = no
