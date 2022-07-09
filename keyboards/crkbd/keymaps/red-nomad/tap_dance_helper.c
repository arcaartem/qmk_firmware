#include QMK_KEYBOARD_H
#include "tap_dance_helper.h"
#include "layers.h"

extern int oled_state;

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

td_state_t cur_dance(qk_tap_dance_state_t *state) {
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

void layer_slash_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_BACKSLASH);
            break;
        case TD_SINGLE_HOLD:
            layer_on(L1);
            if (layer_state_is(BASE_ALT))
                layer_on(L1_ALT);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LSFT);
            register_code(KC_BACKSLASH);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LALT);
            layer_on(L1);
            if (layer_state_is(BASE_ALT))
                layer_on(L1_ALT);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_BACKSLASH);
            register_code(KC_BACKSLASH);
            break;
        case TD_TRIPLE_TAP:
            if (layer_state_is(L1)) {
                if (layer_state_is(BASE_ALT))
                    layer_on(L1_ALT);
                layer_off(L1);
            } else {
                layer_on(L1);
                if (layer_state_is(BASE_ALT))
                    layer_on(L1_ALT);
            }
            break;
        default:
        break;
    }
}

void layer_slash_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_BACKSLASH);
            break;
        case TD_SINGLE_HOLD:
            if (layer_state_is(BASE_ALT))
                layer_off(L1_ALT);
            layer_off(L1);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_BACKSLASH);
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LALT);
            if (layer_state_is(BASE_ALT))
                layer_off(L1_ALT);
            layer_off(L1);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code(KC_BACKSLASH);
            break;
        default:
        break;
    }
    xtap_state.state = TD_NONE;
}

void oled_toggle_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: oled_state ^= true;
        default:
        break;
    }
}

void oled_toggle_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        default:
        break;
    }
    xtap_state.state = TD_NONE;
}
