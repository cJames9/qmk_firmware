/* Copyright 2023 Brian Low
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "sendstring_brazilian_abnt2.h"
#include "keymap_brazilian_abnt2.h"

//#ifdef CONSOLE_ENABLE
#include "print.h"
//#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
enum layers {
   _BASE = 0,
   _CLMK,
   _GAME,
   _SYMB,
   _NAVI,
   _TNAV,
   _NUM
};

enum custom_keycodes {
    M_CUT = SAFE_RANGE,
    M_COPY,
    M_PASTE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
        const bool is_combo = record->event.type == COMBO_EVENT;
        uprintf("0x%04X,%u,%u,%u,",
            keycode,
            is_combo ? 254 : record->event.key.row,
            is_combo ? 254 : record->event.key.col,
            get_highest_layer(layer_state)
            );
        uprint_bin4(record->event.pressed);
        uprintf(",0x%02X,0x%02X,%u\n",
            get_mods(),
            get_oneshot_mods(),
            record->tap.count
            );
    #endif
    switch (keycode) {
    case M_CUT:
        if (record->event.pressed) {
            // when keycode M_CUT is pressed
            SEND_STRING(SS_LCTL("x"));
        } else {
            // when keycode M_CUT is released
        }
        break;
    case M_COPY:
        if (record->event.pressed) {
            // when keycode M_COPY is pressed
            SEND_STRING(SS_LCTL("c"));
        } else {
            // when keycode M_COPY is released
        }
        break;
    case M_PASTE:
        if (record->event.pressed) {
            // when keycode M_PASTE is pressed
            SEND_STRING(SS_LCTL("v"));
        } else {
            // when keycode M_PASTE is released
        }
        break;
    }
    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case BR_CCED:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case BR_ACUT:
        case BR_TILD:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Layout padrão, adaptado do QWERTY ABNT2
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | '    |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  ´   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ç  |  ~   |
 * |------+------+------+------+------+------|  Mute |    | Numpad|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   ;  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT | LCMD | MO 3 | LCTL/| /Space  /       \Enter \  | MO 4 | Del  | APPL |  /   |
 *            |      |      |      | Space|/       /         \      \ |      |      |      |      |
 *            '---------------------------'-------´           `------''---------------------------'
 */

[_BASE] = LAYOUT(
    KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,                              KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC,
    BR_QUOT,  KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,                              KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    BR_ACUT,
    KC_TAB,   KC_A,    KC_S,     KC_D,    KC_F,    KC_G,                              KC_H,     KC_J,     KC_K,    KC_L,    BR_CCED, BR_TILD,
    KC_LSFT,  KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,           KC_MUTE,   TG(6),  KC_N,     KC_M,     KC_COMM, KC_DOT,  BR_SCLN, KC_RSFT,
                       KC_LALT,  KC_LCMD, MO(3),   LCTL_T(KC_SPC), KC_SPC,    KC_ENT, MO(4),    KC_DEL,   KC_APP,  BR_SLSH
),

/*
 * Layout Colemak-DH adaptado, em teste
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | '    |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   Ç  |  ´   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  ~   |
 * |------+------+------+------+------+------|  Mute |    | Numpad|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   ;  |Rshift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT | LCMD | MO 3 | LCTL/| /Space  /       \Enter \  | MO 4 | Del  | APPL |  /   |
 *            |      |      |      | Space|/       /         \      \ |      |      |      |      |
 *            '---------------------------'-------´           `------''---------------------------'
 */

[_CLMK] = LAYOUT(
    KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,                              KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC,
    BR_QUOT,  KC_Q,    KC_W,     KC_F,    KC_P,    KC_G,                              KC_J,     KC_L,     KC_U,    KC_Y,    BR_CCED, BR_ACUT,
    KC_TAB,   KC_A,    KC_R,     KC_S,    KC_T,    KC_D,                              KC_H,     KC_N,     KC_E,    KC_I,    KC_O,    BR_TILD,
    KC_LSFT,  KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,           KC_MUTE,   TG(6),  KC_K,     KC_M,     KC_COMM, KC_DOT,  BR_SCLN, KC_RSFT,
                       KC_LALT,  KC_LCMD, MO(3),   LCTL_T(KC_SPC), KC_SPC,    KC_ENT, MO(4),    KC_DEL,   KC_APP,  BR_SLSH
),

/*
 * Layout para jogos: QWERTY do lado esquerdo e setas do lado direito
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | '    |   Q  |   W  |   E  |   R  |   T  |                    |      | Home |  Up  | PgUp |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|      | Left | Down | Right| Del  |      |
 * |------+------+------+------+------+------|  Mute |    | Numpad|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|      | End  |      | PgDn |      |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT | LCMD | MO 3 | LCTL | /Space  /       \Enter \  | MO 4 | Del  | APPL |  /   |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            '---------------------------'-------´           `------''---------------------------'
 */

[_GAME] = LAYOUT(
    KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,                       KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC,
    BR_QUOT,  KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,                       _______,  KC_HOME,  KC_UP,   KC_PGUP, _______, _______,
    KC_TAB,   KC_A,    KC_S,     KC_D,    KC_F,    KC_G,                       _______,  KC_LEFT,  KC_DOWN, KC_RGHT, KC_DEL,  _______,
    KC_LSFT,  KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_MUTE,   TG(6),  _______,  KC_END,   _______, KC_PGDN, _______, KC_RSFT,
                       KC_LALT,  KC_LCMD, MO(3),   KC_LCTL, KC_SPC,    KC_ENT, MO(4),    KC_DEL,   KC_APP,  BR_SLSH
),

/*
 * Layout símbolos
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |Rec M1|PlayM1|Rec M2|PlayM2|RecStp|                    |   {  |   }  |      |   \  |   |  |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   [  |   ]  |   -  |   +  |   =  |  ~   |
 * |------+------+------+------+------+------|  Mute |    | Numpad|------+------+------+------+------+------|
 * |LShift|      | Cut  | Copy | Paste|      |-------|    |-------|      |      |   _  |   .  |RSft/;| TG 5 |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT | LCMD | MO 3 | LCTL/| /Space  /       \Enter \  | MO 4 | Del  | APPL |  /   |
 *            |      |      |      | Space|/       /         \      \ |      |      |      |      |
 *            '---------------------------'-------´           `------''---------------------------'
 */

[_SYMB] = LAYOUT(
    _______,  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,                             KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______,  DM_REC1, DM_PLY1,  DM_REC2, DM_PLY2, DM_RSTP,                           BR_LCBR,  BR_RCBR,  _______, BR_BSLS, BR_PIPE, KC_F12,
    _______,  BR_EXLM, BR_AT,    BR_HASH, BR_DLR,  BR_PERC,                           BR_LBRC,  BR_RBRC,  KC_MINS, KC_PPLS, KC_EQL,  BR_TILD,
    KC_LSFT,  _______, M_CUT,    M_COPY,  M_PASTE, _______,        KC_MUTE,   TG(6),  _______,  _______,  BR_UNDS, KC_DOT,  RSFT_T(BR_SCLN), TG(5),
                       KC_LALT,  KC_LCMD, MO(3),   LCTL_T(KC_SPC), KC_SPC,    KC_ENT, MO(4),    KC_DEL,   KC_APP,  BR_SLSH
),

/*
 * Layout navegação
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | '    |  Ins | PrtSc| Appl |      |      |                    |      | Home |  Up  | PgUp |      |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | Prev | Play | Next | LCTL | Caps |-------.    ,-------| TG 1 | Left | Down | Right|  Del |  ~   |
 * |------+------+------+------+------+------|  Mute |    | Numpad|------+------+------+------+------+------|
 * |LShift|      | Cut  | Copy | Paste|      |-------|    |-------| TG 2 | End  |      | PgDn |RSft/;| TG 5 |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT | LCMD | MO 3 | LCTL/| /Space  /       \Enter \  | MO 4 | Del  | APPL |  /   |
 *            |      |      |      | Space|/       /         \      \ |      |      |      |      |
 *            '---------------------------'-------´           `------''---------------------------'
 */

[_NAVI] = LAYOUT(
    _______,  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,                             KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______,  KC_INS,  KC_PSCR,  KC_APP,  _______, _______,                           _______,  KC_HOME,  KC_UP,   KC_PGUP, _______, KC_F12,
    _______,  KC_MPRV, KC_MPLY,  KC_MNXT, KC_LCTL, KC_CAPS,                           TG(1),    KC_LEFT,  KC_DOWN, KC_RGHT, KC_DEL,  BR_TILD,
    _______,  _______, M_CUT,    M_COPY,  M_PASTE, _______,        KC_MUTE,   TG(6),  TG(2),    KC_END,   _______, KC_PGDN, RSFT_T(BR_SCLN), TG(5),
                       KC_LALT,  KC_LCMD, MO(3),   LCTL_T(KC_SPC), KC_SPC,    KC_ENT, MO(4),    KC_DEL,   KC_APP,  BR_SLSH
),

[_TNAV] = LAYOUT(
    _______,  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,                             KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______,  KC_INS,  KC_PSCR,  KC_APP,  _______, _______,                           _______,  KC_HOME,  KC_UP,   KC_PGUP, _______, KC_F12,
    _______,  KC_MPRV, KC_MPLY,  KC_MNXT, KC_LCTL, KC_CAPS,                           TG(1),    KC_LEFT,  KC_DOWN, KC_RGHT, KC_DEL,  BR_TILD,
    _______,  _______, M_CUT,    M_COPY,  M_PASTE, _______,        KC_MUTE,   TG(6),  TG(2),    KC_END,   _______, KC_PGDN, RSFT_T(BR_SCLN), TG(5),
                       KC_LALT,  KC_LCMD, MO(3),   LCTL_T(KC_SPC), KC_SPC,    KC_ENT, MO(4),    KC_DEL,   KC_APP,  BR_SLSH
),

/*
 * Layout teclado numérico + controle dos LEDs
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |      |                    |      |  Num |   /  |   *  |   -  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |On/Off| Mode+| Mode-|      |      |      |                    |      |   7  |   8  |   9  |   +  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | Hue+ | Hue- | Brgt+| Brgt-|      |-------.    ,-------|      |   4  |   5  |   6  |   .  |      |
 * |------+------+------+------+------+------|  Mute |    | Numpad|------+------+------+------+------+------|
 * |LShift| Sat+ | Sat- | Spd+ | Spd- |      |-------|    |-------|      |   1  |   2  |   3  |  Ent |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT | LCMD | MO 3 | LCTL/| /Space  /       \Enter \  | MO 4 |   0  |   0  |   ,  |
 *            |      |      |      | Space|/       /         \      \ |      |      |      |      |
 *            '---------------------------'-------´           `------''---------------------------'
 */

[_NUM] = LAYOUT(
    _______,  _______, _______,  _______, _______, _______,                           _______,  KC_NUM,   KC_PSLS, KC_PAST, KC_PMNS, KC_BSPC,
    RGB_TOG,  RGB_MOD, RGB_RMOD, _______, _______, _______,                           _______,  KC_P7,    KC_P8,   KC_P9,   KC_PPLS, _______,
    _______,  RGB_HUI, RGB_HUD,  RGB_VAI, RGB_VAD, _______,                           _______,  KC_P4,    KC_P5,   KC_P6,   BR_PDOT, _______,
    _______,  RGB_SAI, RGB_SAD,  RGB_SPI, RGB_SPD, _______,        KC_MUTE,   TG(6),  _______,  KC_P1,    KC_P2,   KC_P3,   KC_PENT, _______,
                       KC_LALT,  KC_LCMD, MO(3),   LCTL_T(KC_SPC), KC_SPC,    KC_ENT, MO(4),    KC_P0,    KC_P0,   BR_PCMM
)

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
[_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
[_CLMK] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
[_GAME] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
[_SYMB] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
[_NAVI] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
[_TNAV] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
[_NUM]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_L, KC_WH_R) }
};
#endif
