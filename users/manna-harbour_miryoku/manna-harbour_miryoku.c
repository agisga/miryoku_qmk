// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"

enum layers { MIRYOKU_LAYER_NAMES };

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
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(SYM, KC_SPC), LT(NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(NAV, KC_ENT), LT(MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_SPC, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN1, KC_BTN3, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_ENT, KC_TAB, COMBO_END};
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
};

const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM qz_combo[] = {KC_Q, LT(BUTTON, KC_Z), COMBO_END};
const uint16_t PROGMEM az_combo[] = {LGUI_T(KC_A), LT(BUTTON, KC_Z), COMBO_END};
const uint16_t PROGMEM sx_combo[] = {LALT_T(KC_S), ALGR_T(KC_X), COMBO_END};
const uint16_t PROGMEM dc_combo[] = {LCTL_T(KC_D), KC_C, COMBO_END};
const uint16_t PROGMEM fv_combo[] = {LSFT_T(KC_F), KC_V, COMBO_END};
const uint16_t PROGMEM gb_combo[] = {KC_G, KC_B, COMBO_END};
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
  //---
  #if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
    COMBO(thumbcombos_base_right, LT(FUN, KC_DEL)),
    COMBO(thumbcombos_base_left, LT(MEDIA, KC_ESC)),
    COMBO(thumbcombos_nav, KC_DEL),
    COMBO(thumbcombos_mouse, KC_BTN2),
    COMBO(thumbcombos_media, KC_MUTE),
    COMBO(thumbcombos_num, KC_DOT),
    #if defined (MIRYOKU_LAYERS_FLIP)
    COMBO(thumbcombos_sym, KC_RPRN),
    #else
    COMBO(thumbcombos_sym, KC_LPRN),
    #endif
    COMBO(thumbcombos_fun, KC_APP)
  #endif
};
