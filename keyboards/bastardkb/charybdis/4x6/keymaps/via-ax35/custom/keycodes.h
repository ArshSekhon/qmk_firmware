#pragma once
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H


enum layer_names {
    BASE = 0,
    NAV,
    NUM,
    // SYM,
    MOUSE,
    FUN,
    MEDIA,
    CODE
};

enum custom_keycodes {
    // Editing actions
    AX_COPY = SAFE_RANGE,
    AX_PASTE,
    AX_CUT,
    AX_LOCK,
    AX_UNDO,
    AX_REDO,



    // Screenshot + Screen Recording
    AX_SCRNSHT_TO_CLIP,
    AX_SCRNSHT,
    AX_SCREEN_RECORD,

    AX_INDICATE_OS,

    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_SHFT,
    OS_HYPER,
    OS_MEH
};



#define KC_SCLN_MEH MEH_T(KC_SCLN)
#define KC_TO_SYM TO(SYM)

#define BSP_FN LT(FUN, KC_BSPC)
#define SHFT_SPC LSFT_T(KC_SPC)
#define TAB_NUM LT(NUM, KC_TAB)
#define GESC_MOUSE LT(MOUSE, QK_GESC)
#define QUOT_NAV LT(NAV, KC_QUOT)
#define SPC_CODE LT(CODE, KC_SPC)




#define MS_L KC_BTN1
#define MS_R KC_BTN2
#define MS_M KC_BTN3

#define WH_L KC_MS_WH_LEFT
#define WH_R KC_MS_WH_RIGHT
#define WH_D KC_MS_WH_DOWN
#define WH_U KC_MS_WH_UP

