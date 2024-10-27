// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// Tap Dance declarations
enum {
  GUI_GAME,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
  [GUI_GAME] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LGUI, 3),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT(
    KC_ESC,         KC_1,  KC_2,          KC_3,     KC_4,     KC_5,                                KC_6,     KC_7,     KC_8,     KC_9,    KC_0,     KC_BSLS,
    KC_TAB,         KC_Q,  KC_W,          KC_E,     KC_R,     KC_T,                                KC_Y,     KC_U,     KC_I,     KC_O,    KC_P,     KC_EQL,
    SH_T(KC_LBRC),  KC_A,  KC_S,          KC_D,     KC_F,     KC_G,                                KC_H,     KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_RBRC,
    KC_LSFT,        KC_Z,  KC_X,          KC_C,     KC_V,     KC_B,    KC_MPLY,          KC_DEL,   KC_N,     KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,
                           TD(GUI_GAME),  KC_LALT,  KC_LCTL,  KC_SPC,  LT(1, KC_ENT),    KC_BSPC,  KC_QUOT,  KC_MINS,  KC_GRV,   TG(2) 
  ),
  LAYOUT( //FN
    KC_F11,   KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,                            KC_F6,    KC_F7,  KC_F8,    KC_F9,  KC_F10,   KC_F12,
    KC_F12,   KC_INS,   KC_HOME,  KC_UP,    KC_END,    KC_CAPS,                          KC_NUM,   KC_P7,  KC_P8,    KC_P9,  KC_PMNS,  RGB_MOD,
    KC_LCTL,  KC_BSPC,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_DEL,                           KC_PSLS,  KC_P4,  KC_P5,    KC_P6,  KC_PPLS,  RGB_TOG,
    KC_LSFT,  KC_MUTE,  KC_MRWD,  KC_MFFD,  KC_MPRV,   KC_MNXT,  KC_NO,       KC_NO,     KC_PAST,  KC_P1,  KC_P2,    KC_P3,  KC_PENT,  RGB_RMOD,
                        KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,       KC_BSPC,   KC_NO,    KC_P0,  KC_PDOT,  KC_NO
  ),
  LAYOUT( //ARR
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                          KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,   KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                          KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,
                        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  TG(2) 
  ),
  LAYOUT( //GAME  
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                               KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                               KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                               KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  SH_T(KC_ENT),      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS 
  )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write_P(PSTR("\n\n\n"), false);
    oled_write_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("MAIN"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("FN"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("ARR"), false);
            break;
        case 3:
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