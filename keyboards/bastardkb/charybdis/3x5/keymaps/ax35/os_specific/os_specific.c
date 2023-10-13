#include "os_specific.h"

extern keymap_config_t keymap_config;

ostype_t is_mac_os() {
  return keymap_config.swap_lctl_lgui;
}

void os_specific_copy() {
    // WITH_SUPER_MOD("c");
}

void os_specific_paste() {
    // WITH_SUPER_MOD("v");
}

void os_specific_lock() {
//   if (is_mac_os()) {
//     SEND_STRING(SS_LCTRL(SS_LCMD("q")));
//   } else {
//     SEND_STRING(SS_LGUI("l"));
//   }
}

void os_specific_cut() {
    // WITH_SUPER_MOD("x");
}

void os_specific_undo() {
    // WITH_SUPER_MOD("z");
};
void os_specific_redo() {
    // WITH_SUPER_MOD(SS_LSFT("z"));
};

void os_specific_screenshot(){
//   if (is_mac_os()) {
//     SEND_STRING(SS_LCMD(SS_LSFT("4")));
//   } else {
//     SEND_STRING(SS_LGUI(SS_LSFT("s")));
//   }
}

void os_specific_screenshot_to_clipboard() {
//   if (is_mac_os()) {
//     SEND_STRING(SS_LCTRL(SS_LCMD(SS_LSFT("4"))));
//   } else {
//     SEND_STRING(SS_LGUI(SS_LSFT("s")));
//   }
}

void os_specific_record() {
//   if (is_mac_os()) {
//     SEND_STRING(SS_LCMD(SS_LSFT("5")));
//   } else {
//     SEND_STRING(SS_LGUI(SS_LALT("r")));
//   }
}

void os_specific_indicate_os(){
//   if (is_mac_os()){
//     SEND_STRING("MacOS");
//   } else {
//     SEND_STRING("Linux/Windows");
//   }
}
