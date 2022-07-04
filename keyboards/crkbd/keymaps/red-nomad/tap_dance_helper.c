#include QMK_KEYBOARD_H
#include "tap_dance_helper.h"
#include "layers.h"

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->pressed) return TD_DOUBLE_HOLD;
        return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (!state->pressed) return TD_TRIPLE_TAP;
        return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

void layer_slash_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_BSLASH); break;
        case TD_SINGLE_HOLD: layer_on(L1); break;
        case TD_DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_BSLASH); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); layer_on(L1); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_BSLASH); register_code(KC_BSLASH); break;
        case TD_TRIPLE_TAP:
            if (layer_state_is(L1)) {
                // If already set, then switch it off
                layer_off(L1);
            } else {
                // If not already set, then switch the layer on
                layer_on(L1);
            }
            break;
        default:
        break;
    }
}

void layer_slash_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_BSLASH); break;
        case TD_SINGLE_HOLD: layer_off(L1); break;
        case TD_DOUBLE_TAP: unregister_code(KC_BSLASH); unregister_code(KC_LSFT); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); layer_off(L1); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_BSLASH); break;
        default:
        break;
    }
    xtap_state.state = TD_NONE;
}

void layer_alt_slash_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_BSLASH); break;
        case TD_SINGLE_HOLD: layer_on(L1); layer_on(L1_ALT); break;
        case TD_DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_BSLASH); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); layer_on(L1); layer_on(L1_ALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_BSLASH); register_code(KC_BSLASH); break;
        case TD_TRIPLE_TAP:
            if (layer_state_is(L1)) {
                // If already set, then switch it off
                layer_off(L1);
            } else {
                // If not already set, then switch the layer on
                layer_on(L1);
            }
            break;
        default:
        break;
    }
}

void layer_alt_slash_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_BSLASH); break;
        case TD_SINGLE_HOLD: layer_off(L1_ALT); layer_off(L1); break;
        case TD_DOUBLE_TAP: unregister_code(KC_BSLASH); unregister_code(KC_LSFT); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); layer_off(L1_ALT); layer_off(L1); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_BSLASH); break;
        default:
        break;
    }
    xtap_state.state = TD_NONE;
}
