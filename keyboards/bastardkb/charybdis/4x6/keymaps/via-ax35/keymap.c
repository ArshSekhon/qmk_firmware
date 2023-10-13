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
#include "./custom/keycodes.h"
#include "./layers/layers.h"
#include "oneshot/oneshot.h"
#include  "os_detection.h"
#include  "print.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

// Automatically enable sniping-mode on the pointer layer.

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI


#define LAYOUT_wrapper(...) _LAYOUT_wrapper(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_3x5_to_4x5_adapter(BASE_LAYER),
  [FUN] = LAYOUT_3x5_to_4x5_adapter(FUN_LAYER),
  [NUM] = LAYOUT_3x5_to_4x5_adapter(NUM_LAYER),
  [NAV] = LAYOUT_3x5_to_4x5_adapter(NAV_LAYER),
  [MOUSE] = LAYOUT_3x5_to_4x5_adapter(MOUSE_LAYER),
  [MEDIA] = LAYOUT_3x5_to_4x5_adapter(MEDIA_LAYER),
//   [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
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
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
}





bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case TO(BASE):
    case LT(NAV, KC_SPC):
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case BSP_FN:
    case ENT_NAV:
    case SHIFT_ESC:
    case SPC_CODE:
    case SHFT_SPC:
    case TAB_NUM:
    case GESC_MOUSE:
    case QUOT_NAV:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}


oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case AX_COPY:
      if (record->event.pressed) {
        // TODO: finish this
       }
      return false; // Skip all further processing of this key

    case AX_PASTE:
      if (record->event.pressed) {
        // TODO: finish this
       }
      return false;

    case AX_UNDO:
      if (record->event.pressed) {
        // TODO: finish this
       }
      return false;

    case AX_REDO:
      if (record->event.pressed) {
        // TODO: finish this
       }
      return false;

    case AX_CUT:
      if (record->event.pressed) {
        // TODO: finish this
       }
      return false;

    case AX_LOCK:
      if (record->event.pressed) {
        // TODO: finish this
       }
      return false;

    case AX_SCRNSHT:
      if (record->event.pressed) {
        // TODO: finish this
       }
      return false;

    case AX_SCRNSHT_TO_CLIP:
      if (record->event.pressed) {
        // TODO: finish this
       }
      return false;

    case AX_SCREEN_RECORD:
      if (record->event.pressed) {
        // TODO: finish this
       }
      return false;

    case AX_INDICATE_OS:
      if (record->event.pressed) {
        // TODO: finish this
       os_variant_t host_os = detected_host_os();
       if(host_os == OS_MACOS) {
        SEND_STRING("MACOS");
       } else if (host_os == OS_WINDOWS) {
        SEND_STRING("WINDOWS");
       } else if (host_os == OS_LINUX) {
        SEND_STRING("LINUX");
       } else if (host_os == OS_IOS) {
        SEND_STRING("IOS");
       } else if (host_os == OS_UNSURE) {
        SEND_STRING("UNSURE");
       }
      }
      return false;

    default:
      update_oneshot(
          &os_shft_state, KC_LSFT, OS_SHFT,
          keycode, record
      );
      update_oneshot(
          &os_ctrl_state, KC_LCTL, OS_CTRL,
          keycode, record
      );
      update_oneshot(
          &os_alt_state, KC_LALT, OS_ALT,
          keycode, record
      );
      update_oneshot(
          &os_cmd_state, KC_LCMD, OS_CMD,
          keycode, record
      );
      return true; // Process all other keycodes normally
  }
}


#if defined(POINTING_DEVICE_ENABLE) && defined(CHARYBDIS_AUTO_SNIPING_ON_LAYER)
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#endif // POINTING_DEVICE_ENABLE && CHARYBDIS_AUTO_SNIPING_ON_LAYER
