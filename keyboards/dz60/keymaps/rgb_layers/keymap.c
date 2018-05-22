#include "dz60.h"

// Keycode Definitions
#define ______ KC_TRNS
#define XXXXXX KC_NO

// Layer Definitions
#define _L0 0
#define _L1 1
#define _L2 2
#define _L3 3

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Base layer
[_L0] = LAYOUT(
		F(0), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, XXXXXX, KC_BSPC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, XXXXXX, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(_L1),
		KC_LCTL, KC_LGUI, KC_LALT, XXXXXX, KC_SPC, XXXXXX, KC_RALT, KC_RGUI, XXXXXX, MO(_L2), KC_RCTL),

// Function layer
[_L1] = LAYOUT(
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, XXXXXX, KC_DEL,
		RESET, ______, KC_UP, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		KC_PSCR, KC_LEFT, KC_DOWN, KC_RIGHT, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		______, XXXXXX, ______, ______, ______, ______, ______, ______, ______, ______, KC_VOLD, KC_VOLU, KC_MUTE, ______,
		______, ______, ______, XXXXXX, ______, XXXXXX, ______, ______, XXXXXX, ______, ______),

// RGB layer
[_L2] = LAYOUT(
		RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______, ______, ______, ______, ______, XXXXXX, ______,
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		______, XXXXXX, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		______, ______, ______, XXXXXX, ______, XXXXXX, ______, ______, XXXXXX, ______, ______),

// Extra layer
[_L3] = LAYOUT(
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, XXXXXX, ______,
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		______, XXXXXX, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
		______, ______, ______, XXXXXX, ______, XXXXXX, ______, ______, XXXXXX, ______, ______),

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

// RGB update code
void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
     rgblight_sethsv_at(0, 255, 255, 0);     
     rgblight_sethsv_at(0, 255, 255, 14);
	 rgblight_sethsv_at(0, 255, 255, 15);
  } else {
    if (biton32(layer_state) == _L0) {
       rgblight_sethsv_at(180, 255, 128, 0);
       rgblight_sethsv_at(180, 255, 128, 14);
	   rgblight_sethsv_at(180, 255, 128, 15);
    }
  }
}

// Mute RGB code
static bool mute_toggle;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      switch (keycode) {
      case KC_MUTE:
        if (!record->event.pressed) { mute_toggle = !mute_toggle; }
        if (mute_toggle) {
          rgblight_sethsv_at(0, 255, 255, 7);
          rgblight_sethsv_at(0, 255, 255, 8);
          rgblight_sethsv_at(0, 255, 255, 9);
        } else { 
          rgblight_sethsv_at(180, 255, 128, 7);
          rgblight_sethsv_at(180, 255, 128, 8);
          rgblight_sethsv_at(180, 255, 128, 9);
        }
        return true;
      default:
        return true;
      }
  }

// RGB Modes & Colors https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h
// 1 = Static
// 2-5 = Breathing
// 6-8 = Rainbow
// 9-14 = Swirl
// 15-20 = Snake
// 21-24 = Nightrider
// 25 = Christmas
// 26-30 = Static Gradient


// RGB Layers w/Capslock & Mute RGB indicators
uint8_t prev = _L0;
uint32_t desired = 1;
uint16_t hue = 180;
uint16_t sat = 255;
uint16_t val = 128;

void get_hsv(void) {
    hue = rgblight_get_hue();
    sat = rgblight_get_sat();
    val = rgblight_get_val();
}

void reset_hsv(void) {
    rgblight_sethsv(hue, sat, val);
}

void matrix_init_user() {
    rgblight_mode(desired);
    rgblight_enable();
    reset_hsv();
}

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  if (prev!=_L3) {
      switch (layer) {
        case _L0:
          rgblight_sethsv(180, 255, 128);
          rgblight_mode(1);
          if (host_keyboard_leds()  & (1<<USB_LED_CAPS_LOCK) ) {
            rgblight_sethsv_at(0, 255, 255, 0);
            rgblight_sethsv_at(0, 255, 255, 14);
            rgblight_sethsv_at(0, 255, 255, 15);
          }
          if (mute_toggle) {
            rgblight_sethsv_at(0, 255, 255, 7);
            rgblight_sethsv_at(0, 255, 255, 8);
            rgblight_sethsv_at(0, 255, 255, 9);
          } else {
            rgblight_sethsv_at(180, 255, 128, 7);
            rgblight_sethsv_at(180, 255, 128, 8);
            rgblight_sethsv_at(180, 255, 128, 9);
          }
          break;

        case _L1:
          rgblight_mode(1);
          rgblight_sethsv(150, 255, 255);
          break;

        case _L2:
          rgblight_mode(1);
          rgblight_sethsv( 16, 176, 255);
          break;

        case _L3:
          rgblight_mode(5);
          rgblight_sethsv( 16, 176, 255);
          break;

      }
  } else {
      desired = rgblight_get_mode();
      get_hsv();
  }
  prev = layer;
  return state;
}