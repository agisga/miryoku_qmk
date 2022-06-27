// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

// FIXME: There is a bug in this file. When making a new keyboard that was not already set up with a closer to default miryoku (e.g., `make draculad:manna-harbour_miryoku:dfu`), there are many error messages related to the key combos (e.g., `Error: 'COMBO_END' undeclared here (not in a function); did you mean 'COMBO_TERM'?`, `error: unknown type name 'combo_t'`). However, if we revert this file to its upstream version, then make and flash the new keyboard, and then change this file back to this current version, then after this process the `make` command executes with no errors and flashes the keyboard successfully.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


//--- key overrides (used for custom shift behaviour)
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t delete_mt_key_override = ko_make_basic(MOD_MASK_SHIFT, LT(U_NUM,KC_BSPC), KC_DEL);
const key_override_t tab_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_TAB);
const key_override_t tab_mt_key_override = ko_make_basic(MOD_MASK_SHIFT, LT(U_SYM,KC_SPC), KC_TAB);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    &delete_mt_key_override,
    &tab_key_override,
    &tab_mt_key_override,
    NULL // Null terminate the array of overrides!
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

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {OSM(MOD_LSFT), LT(U_NUM, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_SYM, KC_SPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
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
  ASD_WT,
  XCV_ACT,
  WX_CX,
  EC_CC,
  RV_CV,
  FG_PAREN,
  RT_SQBR,
  VB_CRBR,
  DFG_LPAREN,
  ERT_LSQBR,
  CVB_LCRBR,
  DOTCOMMAQ,
  HJ_QUOTE,
  KM_CBSPC,
  KDOT_CDEL,
  JKL_TAB,
};

const uint16_t PROGMEM qz_combo[] = {KC_Q, LT(U_BUTTON,KC_Z), COMBO_END};
const uint16_t PROGMEM az_combo[] = {LGUI_T(KC_A), LT(U_BUTTON,KC_Z), COMBO_END};
const uint16_t PROGMEM sx_combo[] = {LALT_T(KC_S), ALGR_T(KC_X), COMBO_END};
const uint16_t PROGMEM dc_combo[] = {LCTL_T(KC_D), KC_C, COMBO_END};
const uint16_t PROGMEM fv_combo[] = {LSFT_T(KC_F), KC_V, COMBO_END};
const uint16_t PROGMEM gb_combo[] = {KC_G, KC_B, COMBO_END};
const uint16_t PROGMEM asdf_combo[] = {LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), COMBO_END};
const uint16_t PROGMEM qwer_combo[] = {KC_Q, KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM sdf_combo[] = {LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), COMBO_END};
const uint16_t PROGMEM asd_combo[] = {LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), COMBO_END};
const uint16_t PROGMEM xcv_combo[] = {ALGR_T(KC_X), KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM wx_combo[] = {KC_W, ALGR_T(KC_X), COMBO_END};
const uint16_t PROGMEM ec_combo[] = {KC_E, KC_C, COMBO_END};
const uint16_t PROGMEM rv_combo[] = {KC_R, KC_V, COMBO_END};
const uint16_t PROGMEM fg_combo[] = {LSFT_T(KC_F), KC_G, COMBO_END};
const uint16_t PROGMEM rt_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM vb_combo[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM dfg_combo[] = {LCTL_T(KC_D), LSFT_T(KC_F), KC_G, COMBO_END};
const uint16_t PROGMEM ert_combo[] = {KC_E, KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM cvb_combo[] = {KC_C, KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM dotcommaq_combo[] = {KC_COMMA, ALGR_T(KC_DOT), LT(U_BUTTON,KC_SLSH), COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, LSFT_T(KC_J), COMBO_END};
const uint16_t PROGMEM km_combo[] = {LCTL_T(KC_K), KC_M, COMBO_END};
const uint16_t PROGMEM kdot_combo[] = {LCTL_T(KC_K), ALGR_T(KC_DOT), COMBO_END};
const uint16_t PROGMEM jkl_combo[] = {LALT_T(KC_L), LCTL_T(KC_K), LSFT_T(KC_J), COMBO_END};
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
  [ASD_WT] = COMBO(asd_combo, LGUI(KC_TAB)),
  [XCV_ACT] = COMBO(xcv_combo, LALT(LCTL(KC_TAB))),
  [WX_CX] = COMBO(wx_combo, LCTL(KC_X)),
  [EC_CC] = COMBO(ec_combo, LCTL(KC_C)),
  [RV_CV] = COMBO(rv_combo, LCTL(KC_V)),
  [FG_PAREN] = COMBO(fg_combo, AUTOCLOS_PAREN),
  [RT_SQBR] = COMBO(rt_combo, AUTOCLOS_SQBRA),
  [VB_CRBR] = COMBO(vb_combo, AUTOCLOS_CURLYBRA),
  [DFG_LPAREN] = COMBO(dfg_combo, LATEX_PAREN),
  [ERT_LSQBR] = COMBO(ert_combo, LATEX_SQBRA),
  [CVB_LCRBR] = COMBO(cvb_combo, LATEX_CURLYBRA),
  [DOTCOMMAQ] = COMBO(dotcommaq_combo, KC_ELLIPSIS),
  [HJ_QUOTE] = COMBO(hj_combo, AUTOCLOS_QUOTE),
  [KM_CBSPC] = COMBO(km_combo, LCTL(KC_BSPC)),
  [KDOT_CDEL] = COMBO(kdot_combo, LCTL(KC_DEL)),
  [JKL_TAB] = COMBO(jkl_combo, KC_TAB),
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
    COMBO(thumbcombos_fun, KC_APP)
  #endif
};


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
