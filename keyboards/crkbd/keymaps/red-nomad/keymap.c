/*
Copyright 2019 @foostan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "print.h"

#define BASE 0
#define L1 1
#define L2 2
#define L3 3
#define L4 4

#define OLED_USER_TIMEOUT 60000

uint8_t hid_buffers[2][32] = { 0 };
uint8_t hid_buffer_lengths[2] = { 0 };

enum {
    TD_LALT_LCTRL,
    TD_RALT_LGUI,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LALT_LCTRL] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LCTRL),
    [TD_RALT_LGUI] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_LGUI),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------------------------------------------.                                                   ,-----------------------------------------------------------------------------------------.
        LT(L4,KC_TAB),          KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                                                              KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,     KC_BSPACE,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
       HYPR_T(KC_ESC),          KC_A,          KC_S,          KC_D,          KC_F,          KC_G,                                                              KC_H,          KC_J,          KC_K,          KC_L,       KC_SCLN,        KC_ENT,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
              KC_LSFT,          KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,                                                              KC_N,          KC_M,       KC_COMM,        KC_DOT,       KC_SLSH,       KC_RSFT,
    //|--------------+--------------+--------------+--------------+--------------+--------------+---------------|                    |--------------+--------------+--------------+--------------+--------------+--------------+--------------|
                                                                TD(TD_LALT_LCTRL),LT(L2,KC_QUOTE),LGUI_T(KC_SPC),                     LCTL_T(KC_SPC),LT(L1,KC_BSLASH),TD(TD_RALT_LGUI)
                                                                //`---------------------------------------------'                    `--------------------------------------------'
  ),

  [L1] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------------------------------------------.                                                   ,-----------------------------------------------------------------------------------------.
              _______,         KC_UP,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                                                           KC_HOME,       KC_PGDN,       KC_PGUP,        KC_END,     KC_INSERT,     KC_DELETE,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
              KC_LEFT,       KC_DOWN,      KC_RIGHT,       XXXXXXX,       XXXXXXX,       XXXXXXX,                                                           KC_LEFT,       KC_DOWN,         KC_UP,      KC_RIGHT,       XXXXXXX,       _______,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
              _______,    LCTL(KC_Z),    LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),       XXXXXXX,                                                     LALT(KC_LEFT), LALT(KC_DOWN),   LALT(KC_UP),LALT(KC_RIGHT),       XXXXXXX,       _______,
    //|--------------+--------------+--------------+--------------+--------------+--------------+---------------|                    |--------------+--------------+--------------+--------------+--------------+--------------+--------------|
                                                                          _______,        MO(L3),        _______,                            _______,       _______,       _______
                                                                //`---------------------------------------------'                    `--------------------------------------------'
  ),

  [L2] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------------------------------------------.                                                   ,-----------------------------------------------------------------------------------------.
           RALT(KC_3),          KC_1,          KC_2,          KC_3,          KC_4,          KC_5,                                                              KC_6,          KC_7,          KC_8,          KC_9,          KC_0,       _______,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
       HYPR_T(KC_ESC),LSFT(KC_GRAVE),LSFT(KC_MINUS),LSFT(KC_EQUAL),LSFT(KC_LBRACKET),LSFT(KC_RBRACKET),                                                    KC_GRAVE,      KC_MINUS,      KC_EQUAL,   KC_LBRACKET,   KC_RBRACKET,       _______,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
              _______,    LSFT(KC_1),    LSFT(KC_2),    LSFT(KC_3),    LSFT(KC_4),    LSFT(KC_5),                                                        LSFT(KC_6),    LSFT(KC_7),    LSFT(KC_8),    LSFT(KC_9),    LSFT(KC_0),       _______,
    //|--------------+--------------+--------------+--------------+--------------+--------------+---------------|                    |--------------+--------------+--------------+--------------+--------------+--------------+--------------|
                                                                          _______,       _______,        _______,                            _______,        MO(L3),       _______
                                                                //`---------------------------------------------'                    `--------------------------------------------'
  ),

  [L3] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------------------------------------------.                                                   ,-----------------------------------------------------------------------------------------.
 MAGIC_TOGGLE_CTL_GUI,  KC_MS_ACCEL0,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,XXXXXXX,                                             KC_MS_WH_LEFT, KC_MS_WH_DOWN,   KC_MS_WH_UP,KC_MS_WH_RIGHT,       RGB_TOG,KC_SYSTEM_POWER,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
         EEPROM_RESET,  KC_MS_ACCEL1,    KC_MS_BTN3,    KC_MS_BTN2,    KC_MS_BTN1,    KC_MS_BTN4,                                                        KC_MS_LEFT,    KC_MS_DOWN,      KC_MS_UP,   KC_MS_RIGHT,       RGB_SPI,KC_SYSTEM_SLEEP,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
                RESET,  KC_MS_ACCEL2, KC_AUDIO_MUTE,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MS_BTN5,                                                           RGB_MOD,      RGB_RMOD,       RGB_SAI,       RGB_SAD,       RGB_SPD,KC_SYSTEM_WAKE,
    //|--------------+--------------+--------------+--------------+--------------+--------------+---------------|                    |--------------+--------------+--------------+--------------+--------------+--------------+--------------|
                                                                          RGB_HUD,       _______,        RGB_HUI,                            RGB_VAI,       _______,       RGB_VAD
                                                                //`---------------------------------------------'                    `--------------------------------------------'
  ),

  [L4] = LAYOUT_split_3x6_3( \
    //,-----------------------------------------------------------------------------------------.                                                   ,-----------------------------------------------------------------------------------------.
              _______,         KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,                                                             KC_F6,         KC_F7,         KC_F8,         KC_F9,        KC_F10,      KC_POWER,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
              _______,        KC_F11,        KC_F12,        KC_F13,        KC_F14,        KC_F15,                                                            KC_F16,        KC_F17,        KC_F18,        KC_F19,        KC_F20,       _______,
    //|--------------+--------------+--------------+--------------+--------------+--------------|                                                   |--------------+--------------+--------------+--------------+--------------+--------------|
              _______,        KC_F21,        KC_F22,        KC_F23,        KC_F24,       XXXXXXX,                                                   DYN_MACRO_PLAY1,DYN_MACRO_PLAY2,DYN_REC_START1,DYN_REC_START2, DYN_REC_STOP,       _______,
    //|--------------+--------------+--------------+--------------+--------------+--------------+---------------|                    |--------------+--------------+--------------+--------------+--------------+--------------+--------------|
                                                                          _______,       _______,        _______,                            _______,       _______,       _______
                                                                //`---------------------------------------------'                    `--------------------------------------------'
  ),
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8
#define L_FUNCTION 16

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}
#endif

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (is_oled_on()) {
        uint8_t buffer_select = data[0];
        uint8_t data_length = data[1];
        dprintf("raw_hid_receive - buffer_select: %d, data_lenght: %d, length: %d\n", buffer_select, data_length, length);
        if (buffer_select > 1 || data_length > 29) {
            return;
        }

        hid_buffer_lengths[buffer_select] = data_length;
        for (uint8_t i=0; i<data_length && i<30; i++) {
            hid_buffers[buffer_select][i] = data[i+2];
        }
    }
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        case L_FUNCTION:
            oled_write_ln_P(PSTR("Function"), false);
            break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write_ln(keylog_str, false);
}

void oled_render_hid_buffer(uint8_t buffer) {
    uint8_t length = hid_buffer_lengths[buffer];
    /* dprintf("oled_render_hid_buffer - buffer: %d, length: %d\n", buffer, length); */
    if (length > 0) {
        for (uint8_t i=0; i<length; i++) {
            oled_write_char((char)hid_buffers[buffer][i], false);
        }
    }
}

void oled_render_hid_message(void) {
    oled_render_hid_buffer(0);
    oled_write_ln_P(PSTR(""), false);
    oled_render_hid_buffer(1);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
#    ifdef ENCODER_ENABLE
    if (last_matrix_activity_elapsed() > OLED_USER_TIMEOUT && last_encoder_activity_elapsed() > OLED_USER_TIMEOUT) {
#    else
    if (last_matrix_activity_elapsed() > OLED_USER_TIMEOUT) {
#    endif
        if (is_oled_on()) {
            oled_off();
        }
        return;
    } else if (!is_oled_on()) {
        oled_on();
    }

    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
        oled_render_hid_message();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE
