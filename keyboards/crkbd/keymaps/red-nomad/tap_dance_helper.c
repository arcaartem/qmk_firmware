#include QMK_KEYBOARD_H
#include "tap_dance_helper.h"
#include "layers.h"

td_state_t cur_dance(tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            return state->pressed ? TD_SINGLE_HOLD : TD_SINGLE_TAP;
        case 2:
            if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
            if (state->pressed) return TD_DOUBLE_HOLD;
            return TD_DOUBLE_TAP;
        case 3:
            if (state->interrupted) return TD_TRIPLE_SINGLE_TAP;
            if (state->pressed) return TD_TRIPLE_HOLD;
            return TD_TRIPLE_TAP;
        default:
            return TD_UNKNOWN;
    }
}

