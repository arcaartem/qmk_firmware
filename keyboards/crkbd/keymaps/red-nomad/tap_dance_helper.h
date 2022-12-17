#ifndef TAP_DANCE_HELPER__H
#define TAP_DANCE_HELPER__H

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_LSFT_HYPR,
    TD_LALT_MEH,
    TD_LALT_RALT,
    TD_RALT_MEH,
    TD_RALT_GUI,
    TD_LAYER_QUOTE,
    TD_LAYER_SLASH,
    TD_LAYER_MEH,
    TD_OLED_TOGGLE,
};

td_state_t cur_dance(tap_dance_state_t *state);

void layer_slash_dance_finished(tap_dance_state_t *state, void *user_data);
void layer_slash_dance_reset(tap_dance_state_t *state, void *user_data);
void oled_toggle_dance_finished(tap_dance_state_t *state, void *user_data);
void oled_toggle_dance_reset(tap_dance_state_t *state, void *user_data);
void lsft_hyper_dance_finished(tap_dance_state_t *state, void *user_data);
void lsft_hyper_dance_reset(tap_dance_state_t *state, void *user_data);
void lalt_meh_dance_finished(tap_dance_state_t *state, void *user_data);
void lalt_meh_dance_reset(tap_dance_state_t *state, void *user_data);

#endif
