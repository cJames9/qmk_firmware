# Copyright 2019 Manna Harbour
# https://github.com/manna-harbour/miryoku

OLED_ENABLE			 = yes
WPM_ENABLE           = yes   # WPM Calculation
CONSOLE_ENABLE 		 = yes
COMMAND_ENABLE       = no
LUMBERJACK_ENABLE    = yes

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled.c
endif

# MIRYOKU_NAV = INVERTEDT
# MIRYOKU_CLIPBOARD = WIN