/* Copyright 2020 gtips
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

// tap dance declaration
enum {
  TD_UP1_UP2,
};

// tap dance declarations
qk_tap_dance_action_t tap_dance_actions[] = {
  // tap once for layer 1, twice for layer 2
  [TD_UP1_UP2] = ACTION_TAP_DANCE_DOUBLE(MO(_UP1), MO(_UP2))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung41( // qwerty, base layer
    KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,     KC_T,                    KC_Y,            KC_U,           KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_LSPO,  KC_A,   KC_S,   KC_D,   KC_F,     KC_G,                    KC_H,            KC_J,           KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_RCPC,  KC_Z,   KC_X,   KC_C,   KC_V,     KC_B,                    KC_N,            KC_M,           KC_COMM,  KC_DOT,   KC_SLSH,  KC_SFTENT,
                                      KC_LGUI,  TT(_LOW), LT(_ADJ,KC_SPC), TD(TD_UP1_UP2),  RALT_T(KC_ESC)
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


// Light LED 11 RED when LOW is active
const rgblight_segment_t PROGMEM my_low_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_RED}
);
// Light LED 11 CYAN when UP1 is active
const rgblight_segment_t PROGMEM my_up1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_CYAN}
);
// Light LED 11 PURPLE when UP2 is active
const rgblight_segment_t PROGMEM my_up2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_PURPLE}
);
// Light LED 11 GREEN when ADJ is active
const rgblight_segment_t PROGMEM my_adj_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_GREEN}
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
