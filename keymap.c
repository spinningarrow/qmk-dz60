#include "dz60.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define ______ KC_TRNS
#define BASE 0
#define F_KEYS 1
#define F_APPLE 2

enum {
  TD_GUI_LCAG = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_2_shifts(
       KC_GRV,        KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, TT(F_APPLE),
       KC_TAB,        KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,
       CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,
       KC_LSPO,       ______,  KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSPC, KC_UP,   TT(F_KEYS),
       KC_MEH,       KC_LALT, KC_LGUI, KC_SPC, KC_SPC, KC_SPC, KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT
  ),

  [F_KEYS] = LAYOUT_2_shifts(
      KC_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,  ______,  ______,
      ______, RGB_MOD, ______,  ______,  RESET,   ______, ______, ______, ______, ______, ______, RGB_VAI, RGB_VAD, RGB_TOG,
      ______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, ______, ______, ______, ______, ______, ______, ______,  ______,
      ______, ______,  ______,  ______,  ______,  ______, ______, ______, ______, ______, ______, ______,  ______,  ______,  ______,
      ______, ______,  ______,  ______,  ______,  ______, ______, ______, ______, ______, ______
  ),

  [F_APPLE] = LAYOUT_2_shifts(
      ______, KC_F14, KC_F15, ______, ______, ______, ______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,  ______,  ______,  ______,  ______,
      ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,  ______,  ______,  ______,
      ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,  ______,  ______,  ______,  ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,  ______
  ),
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GUI_LCAG] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_HYPR)
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case F_KEYS:
      rgblight_mode(1);
      rgblight_sethsv(90, 200, 75);
      break;

    case F_APPLE:
      rgblight_mode(1);
      rgblight_sethsv(30, 180, 80);
      break;

    default:
      rgblight_mode(1); // static colour
      rgblight_setrgb(0, 0, 0);
      break;

  }

  return state;
}
