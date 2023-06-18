#ifndef TAP_DANCE_HELPER__H
#define TAP_DANCE_HELPER__H

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
    TD_TRIPLE_SINGLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_ESC_HYPER,
    TD_LSFT_MEH,
    TD_LALT_EH,
    TD_LALT_RALT,
    TD_RALT_MEH,
    TD_RALT_GUI,
    TD_LAYER_QUOTE,
    TD_LAYER_SLASH,
    TD_LAYER_MEH,
};

td_state_t cur_dance(tap_dance_state_t *state);

void esc_hyper_dance_finished(tap_dance_state_t *state, void *user_data);
void esc_hyper_dance_reset(tap_dance_state_t *state, void *user_data);
void lsft_meh_dance_finished(tap_dance_state_t *state, void *user_data);
void lsft_meh_dance_reset(tap_dance_state_t *state, void *user_data);
void lalt_eh_dance_finished(tap_dance_state_t *state, void *user_data);
void lalt_eh_dance_reset(tap_dance_state_t *state, void *user_data);

#endif
