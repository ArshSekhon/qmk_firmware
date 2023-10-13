#pragma once
#include QMK_KEYBOARD_H
#include "../custom/keycodes.h"

#define BSP_FN LT(FUN, KC_BSPC)
#define ENT_NAV LT(NAV, KC_ENT)
#define SHIFT_ESC LSFT_T(KC_ESC)
#define TAB_CODE LT(CODE, KC_TAB)
#define ESC_SYM LT(SYM, KC_ESC)
#define SPC_NUM LT(NUM, KC_SPC)
#define MOUSE_KEY(kc) LT(MOUSE, kc)
#define MEDIA_KEY(kc) LT(MEDIA, kc)



#define _KC_LAYOUT_wrapper(                                                                             \
         k00,      k01,      k02,      k03,      k04,      k05,      k06,      k07,      k08,      k09, \
         k10,      k11,      k12,      k13,      k14,      k15,      k16,      k17,      k18,      k19, \
         k20,      k21,      k22,      k23,      k24,      k25,      k26,      k27,      k28,      k29, \
         ...)                                                                                           \
    KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, \
    KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, \
    KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, \
    __VA_ARGS__
#define KC_LAYOUT_wrapper(...) _KC_LAYOUT_wrapper(__VA_ARGS__)

#define _KC_LAYOUT_L_wrapper(                                                                             \
         k00,      k01,      k02,      k03,      k04,      k05,      k06,      k07,      k08,      k09, \
         k10,      k11,      k12,      k13,      k14,      k15,      k16,      k17,      k18,      k19, \
         k20,      k21,      k22,      k23,      k24,      k25,      k26,      k27,      k28,      k29, \
         ...)                                                                                           \
    KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, k05, k06, k07, k08, k09, \
    KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, k15, k16, k17, k18, k19, \
    KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, k25, k26, k27, k28, k29, \
    __VA_ARGS__
#define KC_LAYOUT_L_wrapper(...) _KC_LAYOUT_L_wrapper(__VA_ARGS__)

#define _KC_LAYOUT_R_wrapper(                                                                             \
         k00,      k01,      k02,      k03,      k04,      k05,      k06,      k07,      k08,      k09, \
         k10,      k11,      k12,      k13,      k14,      k15,      k16,      k17,      k18,      k19, \
         k20,      k21,      k22,      k23,      k24,      k25,      k26,      k27,      k28,      k29, \
         ...)                                                                                           \
    k00, k01, k02, k03, k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, \
    k10, k11, k12, k13, k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, \
    k20, k21, k22, k23, k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, \
    __VA_ARGS__
#define KC_LAYOUT_R_wrapper(...) _KC_LAYOUT_R_wrapper(__VA_ARGS__)

#define _MOUSE_MOD(                                               \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,             \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,             \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,             \
    ...)                                                          \
            L00,        L01,        L02,        L03,        L04,  \
            R05,        R06,        R07,        R08,        R09,  \
            L10,        L11,        L12,        L13,        L14,  \
            R15,        R16,        R17,        R18,        R19,  \
      MOUSE_KEY(L20),       L21,        L22,        L23,        L24,  \
            R25,        R26,        R27,        R28,  MOUSE_KEY(R29), \
      __VA_ARGS__
#define MOUSE_MOD(...) _MOUSE_MOD(__VA_ARGS__)


#define _MEDIA_MOD(                                               \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,             \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,             \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,             \
    ...)                                                          \
            L00,        L01,        L02,        L03,        L04,  \
            R05,        R06,        R07,        R08,        R09,  \
            L10,        L11,        L12,        L13,        L14,  \
            R15,        R16,        R17,        R18,        R19,  \
            L20,        L21,        L22,        L23,        L24,  \
            R25,        MEDIA_KEY(R26), R27,        R28,        R29, \
      __VA_ARGS__
#define MEDIA_MOD(...) _MEDIA_MOD(__VA_ARGS__)

#define CHARYBDIS_LAYOUT_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)


#define _LAYOUT_3x5_to_4x5_adapter(\
  k11, k12, k13, k14, k15,     k65, k64, k63, k62, k61, \
  k21, k22, k23, k24, k25,     k75, k74, k73, k72, k71, \
  k31, k32, k33, k34, k35,     k85, k84, k83, k82, k81, \
            k43, k44, k41,     k91, k93) \
LAYOUT_charybdis_4x6( \
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
  KC_NO, k11,   k12,   k13,   k14,   k15,       k65,   k64,   k63,   k62,   k61,   KC_NO, \
  KC_NO, k21,   k22,   k23,   k24,   k25,       k75,   k74,   k73,   k72,   k71,   KC_NO, \
  KC_NO, k31,   k32,   k33,   k34,   k35,       k85,   k84,   k83,   k82,   k81,   KC_NO, \
                       k43,   k44,   k41,       k91,   k93,                     \
                              KC_NO, KC_NO,     KC_NO                           \
)

#define LAYOUT_3x5_to_4x5_adapter(...) _LAYOUT_3x5_to_4x5_adapter(__VA_ARGS__)



