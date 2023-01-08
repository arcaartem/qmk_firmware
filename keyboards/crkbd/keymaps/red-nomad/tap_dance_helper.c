#include QMK_KEYBOARD_H
#include "tap_dance_helper.h"
#include "layers.h"

extern int custom_oled_power_state;

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state[] = {
    [TD_TAB_HYPER] = {
        .is_press_action = true,
        .state = TD_NONE
    },
    [TD_LSFT_MEH] = {
        .is_press_action = true,
        .state = TD_NONE
    },
    [TD_LALT_EH] = {
        .is_press_action = true,
        .state = TD_NONE
    },
    [TD_OLED_TOGGLE] = {
        .is_press_action = true,
        .state = TD_NONE
    },
};

td_state_t cur_dance(tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            return state->pressed ? TD_SINGLE_HOLD : TD_SINGLE_TAP;
        case 2:
            return state->pressed ? TD_DOUBLE_HOLD : TD_DOUBLE_TAP;
        case 3:
            return state->pressed ? TD_TRIPLE_HOLD : TD_TRIPLE_TAP;
        default:
            return TD_UNKNOWN;
    }
}

void oled_toggle_dance_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state[TD_OLED_TOGGLE].state = cur_dance(state);
    switch (xtap_state[TD_OLED_TOGGLE].state) {
        case TD_SINGLE_TAP: custom_oled_power_state ^= 1;
        default:
        break;
    }
}

void oled_toggle_dance_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state[TD_OLED_TOGGLE].state) {
        default:
        break;
    }
    xtap_state[TD_OLED_TOGGLE].state = TD_NONE;
}

void tab_hyper_dance_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state[TD_TAB_HYPER].state = cur_dance(state);
    switch (xtap_state[TD_TAB_HYPER].state) {
        case TD_SINGLE_TAP:
            register_code(KC_TAB);
        break;
        case TD_SINGLE_HOLD:
            layer_on(L4);
        break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LGUI);
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
        break;
        default:
        break;
    }
}

void tab_hyper_dance_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state[TD_TAB_HYPER].state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_TAB);
        break;
        case TD_SINGLE_HOLD:
            layer_off(L4);
        break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LGUI);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_LSFT);
        break;
        default:
        break;
    }
    xtap_state[TD_TAB_HYPER].state = TD_NONE;
}

void lsft_meh_dance_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state[TD_LSFT_MEH].state = cur_dance(state);
    switch (xtap_state[TD_LSFT_MEH].state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
        break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
        break;
        default:
        break;
    }
}

void lsft_meh_dance_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state[TD_LSFT_MEH].state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            unregister_code(KC_LSFT);
        break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_LSFT);
        break;
        default:
        break;
    }
    xtap_state[TD_LSFT_MEH].state = TD_NONE;
}

void lalt_eh_dance_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state[TD_LALT_EH].state = cur_dance(state);
    switch (xtap_state[TD_LALT_EH].state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            register_code(KC_LALT);
        break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
            register_code(KC_LALT);
            register_code(KC_LSFT);
        break;
        default:
        break;
    }
}

void lalt_eh_dance_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state[TD_LALT_EH].state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            unregister_code(KC_LALT);
        break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LALT);
            unregister_code(KC_LSFT);
        break;
        default:
        break;
    }
    xtap_state[TD_LALT_EH].state = TD_NONE;
}
