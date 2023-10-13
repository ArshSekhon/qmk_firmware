
#pragma once

#include QMK_KEYBOARD_H

typedef enum OSTYPE {
  WINDOWS,
  MACOSX,
  LINUX
} ostype_t;

ostype_t is_mac_os(void);

#define WITH_SUPER_MOD(STRING) (is_mac_os() ? SEND_STRING(SS_LGUI(STRING)) : SEND_STRING(SS_LCTRL(STRING)))
void os_specific_copy(void);
void os_specific_cut(void);
void os_specific_paste(void);
void os_specific_undo(void);
void os_specific_redo(void);
void os_specific_lock(void);
void os_specific_screenshot(void);
void os_specific_screenshot_to_clipboard(void);
void os_specific_record(void);
void os_specific_indicate_os(void);
