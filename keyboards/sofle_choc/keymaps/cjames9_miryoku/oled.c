// Copied and adapted from laosteven's Corne keymap
// https://github.com/laosteven/fluffy-octo-eureka

//#pragma once

#include "oled_driver.h"
#include "quantum.h"
#include QMK_KEYBOARD_H

#include <stdio.h>

enum layers {
   _BASE = 0,
   _CLMK,
   _GAME,
   _SYMB,
   _NAVI,
   _TNAV,
   _NUM
};

#ifdef OLED_ENABLE
char wpm_str[12];
char buf[30];
char mod_str[12];
char keylog_str[24] = {};
uint16_t wpm_graph_timer = 0;
// static uint32_t oled_timer = 0;
static uint32_t anim_timer = 0;
#define ANIM_SIZE 512
#define ANIM_FRAME 300

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void oled_render_separator(void) {
    oled_write("_____", false);
}

void oled_render_space(void) {
    oled_write("     ", false);
}

void oled_render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write("[QWR]", false);
            break;
        case _CLMK:
            oled_write("[CMK]", false);
            break;
        case _GAME:
            oled_write("[GAM]", false);
            break;
        case _SYMB:
            oled_write("[SYM]", true);
            break;
        case _NAVI:
            oled_write("[NAV]", true);
            break;
        case _TNAV:
            oled_write("[TNV]", true);
            break;
        case _NUM:
            oled_write("[NUM]", true);
            break;
        default:
            oled_write("[NOP]", true);
            break;
    }
}

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) ||
        (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "[MAT] %dx%d [KYC] %03d ",
        record->event.key.row, record->event.key.col,
        keycode);
}

static void oled_render_keylog(void) {
    if (strlen(keylog_str) == 0) {
        snprintf(keylog_str, sizeof(keylog_str), "[MAT] 0x0 [KYC] 000 ");
    }
    oled_write(keylog_str, false);
}

static void oled_render_hsv(bool full) {
#ifdef RGB_MATRIX_ENABLE
  if (rgb_matrix_get_mode() > 1 && rgb_matrix_is_enabled()) {
      if (full) {
          snprintf(buf, sizeof(buf), "[LED]M %3dH %3dS %3dV %3d",
                   rgb_matrix_get_mode(),
                   rgb_matrix_get_hue(),
                   rgb_matrix_get_sat(),
                   rgb_matrix_get_val());
      } else {
          snprintf(buf, sizeof(buf), "[%3d] ", rgb_matrix_get_mode());
      }
      oled_write(buf, false);
  }
#endif
}

void oled_render_keymods(led_t led_state) {
    sprintf(mod_str, "num %scap %s",
        led_state.num_lock ? "+" : "-",
        led_state.caps_lock ? "+" : "-"
    );
    oled_write(mod_str, false);
}

void oled_render_wpm(void) {
    sprintf(wpm_str, "[WPM] %03d ", get_current_wpm());
    oled_write(wpm_str, false);
}

// Inspired from brickbots' Kyria keymap
// - https://github.com/brickbots/qmk_firmware/tree/brickbots_dev/keyboards/kyria/keymaps/brickbots
// - https://www.reddit.com/r/MechanicalKeyboards/comments/evimyg/kyria_is_kool_onboard_wpm_calc_oled_graph/
static void oled_render_wpm_graph(void) {
    static uint8_t bar_count = 0;
    uint8_t bar_height = 0;
    uint8_t bar_segment = 0;
    uint8_t oled_lines = oled_max_lines();

    if (wpm_graph_timer == 0) {
        wpm_graph_timer = timer_read();
        return;
    }
    if(timer_elapsed(wpm_graph_timer) > 500) {
        wpm_graph_timer = timer_read();

        bar_height = get_current_wpm() / 6;
        if(bar_height > (OLED_DISPLAY_WIDTH / oled_lines * 4)) {
            bar_height = OLED_DISPLAY_WIDTH / oled_lines * 4;
        }

        oled_pan(false);
        bar_count++;
        for (uint8_t i = oled_lines; i > (oled_lines - 4); i--) {
            if (bar_height > 7) {
                if (i % 2 == 1 && bar_count % 3 == 0)
                    bar_segment = 254;
		        else
		            bar_segment = 255;
		        bar_height -= 8;
	        } else {

                switch (bar_height) {
                    case 0:
                        bar_segment = 128;
                        break;

                    case 1:
                        bar_segment = 128;
                        break;

                    case 2:
                        bar_segment = 192;
                        break;

                    case 3:
                        bar_segment = 224;
                        break;

                    case 4:
                        bar_segment = 240;
                        break;

                    case 5:
                        bar_segment = 248;
                        break;

                    case 6:
                        bar_segment = 252;
                        break;

                    case 7:
                        bar_segment = 254;
                        break;
                }
            bar_height = 0;

            if (i % 2 == 1 && bar_count % 3 == 0)
                bar_segment++;
            }
            oled_write_raw_byte(bar_segment, (i-1) * OLED_DISPLAY_HEIGHT);
        }
    }
}

// 5x3 Logos
void oled_render_crkbd_logo(void) {
    static const char PROGMEM font_logo[16] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(font_logo, false);
};

void oled_render_kapi_logo(void) {
    static const char PROGMEM font_kapi_logo[2][16] = {
        {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0},
        {0x85, 0x86, 0x87, 0x88, 0x89, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0}
    };
    oled_write_P(font_kapi_logo[get_current_wpm() % 2], false);
};

void oled_render_music_bars(void) {
    static uint8_t current_frame = 0;

    static const char PROGMEM music_bars[3][16] = {
        {0x8f, 0x90, 0x91, 0x92, 0x93, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0},
        {0x95, 0x96, 0x97, 0x98, 0x99, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0},
        {0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0}
    };

    if (timer_elapsed32(anim_timer) > ANIM_FRAME) {
        anim_timer = timer_read32();
        const char* frame = music_bars[current_frame];
        oled_write_P(frame, false);
        current_frame = (current_frame + 1) % 3;
    }
}


void oled_render_idle(void) {
    oled_render_space();
    oled_render_space();
    oled_render_space();
    oled_render_crkbd_logo();
    oled_render_space();
    oled_render_space();
    oled_render_space();
    oled_render_space();
}

void oled_render_master(void) {
    oled_render_layer_state();
    oled_render_separator();

    oled_render_keylog();
    oled_render_separator();

    oled_render_keymods(host_keyboard_led_state());
    oled_render_separator();

    oled_render_wpm();
    oled_render_wpm_graph();
}

void oled_render_slave(void) {
    oled_render_crkbd_logo();
    oled_write("sofle", false);
    oled_write("choc ", false);
    oled_render_separator();

    oled_render_hsv(true);
	//oled_render_space();
    oled_render_separator();

    oled_render_music_bars();
}

bool oled_task_user(void) {
    /*if (timer_elapsed32(oled_timer) > 60000 && timer_elapsed32(oled_timer) < 80000) {
        // 1min
        oled_render_idle();
        return false;
    }
    else if (timer_elapsed32(oled_timer) > 80000) {
        // 1min30
        oled_off();
        rgb_matrix_disable();
        return false;
    }
    else {
        if (!is_oled_on()) {
            oled_on();
            rgb_matrix_enable();
        }*/

        if (is_keyboard_master()) {
            oled_render_master();
        } else {
            oled_render_slave();
        }
		return false;
    //}
}
#endif
