#include QMK_KEYBOARD_H
#include "layers.h"
#include "oled_helper.h"

#ifdef OLED_ENABLE

#define OLED_USER_TIMEOUT 30000

uint8_t hid_buffers[2][32] = { 0 };
uint8_t hid_buffer_lengths[2] = { 0 };
char keylog_str[24] = {};

uint16_t get_top_layer(void) {
    uint16_t top_layer = 0x8000;
    while (top_layer > layer_state && top_layer > 0)
        top_layer >>= 1;

    return top_layer;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  }

  return OLED_ROTATION_180;
}

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

void print_hex_string(uint8_t value) {
    char layer_state_buf[7] = {};
    snprintf(layer_state_buf, sizeof(layer_state_buf), "%04x", layer_state);
    oled_write_ln(layer_state_buf, false);
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    switch (get_top_layer()) {
        case 0:
        case L_BASE:
        case L_BASE_ALT:
            oled_write_P(PSTR("BASE "), true);
            break;
        case L_LOWER:
            oled_write_P(PSTR("LOWER"), true);
            break;
        case L_RAISE:
            oled_write_P(PSTR("RAISE"), true);
            break;
        case L_MEDIA:
            oled_write_P(PSTR("MEDIA"), true);
            break;
        case L_MOUSE:
            oled_write_P(PSTR("MOUSE"), true);
            break;
        case L_FUNCTION:
            oled_write_P(PSTR("FKEYS"), true);
            break;
        default:
            print_hex_string(layer_state);
            break;
    }

    if (layer_state & L_BASE_ALT)
        oled_write_ln_P(PSTR(" (*)"), false);
    else
        oled_write_ln_P(PSTR(""), false);

    oled_write_P(PSTR("-----"), false);
}

void oled_print_mod(uint16_t mods, uint16_t mod_mask, char * indicator) {
    if ((mods & mod_mask) > 0)
        oled_write(indicator, false);
    else
        oled_write_P(PSTR(" "), false);
}

void oled_render_mod_state(void) {
    uint16_t mods = get_mods();
    oled_write_P(PSTR("Mods "), false);
    oled_write_P(PSTR("G"), ((mods & MOD_MASK_GUI) > 0));
    oled_write_P(PSTR("C"), ((mods & MOD_MASK_CTRL) > 0));
    oled_write_P(PSTR("A"), ((mods & MOD_MASK_ALT) > 0));
    oled_write_ln_P(PSTR("S"), ((mods & MOD_MASK_SHIFT) > 0));
    oled_write_P(PSTR("-----"), false);
}

void oled_render_host_led_status(void) {
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("Leds "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_write_ln_P(PSTR("S"), led_state.scroll_lock);
    oled_write_P(PSTR("-----"), false);
}

void oled_render_layer_mod_host_state(void) {
    oled_render_layer_state();
    oled_render_mod_state();
    oled_render_host_led_status();
}

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  uint16_t rawKeycode = keycode;
  keycode = keycode & 0x7F;
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), " '%c'  %dx%d %05x",
           name, record->event.key.row, record->event.key.col,
           rawKeycode);
}

void oled_render_keylog(void) {
    oled_write_ln_P(PSTR("Key"), false);
    oled_write(keylog_str, false);
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

void oled_render_custom_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}
bool oled_task_user(void) {

/*#ifdef ENCODER_ENABLE*/
    /*bool is_activity_elapsed = (last_matrix_activity_elapsed() > OLED_USER_TIMEOUT && last_encoder_activity_elapsed() > OLED_USER_TIMEOUT);*/
/*#else*/
    /*bool is_activity_elapsed = (last_matrix_activity_elapsed() > OLED_USER_TIMEOUT);*/
/*#endif*/

    /*if (is_activity_elapsed) {*/
        /*if (is_oled_on()) {*/
            /*oled_off();*/
        /*}*/
        /*return false;*/
    /*} else if (!is_oled_on()) {*/
        /*oled_on();*/
    /*}*/

    if (is_keyboard_master()) {
        oled_render_layer_mod_host_state();
        oled_render_keylog();
        oled_render_hid_message();
    } else {
        oled_render_custom_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}

#endif // OLED_ENABLE
