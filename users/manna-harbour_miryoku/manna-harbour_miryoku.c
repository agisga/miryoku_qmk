// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"

enum layers { MIRYOKU_LAYER_NAMES };

//--- used for "super-alt-tab" and other custom macros
enum custom_keycodes {
  ONENOTE_ASDF = SAFE_RANGE,
  ONENOTE_QWER,
  AT_SPECIAL,
  AST_SPECIAL
};

bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.
//---

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE]   = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_BASE),
  [NAV]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_NAV),
  [MOUSE]  = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_MOUSE),
  [MEDIA]  = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_MEDIA),
  [NUM]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_NUM),
  [SYM]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_SYM),
  [FUN]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_FUN),
  [BUTTON] = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_BUTTON)
};

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(SYM, KC_ENT), LT(NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(NAV, KC_SPC), LT(MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN1, KC_BTN3, COMBO_END};
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
  QW_ESC,
  QZ_SCSHT,
  AZ_MUTE,
  SX_VOLDN,
  DC_VOLUP,
  FV_WSL,
  GB_WSR,
  ASDF_NOTE,
  QWER_NOTE,
  SD_AT,
  SDF_AST,
  ASD_WT,
  XCV_ACT,
  WX_CX,
  EC_CC,
  RV_CV,
  KL_CTRL,
};

const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM qz_combo[] = {KC_Q, KC_Z, COMBO_END};
const uint16_t PROGMEM az_combo[] = {KC_A, KC_Z, COMBO_END};
const uint16_t PROGMEM sx_combo[] = {KC_S, KC_X, COMBO_END};
const uint16_t PROGMEM dc_combo[] = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM fv_combo[] = {LSFT_T(KC_F), KC_V, COMBO_END};
const uint16_t PROGMEM gb_combo[] = {KC_G, KC_B, COMBO_END};
const uint16_t PROGMEM asdf_combo[] = {KC_A, KC_S, KC_D, LSFT_T(KC_F), COMBO_END};
const uint16_t PROGMEM qwer_combo[] = {KC_Q, KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM sdf_combo[] = {KC_S, KC_D, LSFT_T(KC_F), COMBO_END};
const uint16_t PROGMEM asd_combo[] = {KC_A, KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM xcv_combo[] = {KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM wx_combo[] = {KC_W, KC_X, COMBO_END};
const uint16_t PROGMEM ec_combo[] = {KC_E, KC_C, COMBO_END};
const uint16_t PROGMEM rv_combo[] = {KC_R, KC_V, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
//---

combo_t key_combos[COMBO_COUNT] = {
  //--- alexej's key-combos
  [QW_ESC] = COMBO(qw_combo, KC_ESC),
  [QZ_SCSHT] = COMBO(qz_combo, LGUI(LSFT(KC_S))),
  [AZ_MUTE] = COMBO(az_combo, KC_MUTE),
  [SX_VOLDN] = COMBO(sx_combo, KC_VOLD),
  [DC_VOLUP] = COMBO(dc_combo, KC_VOLU),
  [FV_WSL] = COMBO(fv_combo, LCTL(LGUI(KC_LEFT))),
  [GB_WSR] = COMBO(gb_combo, LCTL(LGUI(KC_RIGHT))),
  [ASDF_NOTE] = COMBO(asdf_combo, ONENOTE_ASDF),
  [QWER_NOTE] = COMBO(qwer_combo, ONENOTE_QWER),
  [SD_AT] = COMBO(sd_combo, AT_SPECIAL),
  [SDF_AST] = COMBO(sdf_combo, AST_SPECIAL),
  [ASD_WT] = COMBO(asd_combo, LGUI(KC_TAB)),
  [XCV_ACT] = COMBO(xcv_combo, LALT(LCTL(KC_TAB))),
  [WX_CX] = COMBO(wx_combo, LCTL(KC_X)),
  [EC_CC] = COMBO(ec_combo, LCTL(KC_C)),
  [RV_CV] = COMBO(rv_combo, LCTL(KC_V)),
  [KL_CTRL] = COMBO(kl_combo, OSM(MOD_LCTL)),
  //---
  #if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
    COMBO(thumbcombos_base_right, LT(FUN, KC_DEL)),
    COMBO(thumbcombos_base_left, LT(MOUSE, KC_ESC)),
    COMBO(thumbcombos_nav, KC_DEL),
    COMBO(thumbcombos_mouse, KC_BTN2),
    COMBO(thumbcombos_media, KC_MUTE),
    COMBO(thumbcombos_num, KC_DOT),
    #if defined (MIRYOKU_LAYERS_FLIP)
    // AG: I switched [ and ], so the if else is useless for now..
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
  }
return true;
}
