// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"


//--- tap dance OSM(Shift) and Enter
// based on https://github.com/samhocevar-forks/qmk-firmware/blob/master/docs/feature_tap_dance.md#example-6-using-tap-dance-for-momentary-layer-switch-and-layer-toggle-keys

typedef struct {
  bool is_press_action;
  int state;
} tap;

//Define a type for as many tap dance states as you need
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

//Declare the functions to be used with your tap dance key(s)
int cur_dance (qk_tap_dance_state_t *state);
void ql_finished (qk_tap_dance_state_t *state, void *user_data);
void ql_reset (qk_tap_dance_state_t *state, void *user_data);
//---


//--- used for "super-alt-tab" and other custom macros
enum custom_keycodes {
  ONENOTE_ASDF = SAFE_RANGE,
  ONENOTE_QWER,
  AT_SPECIAL,
  AST_SPECIAL,
  KC_ELLIPSIS,
  KC_AUTOCLOS_PAREN,
  KC_AUTOCLOS_SQBRA,
  KC_AUTOCLOS_CURLYBRA,
  KC_AUTOCLOS_QUOTE,
  KC_AUTOCLOS_ANGLEBRA,
  KC_LATEX_PAREN,
  KC_LATEX_SQBRA,
  KC_LATEX_CURLYBRA,
  KC_QU,
  KC_COLONQ,
  KC_COLONWQ,
  KC_PARENQ,
  KC_DOTSPC,
  KC_COMMASPC,
};

bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.
//---


// Additional Features double tap guard
// Also, Alexej's custom tap dance

enum {
    OSM_LSFT_ENT, // custom tap dance
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

//Determine the current tap dance state
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 8;
}

//Initialize tap structure associated with tap dance key
static tap ql_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
// cont. tap dance for OSM shift and Enter
// based on https://github.com/samhocevar-forks/qmk-firmware/blob/master/docs/feature_tap_dance.md#example-6-using-tap-dance-for-momentary-layer-switch-and-layer-toggle-keys
// and https://www.reddit.com/r/olkb/comments/mxcm9p/tap_dance_to_mimic_two_oneshot_modifiers/
void ql_finished (qk_tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
  switch (ql_tap_state.state) {
    case SINGLE_TAP:
      set_oneshot_mods(MOD_BIT(KC_LSFT)); break;     // emulate OSM for Shift
    case SINGLE_HOLD:
      register_code(KC_LSFT); break;                // normal modifier (Shift) when held down
      //layer_on(U_SYM); break;                       // layer on when held down
    case DOUBLE_TAP:
      tap_code(KC_ENT); break;                      // Enter when tapped twice
  }
}

void ql_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ql_tap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: clear_oneshot_mods(); unregister_code(KC_LSFT); break;
    //case SINGLE_HOLD: clear_oneshot_mods(); layer_off(U_SYM);
    case DOUBLE_TAP: break;
  }
  ql_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [OSM_LSFT_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),  // Alexej's custom
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

// standard miryoku thumb combos, alexej's key-combos
// combo names are defined according to the qwerty layout

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
// alexej's key-combos
enum combos {
  AZ_MUTE,
  SX_VOLDN,
  DC_VOLUP,
  FV_WSL,
  GB_WSR,
};
const uint16_t PROGMEM az_combo[] = {LGUI_T(KC_A), LT(U_BUTTON,KC_QUOT), COMBO_END};
const uint16_t PROGMEM sx_combo[] = {LALT_T(KC_R), ALGR_T(KC_X), COMBO_END};
const uint16_t PROGMEM dc_combo[] = {LCTL_T(KC_S), KC_C, COMBO_END};
const uint16_t PROGMEM fv_combo[] = {LSFT_T(KC_T), KC_V, COMBO_END};
const uint16_t PROGMEM gb_combo[] = {KC_D, KC_B, COMBO_END};
// standard miryoku thumb combos
const uint16_t PROGMEM thumbcombos_base_right[] = {TD(OSM_LSFT_ENT), OSL(U_NUM), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_SPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_APP, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_UNDS, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_COLN, KC_SCLN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  // alexej's key-combos
  [AZ_MUTE] = COMBO(az_combo, KC_MUTE),
  [SX_VOLDN] = COMBO(sx_combo, KC_VOLD),
  [DC_VOLUP] = COMBO(dc_combo, KC_VOLU),
  [FV_WSL] = COMBO(fv_combo, LCTL(LGUI(KC_LEFT))),
  [GB_WSR] = COMBO(gb_combo, LCTL(LGUI(KC_RIGHT))),
  // standard miryoku thumb combos
  COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
  COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
  COMBO(thumbcombos_nav, KC_DEL),
  COMBO(thumbcombos_mouse, KC_BTN3),
  COMBO(thumbcombos_media, KC_MUTE),
  COMBO(thumbcombos_num, KC_DOT),
  #if defined (MIRYOKU_LAYERS_FLIP)
  COMBO(thumbcombos_sym, KC_RPRN),
  #else
  COMBO(thumbcombos_sym, KC_LPRN),
  #endif
  COMBO(thumbcombos_fun, KC_APP)
};
#endif

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
        case LGUI_T(KC_A):
            return 300;
        case LGUI_T(KC_O):
            return 300;
        case LT(U_MOUSE,KC_SPC):
            return 190;
        case LT(U_NAV,KC_SPC):
            return 190;
        case LT(U_MEDIA,KC_ESC):
            return 190;
        case LT(U_FUN,KC_DEL):
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
    case ONENOTE_ASDF:
      if (record->event.pressed) {
          SEND_STRING(SS_LWIN(SS_LSFT("n")) SS_DELAY(1000) SS_LCTL("e") SS_DELAY(100) "asdf" SS_DELAY(400) SS_TAP(X_ENT) SS_DELAY(100) SS_LCTL(SS_TAP(X_END)));
      }
      break;

    case ONENOTE_QWER:
      if (record->event.pressed) {
          SEND_STRING(SS_LWIN(SS_LSFT("n")) SS_DELAY(1000) SS_LCTL("e") SS_DELAY(100) "qwer" SS_DELAY(400) SS_TAP(X_ENT) SS_DELAY(100) SS_LCTL(SS_TAP(X_END)));
      }
      break;

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

    case AST_SPECIAL:
        if (record->event.pressed) {
            alt_tab_timer = timer_read();
            if(!is_alt_tab_active) {
                register_code(KC_LALT);
                is_alt_tab_active = true;
            }
            register_code(KC_LSFT);
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
            unregister_code(KC_LSFT);
        }
        break;

    case KC_ELLIPSIS:
      if (record->event.pressed) {
          SEND_STRING("(...)");
      }
      break;

    case KC_AUTOCLOS_PAREN:
      if (record->event.pressed) {
          SEND_STRING("()" SS_TAP(X_LEFT));
      }
      break;

    case KC_AUTOCLOS_SQBRA:
      if (record->event.pressed) {
          SEND_STRING("[]" SS_TAP(X_LEFT));
      }
      break;

    case KC_AUTOCLOS_CURLYBRA:
      if (record->event.pressed) {
          SEND_STRING("{}" SS_TAP(X_LEFT));
      }
      break;

    case KC_AUTOCLOS_QUOTE:
      if (record->event.pressed) {
          SEND_STRING("\"\"" SS_TAP(X_LEFT));
      }
      break;

    case KC_AUTOCLOS_ANGLEBRA:
      if (record->event.pressed) {
          SEND_STRING("<>" SS_TAP(X_LEFT));
      }
      break;

    case KC_LATEX_PAREN:
      if (record->event.pressed) {
          SEND_STRING("\\left(\\right)" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
      }
      break;

    case KC_LATEX_SQBRA:
      if (record->event.pressed) {
          SEND_STRING("\\left[\\right]" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
      }
      break;

    case KC_LATEX_CURLYBRA:
      if (record->event.pressed) {
          SEND_STRING("\\left\\{\\right\\}" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
      }
      break;

    case KC_QU:
      if (record->event.pressed) {
          SEND_STRING("qu");
      }
      break;

    case KC_COLONQ:
      if (record->event.pressed) {
          SEND_STRING(":q");
      }
      break;

    case KC_COLONWQ:
      if (record->event.pressed) {
          SEND_STRING(":wq");
      }
      break;

    case KC_PARENQ:
      if (record->event.pressed) {
          SEND_STRING("(?)");
      }
      break;

    case KC_DOTSPC:
      if (record->event.pressed) {
          SEND_STRING(". ");
      }
      break;

    case KC_COMMASPC:
      if (record->event.pressed) {
          SEND_STRING(", ");
      }
      break;
  }
return true;
}
