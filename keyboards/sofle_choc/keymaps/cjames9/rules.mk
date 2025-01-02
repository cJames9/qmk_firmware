ENCODER_MAP_ENABLE 	 = yes
VIA_ENABLE 			 = yes   # Configuring keyboard with VIA
SPACE_CADET_ENABLE 	 = no
GRAVE_ESC_ENABLE 	 = no
OLED_ENABLE			 = yes
MIDI_ENABLE          = no    # MIDI controls
WPM_ENABLE           = yes   # WPM Calculation
CAPS_WORD_ENABLE 	 = yes   # LShift + RShift enables caps for a single word
CONSOLE_ENABLE 		 = no
COMMAND_ENABLE       = no
DYNAMIC_MACRO_ENABLE = yes

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled.c
endif
