ENCODER_MAP_ENABLE 	= yes
MOUSEKEY_ENABLE 	= yes
SPACE_CADET_ENABLE 	= no
GRAVE_ESC_ENABLE 	= no
OLED_ENABLE			= yes
LTO_ENABLE          = yes   # Link Time Optimization
MIDI_ENABLE         = no    # MIDI controls
WPM_ENABLE          = yes   # WPM Calculation
CAPS_WORD_ENABLE 	= yes   # LShift + RShift enables caps for a single word
CONSOLE_ENABLE 		= yes

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled.c
endif
