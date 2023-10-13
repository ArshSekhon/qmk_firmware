# VIA_ENABLE = yes
# VIAL_ENABLE = yes
# VIAL_INSECURE = yes

MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
DYNAMIC_MACRO_ENABLE = yes
TAP_DANCE_ENABLE = yes
OS_DETECTION_ENABLE = yes

SRC += oneshot/oneshot.c
SRC += os_specific/os_specific.c
SRC += rgb/rgb.c
SRC += layers/layers.c
