#include "layers.h"

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case BASE:
        break;
    case NAV:
        break;
    case NUM:
        break;
    case SYM:
        break;
    case MOUSE:
        break;
    case MEDIA:
        break;
    case FUN:
        break;
    default:
        break;
    }
  return state;
}
