#include "rgb.h"


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    int highest_layer = get_highest_layer(layer_state|default_layer_state);
    if(host_keyboard_led_state().caps_lock){
        // if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
            rgb_matrix_set_color_all( RGB_WHITE);
        // }
    }
    else
    {
        switch(highest_layer) {
            case 2:
                rgb_matrix_set_color_all(RGB_BLUE);
                break;
            case 1:
                rgb_matrix_set_color_all(RGB_RED);
                break;
            default:
                break;
        }
    }
    return true;

}

