#include QMK_KEYBOARD_H
#include "definitions.h"
#include "layers/layers.h"
#include "os_specific/os_specific.h"
#include "oneshot/oneshot.h"
#include "os_detection.h"

// #define KEYBOARD_bastardkb_charybdis_3x5 1

tap_dance_action_t tap_dance_actions[] = {};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = CHARYBDIS_LAYOUT_wrapper(MOUSE_MOD(MEDIA_MOD(BASE_LAYER))),
  [NAV] = CHARYBDIS_LAYOUT_wrapper(NAV_LAYER),
  [NUM] = CHARYBDIS_LAYOUT_wrapper(NUM_LAYER),
  [SYM] = CHARYBDIS_LAYOUT_wrapper(SYM_LAYER),
  [MOUSE] = CHARYBDIS_LAYOUT_wrapper(MOUSE_LAYER),
  [FUN] = CHARYBDIS_LAYOUT_wrapper(FUN_LAYER),
  [MEDIA] = CHARYBDIS_LAYOUT_wrapper(MEDIA_LAYER),
  [CODE] = CHARYBDIS_LAYOUT_wrapper(CODE_LAYER)
};




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
    case ESC_SYM:
    case SPC_NUM:
    case KC_LSFT:
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
      if (record->event.pressed) { os_specific_copy(); }
      return false; // Skip all further processing of this key

    case AX_PASTE:
      if (record->event.pressed) { os_specific_paste(); }
      return false;

    case AX_UNDO:
      if (record->event.pressed) { os_specific_undo(); }
      return false;

    case AX_REDO:
      if (record->event.pressed) { os_specific_redo(); }
      return false;

    case AX_CUT:
      if (record->event.pressed) { os_specific_cut(); }
      return false;

    case AX_LOCK:
      if (record->event.pressed) { os_specific_lock(); }
      return false;

    case AX_SCRNSHT:
      if (record->event.pressed) { os_specific_screenshot(); }
      return false;

    case AX_SCRNSHT_TO_CLIP:
      if (record->event.pressed) { os_specific_screenshot_to_clipboard(); }
      return false;

    case AX_SCREEN_RECORD:
      if (record->event.pressed) { os_specific_record(); }
      return false;

    case AX_INDICATE_OS:
      if (record->event.pressed) { os_specific_indicate_os(); }
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
