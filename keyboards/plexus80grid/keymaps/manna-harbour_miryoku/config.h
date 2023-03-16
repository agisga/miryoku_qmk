// Copyright 2021 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29,\
N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39\
)\
LAYOUT_ortho_5x16(\
LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), XXX,  KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, XXX, LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0),\
K00,           K01,           K02,      K03,                K04,    XXX,  KC_P7,  KC_P8,   KC_P9,   KC_PPLS, XXX, K05,    K06,            K07,            K08,            K09,\
K10,           K11,           K12,      K13,                K14,    XXX,  KC_P4,  KC_P5,   KC_P6,   KC_COLN, XXX, K15,    K16,            K17,            K18,            K19,\
K20,           K21,           K22,      K23,                K24,    XXX,  KC_P1,  KC_P2,   KC_P3,   KC_PDOT, XXX, K25,    K26,            K27,            K28,            K29,\
KC_AST_SPECIAL,LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RIGHT)), K32, K33, K34,  KC_P0,  KC_MUTE, KC_VOLD, KC_VOLU, K35, K36,    XXX,            K37,            KC_WH_D,        KC_WH_U \
)
