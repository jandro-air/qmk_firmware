/*
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

enum layer_names {
    _BASE,
    _LOW,
    _UP1,
    _UP2,
    _ADJ
};

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    DBL_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum 
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung41( // qwerty, base layer
    KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,     KC_T,                    KC_Y,            KC_U,           KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_LSPO,  KC_A,   KC_S,   KC_D,   KC_F,     KC_G,                    KC_H,            KC_J,           KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_RCPC,  KC_Z,   KC_X,   KC_C,   KC_V,     KC_B,                    KC_N,            KC_M,           KC_COMM,  KC_DOT,   KC_SLSH,  KC_SFTENT,
                                      KC_LGUI,  TT(_LOW), LT(_ADJ,KC_SPC), TD(DBL_LAYR),  RALT_T(KC_ESC)
  ),

  [_LOW] = LAYOUT_reviung41( // numpad
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_GRV,             KC_ASTR,  KC_7,   KC_8,   KC_9,   XXXXXXX,   _______,
    _______,  XXXXXXX,  KC_LBRC,  XXXXXXX,  KC_RBRC,  KC_MINS,            KC_EQL,   KC_4,   KC_5,   KC_6,   _______,   _______,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DEL,             KC_0,     KC_1,   KC_2,   KC_3,   KC_BSLS,   _______,
                                            _______,  _______,  KC_BSPC,  KC_RSFT,  _______
  ),

  [_UP1] = LAYOUT_reviung41( // nav and media keys
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  KC_KB_VOLUME_UP,  KC_UP,    KC_KB_VOLUME_DOWN,  XXXXXXX,   _______,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  KC_LEFT,          KC_DOWN,  KC_RIGHT,           XXXXXXX,   XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  KC_MPRV,          KC_MPLY,  KC_MNXT,            XXXXXXX,   _______,
                                            _______,   _______,  _______,  _______,  _______
  ),

  [_UP2] = LAYOUT_reviung41( // nav and media keys pt 2
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  _______,  KC_PGUP,  _______,  XXXXXXX,   _______,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  KC_HOME,  KC_PGDN,  KC_END,   XXXXXXX,   _______,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  _______,  _______,  _______,  XXXXXXX,   _______,
                                            _______,   _______,  _______,  _______,  _______
  ),

  [_ADJ] = LAYOUT_reviung41( // RGB and keyboard modifiers
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  RESET,   XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            XXXXXXX,   XXXXXXX,  _______,  XXXXXXX,  XXXXXXX
  )
};


// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
	if (!state->pressed) return TD_DOUBLE_TAP;
	else return TD_DOUBLE_HOLD;
    }
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(_UP1);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_UP2);
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_UP1);
    } else if (ql_tap_state.state == TD_DOUBLE_HOLD) {
        layer_off(_UP2);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [DBL_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};



// Light LED 11 RED when LOW is active
const rgblight_segment_t PROGMEM my_low_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 2, HSV_AZURE}
);
// Light LED 11 CYAN when UP1 is active
const rgblight_segment_t PROGMEM my_up1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 2, HSV_ORANGE}
);
// Light LED 11 PURPLE when UP2 is active
const rgblight_segment_t PROGMEM my_up2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 2, HSV_MAGENTA}
);
// Light LED 11 GREEN when ADJ is active
const rgblight_segment_t PROGMEM my_adj_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 2, HSV_GOLD}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_low_layer,
    my_up1_layer,
    my_up2_layer,
    my_adj_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _LOW));
    rgblight_set_layer_state(1, layer_state_cmp(state, _UP1));
    rgblight_set_layer_state(2, layer_state_cmp(state, _UP2));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJ));
    return state;
}
