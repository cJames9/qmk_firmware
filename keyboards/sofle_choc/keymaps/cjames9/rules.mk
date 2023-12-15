ENCODER_MAP_ENABLE 	= yes
VIA_ENABLE 			= yes   # Configuring keyboard with VIA
MOUSEKEY_ENABLE 	= yes
SPACE_CADET_ENABLE 	= no
GRAVE_ESC_ENABLE 	= no
# OLED_DRIVER_ENABLE  = yes   # 128X32 OLED Screen
OLED_ENABLE			= yes
LTO_ENABLE          = yes   # Link Time Optimization
MIDI_ENABLE         = no    # MIDI controls
WPM_ENABLE          = yes   # WPM Calculation

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled.c
endif
