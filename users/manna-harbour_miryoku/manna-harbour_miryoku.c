// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"


//--- used for "super-alt-tab" and other custom macros
enum custom_keycodes {
  AT_SPECIAL = SAFE_RANGE,
};

bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.
//---


// Additional Features double tap guard

enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

void u_td_fn_boot(qk_tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) {
    reset_keyboard();
  }
}

#define MIRYOKU_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(qk_tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

qk_tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    NULL
};


//--- per key tapping terms
// shorter tapping terms for thumb keys and shift
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_T):
            return 190;
        case LSFT_T(KC_N):
            return 190;
        case LSFT_T(KC_F):
            return 190;
        case LSFT_T(KC_J):
            return 190;
        case LT(U_MOUSE,KC_SPC):
            return 190;
        case LT(U_NAV,KC_SPC):
            return 190;
        case LT(U_MEDIA,KC_ESC):
            return 190;
        default:
            return TAPPING_TERM;
    }
}




//--- "super-alt-tab" and other custom macros

void matrix_scan_user(void) {     // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 500) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case AT_SPECIAL:
        if (record->event.pressed) {
            alt_tab_timer = timer_read();
            if(!is_alt_tab_active) {
                register_code(KC_LALT);
                is_alt_tab_active = true;
            }
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        break;
  }
return true;
}
