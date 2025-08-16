/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "keymap_uk.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FOCAL,
    LAYER_GAMING,
    LAYER_SYM,
    LAYER_NAV,
    LAYER_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_SYM)
#define RAISE MO(LAYER_NAV)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

#define THUMB_BSPC LT(LAYER_SYM, KC_BSPC)
#define THUMB_ENT LT(LAYER_NAV, KC_ENT)
#define THUMB_SPC LT(LAYER_SYM, KC_SPC)
#define NAV_E LT(LAYER_NAV, KC_E)
#define NAV_H LT(LAYER_NAV, KC_H)
#define HYPER C(S(G(KC_LALT)))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────╮
       KC_ESC,         UK_1,         UK_2,         UK_3,         UK_4,  UK_5,    UK_6,        UK_7,         UK_8,         UK_9,         UK_0,     UK_GRV,
  // ├───────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────┤
       KC_TAB,         UK_Q,         UK_W,        NAV_E,         UK_R,  UK_T,    UK_Y,        UK_U,         UK_I,         UK_O,         UK_P,     UK_MINS,
  // ├───────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────┤
       XXXXXXX, LCTL_T(UK_A), LALT_T(UK_S), LGUI_T(UK_D), LSFT_T(UK_F), UK_G,    UK_H, RSFT_T(UK_J), RGUI_T(UK_K), LALT_T(UK_L), RCTL_T(UK_SCLN), UK_QUOT,
  // ├───────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────┤
       XXXXXXX,        PT_Z,         UK_X,         UK_C,         UK_V,  UK_B,    UK_N,        UK_M,         UK_COMM,      UK_DOT,       PT_SLSH,  XXXXXXX,
  // ╰───────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────╯
                                              THUMB_BSPC, THUMB_ENT, HYPER,    HYPER,  THUMB_SPC,
                                                      XXXXXXX,       XXXXXXX,    XXXXXXX
  //          ╰──────────────────────────────────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [LAYER_FOCAL] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────╮    ╭──────────────────────────────────────────────────────────────────────────╮
       KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,   KC_TRNS,
  // ├───────────────────────────────────────────────────────────────────────┤    ├──────────────────────────────────────────────────────────────────────────┤
       KC_TRNS,     UK_V,         UK_L,        NAV_H,         UK_G,      UK_K,    UK_Q,        UK_F,         UK_O,         UK_U,         UK_J,     KC_TRNS,
  // ├───────────────────────────────────────────────────────────────────────┤    ├──────────────────────────────────────────────────────────────────────────┤
       KC_TRNS, LCTL_T(UK_S), LALT_T(UK_R), LGUI_T(UK_N), LSFT_T(UK_T),  UK_B,    UK_Y,    RSFT_T(UK_C), RGUI_T(UK_A), LALT_T(UK_E), RCTL_T(UK_I), KC_TRNS,
  // ├───────────────────────────────────────────────────────────────────────┤    ├──────────────────────────────────────────────────────────────────────────┤
       KC_TRNS,     PT_Z,         UK_X,         UK_M,         UK_D,      UK_P,    UK_QUOT,     UK_W,        UK_COMM,      UK_DOT,       PT_SLSH,   UK_SCLN,
  // ╰───────────────────────────────────────────────────────────────────────┤    ├──────────────────────────────────────────────────────────────────────────╯
                                   KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS,
                                             KC_TRNS, KC_TRNS,                     KC_TRNS
  //                            ╰────────────────────────────────────────────╯    ╰────────────────────────────────╯
  ),

  [LAYER_GAMING] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, UK_GRV,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, UK_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, UK_SCLN, UK_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, UK_COMM,  UK_DOT, UK_SLSH, KC_RCTL,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,  KC_TRNS,
                                           KC_TRNS, KC_TRNS,     KC_TRNS
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_SYM] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, UK_LBRC, UK_RBRC, UK_DQUO, XXXXXXX,   S(UK_BSLS), UK_LCBR, UK_RCBR, UK_TILD, UK_ASTR, UK_UNDS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,               UK_AMPR, UK_LPRN, UK_RPRN, UK_QUES, UK_COLN,  UK_DLR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,            UK_GRV,   KC_PEQL, UK_EXLM, UK_DQUO, UK_BSLS, UK_PLUS,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, KC_TRNS,    KC_TRNS, XXXXXXX,
                                           KC_TRNS, KC_TRNS,      KC_TRNS
  //                                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NAV] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,      XXXXXXX,  XXXXXXX, XXXXXXX,    XXXXXXX,      XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,     A(KC_LEFT), KC_UP, A(KC_RIGHT), XXXXXXX,      XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────┤
       XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,  C(S(G(KC_LEFT))), KC_LEFT, KC_DOWN, KC_RIGHT, C(S(G(KC_RIGHT))),  XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,    G(KC_LEFT), XXXXXXX, G(KC_RIGHT), XXXXXXX,     XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, KC_TRNS,    KC_TRNS, XXXXXXX,
                                           KC_TRNS, KC_TRNS,    KC_TRNS
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    TG(1),   TG(2),   XXXXXXX, XXXXXXX, QK_BOOT,  EE_CLR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    DT_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    DT_PRNT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    DT_DOWN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                           XXXXXXX, KC_BTN2,    KC_BTN2
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (current_layer == LAYER_FOCAL) {
        return TAPPING_TERM + 230;
    }
    return TAPPING_TERM;
}

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
                       'L', 'L', 'L',  'R', 'R',
                            'L', 'L',  'R'
    );
