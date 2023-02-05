// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"


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


//--- used for "super-alt-tab" and other custom macros
enum custom_keycodes {
  ONENOTE_ASDF = SAFE_RANGE,
  ONENOTE_QWER,
  AT_SPECIAL,
  AST_SPECIAL,
  KC_ELLIPSIS,
  AUTOCLOS_PAREN,
  AUTOCLOS_SQBRA,
  AUTOCLOS_CURLYBRA,
  AUTOCLOS_QUOTE,
  LATEX_PAREN,
  LATEX_SQBRA,
  LATEX_CURLYBRA,
};

bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.
//---

// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    NULL
};


// thumb combos

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {OSM(MOD_LSFT), OSL(U_NUM), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_SPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_APP, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_RPRN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
#endif

//--- alexej's key-combos
// combo names are defined according to the qwerty layout
enum combos {
  QZ_SCSHT,
  AZ_MUTE,
  SX_VOLDN,
  DC_VOLUP,
  FV_WSL,
  GB_WSR,
  ASDF_NOTE,
  QWER_NOTE,
  SDF_AT,
  XC_ENT,
  WE_BSPC,
  FG_PAREN,
  RT_SQBR,
  VB_CRBR,
  DFG_LPAREN,
  ERT_LSQBR,
  CVB_LCRBR,
  DOTCOMMA,
  DOTCOMMAQ,
  HJ_QUOTE,
  IO_TAB,
  KDOT_CDEL,
  JKL_CBSPC,
};

const uint16_t PROGMEM qz_combo[] = {KC_Q, ALGR_T(KC_Z), COMBO_END};
const uint16_t PROGMEM az_combo[] = {LGUI_T(KC_A), ALGR_T(KC_Z), COMBO_END};
const uint16_t PROGMEM sx_combo[] = {LALT_T(KC_R), KC_X, COMBO_END};
const uint16_t PROGMEM dc_combo[] = {LCTL_T(KC_S), KC_C, COMBO_END};
const uint16_t PROGMEM fv_combo[] = {LSFT_T(KC_T), LT(U_SYM,KC_V), COMBO_END};
const uint16_t PROGMEM gb_combo[] = {KC_D, KC_B, COMBO_END};
const uint16_t PROGMEM asdf_combo[] = {LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM qwer_combo[] = {KC_Q, KC_W, LT(U_SYM,KC_F), KC_P, COMBO_END};
const uint16_t PROGMEM sdf_combo[] = {LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, LT(U_SYM,KC_F), COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM fg_combo[] = {LSFT_T(KC_T), KC_D, COMBO_END};
const uint16_t PROGMEM rt_combo[] = {KC_P, KC_G, COMBO_END};
const uint16_t PROGMEM vb_combo[] = {LT(U_SYM,KC_V), KC_B, COMBO_END};
const uint16_t PROGMEM dfg_combo[] = {LCTL_T(KC_S), LSFT_T(KC_T), KC_D, COMBO_END};
const uint16_t PROGMEM ert_combo[] = {LT(U_SYM,KC_F), KC_P, KC_G, COMBO_END};
const uint16_t PROGMEM cvb_combo[] = {KC_C, LT(U_SYM,KC_V), KC_B, COMBO_END};
const uint16_t PROGMEM dotcomma_combo[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM dotcommaq_combo[] = {KC_COMMA, KC_DOT, LT(U_BUTTON,KC_SLSH), COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, LSFT_T(KC_N), COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM kdot_combo[] = {LCTL_T(KC_E), KC_DOT, COMBO_END};
const uint16_t PROGMEM jkl_combo[] = {LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), COMBO_END};
//---

combo_t key_combos[COMBO_COUNT] = {
  //--- alexej's key-combos
  [QZ_SCSHT] = COMBO(qz_combo, LGUI(LSFT(KC_S))),
  [AZ_MUTE] = COMBO(az_combo, KC_MUTE),
  [SX_VOLDN] = COMBO(sx_combo, KC_VOLD),
  [DC_VOLUP] = COMBO(dc_combo, KC_VOLU),
  [FV_WSL] = COMBO(fv_combo, LCTL(LGUI(KC_LEFT))),
  [GB_WSR] = COMBO(gb_combo, LCTL(LGUI(KC_RIGHT))),
  [ASDF_NOTE] = COMBO(asdf_combo, ONENOTE_ASDF),
  [QWER_NOTE] = COMBO(qwer_combo, ONENOTE_QWER),
  [SDF_AT] = COMBO(sdf_combo, AT_SPECIAL),
  [WE_BSPC] = COMBO(we_combo, KC_BSPC),
  [XC_ENT] = COMBO(xc_combo, KC_ENT),
  [FG_PAREN] = COMBO(fg_combo, AUTOCLOS_PAREN),
  [RT_SQBR] = COMBO(rt_combo, AUTOCLOS_SQBRA),
  [VB_CRBR] = COMBO(vb_combo, AUTOCLOS_CURLYBRA),
  [DFG_LPAREN] = COMBO(dfg_combo, LATEX_PAREN),
  [ERT_LSQBR] = COMBO(ert_combo, LATEX_SQBRA),
  [CVB_LCRBR] = COMBO(cvb_combo, LATEX_CURLYBRA),
  [DOTCOMMA] = COMBO(dotcomma_combo, KC_ESC),
  [DOTCOMMAQ] = COMBO(dotcommaq_combo, KC_ELLIPSIS),
  [HJ_QUOTE] = COMBO(hj_combo, AUTOCLOS_QUOTE),
  [IO_TAB] = COMBO(io_combo, KC_TAB),
  [KDOT_CDEL] = COMBO(kdot_combo, LCTL(KC_DEL)),
  [JKL_CBSPC] = COMBO(jkl_combo, LCTL(KC_BSPC)),
  //---
  #if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
    COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
    COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
    COMBO(thumbcombos_nav, KC_DEL),
    COMBO(thumbcombos_mouse, KC_BTN3),
    COMBO(thumbcombos_media, KC_MUTE),
    COMBO(thumbcombos_num, KC_DOT),
    #if defined (MIRYOKU_LAYERS_FLIP)
    // AG: I switched ( and ), so the if else is useless for now..
    COMBO(thumbcombos_sym, KC_LPRN),
    #else
    COMBO(thumbcombos_sym, KC_LPRN),
    #endif
    COMBO(thumbcombos_fun, KC_PSCR)
  #endif
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

    case AUTOCLOS_PAREN:
      if (record->event.pressed) {
          SEND_STRING("()" SS_TAP(X_LEFT));
      }
      break;

    case AUTOCLOS_SQBRA:
      if (record->event.pressed) {
          SEND_STRING("[]" SS_TAP(X_LEFT));
      }
      break;

    case AUTOCLOS_CURLYBRA:
      if (record->event.pressed) {
          SEND_STRING("{}" SS_TAP(X_LEFT));
      }
      break;

    case AUTOCLOS_QUOTE:
      if (record->event.pressed) {
          SEND_STRING("\"\"" SS_TAP(X_LEFT));
      }
      break;

    case LATEX_PAREN:
      if (record->event.pressed) {
          SEND_STRING("\\left(\\right)" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
      }
      break;

    case LATEX_SQBRA:
      if (record->event.pressed) {
          SEND_STRING("\\left[\\right]" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
      }
      break;

    case LATEX_CURLYBRA:
      if (record->event.pressed) {
          SEND_STRING("\\left\\{\\right\\}" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
      }
      break;
  }
return true;
}
