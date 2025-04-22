// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT(// MAIN
    KC_ESC,   KC_1,  KC_2,   KC_3,     KC_4,     KC_5,                                     KC_6,     KC_7,     KC_8,     KC_9,    KC_0,     KC_BSLS,
    KC_TAB,   KC_Q,  KC_W,   KC_E,     KC_R,     KC_T,                                     KC_Y,     KC_U,     KC_I,     KC_O,    KC_P,     KC_EQL,
    KC_LBRC,  KC_A,  KC_S,   KC_D,     KC_F,     KC_G,                                     KC_H,     KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_RBRC,
    KC_LSFT,  KC_Z,  KC_X,   KC_C,     KC_V,     KC_B,     KC_MPLY,       KC_DEL,          KC_N,     KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,
                             KC_LGUI,  KC_LALT,  KC_LCTL,  SH_T(KC_SPC),  LT(1, KC_ENT),   KC_BSPC,  KC_QUOT,  KC_MINS,  KC_GRV,  KC_NO
  ),
  LAYOUT( // FN
    KC_F11,   KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,                            KC_F6,    KC_F7,  KC_F8,    KC_F9,  KC_F10,   KC_F12,
    KC_F12,   KC_INS,   KC_HOME,  KC_UP,    KC_END,    KC_CAPS,                          KC_NUM,   KC_P7,  KC_P8,    KC_P9,  KC_PMNS,  RGB_MOD,
    KC_LCTL,  KC_BSPC,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_DEL,                           KC_PSLS,  KC_P4,  KC_P5,    KC_P6,  KC_PPLS,  RGB_TOG,
    KC_LSFT,  KC_MUTE,  KC_MRWD,  KC_MFFD,  KC_MPRV,   KC_MNXT,  KC_NO,       KC_NO,     KC_PAST,  KC_P1,  KC_P2,    KC_P3,  KC_PENT,  RGB_RMOD,
                        KC_MCTL,  KC_LPAD,  CG_TOGG,   TG(2),    KC_NO,       KC_BSPC,   KC_NO,    KC_P0,  KC_PDOT,  KC_NO
  ),
  LAYOUT( // GAME
    KC_TRNS,  KC_TRNS,  KC_TRNS,         KC_TRNS,  KC_TRNS,  KC_TRNS,                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,         KC_TRNS,  KC_TRNS,  KC_TRNS,                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,         KC_TRNS,  KC_TRNS,  KC_TRNS,                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                        LT(1, KC_ENT),   KC_TRNS,  KC_TRNS,  KC_SPC,   SH_MON,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  TG(2)
  )
};

bool is_swapped = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CG_TOGG:
            if (!record->event.pressed) {
                is_swapped = !is_swapped;
            }
        default:
            return true; // Process all other keycodes normally
    }
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write_P(PSTR("\n\n\n"), false);
    oled_write_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            if (is_swapped) {
                oled_write_ln_P(PSTR("MAC"), false);
            } else {
                oled_write_ln_P(PSTR("MAIN"), false);
            }
            break;
        case 1:
            oled_write_ln_P(PSTR("FUNC"), false);
            break;
          case 2:
            oled_write_ln_P(PSTR("GAME"), false);
            break;
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CAPS"), led_usb_state.caps_lock);
    oled_write_ln_P(PSTR("NUM"), led_usb_state.num_lock);
    oled_write_P(PSTR("\n\n"), false);
    return false;
  }
  
  return true;
}
#endif

#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif