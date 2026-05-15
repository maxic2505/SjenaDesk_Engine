#include "SjenaDeskEngine/Input/Input.h"



#if defined(__linux__)

// KEYMAP | LINUX
int api_key_map(int code) {
    switch (code) {
    case KEY_0: return KEYCODE_0;
    case KEY_1: return KEYCODE_1;
    case KEY_2: return KEYCODE_2;
    case KEY_3: return KEYCODE_3;
    case KEY_4: return KEYCODE_4;
    case KEY_5: return KEYCODE_5;
    case KEY_6: return KEYCODE_6;
    case KEY_7: return KEYCODE_7;
    case KEY_8: return KEYCODE_8;
    case KEY_9: return KEYCODE_9;

    case KEY_A: return KEYCODE_A;
    case KEY_B: return KEYCODE_B;
    case KEY_C: return KEYCODE_C;
    case KEY_D: return KEYCODE_D;
    case KEY_E: return KEYCODE_E;
    case KEY_F: return KEYCODE_F;
    case KEY_G: return KEYCODE_G;
    case KEY_H: return KEYCODE_H;
    case KEY_I: return KEYCODE_I;
    case KEY_J: return KEYCODE_J;
    case KEY_K: return KEYCODE_K;
    case KEY_L: return KEYCODE_L;
    case KEY_M: return KEYCODE_M;
    case KEY_N: return KEYCODE_N;
    case KEY_O: return KEYCODE_O;
    case KEY_P: return KEYCODE_P;
    case KEY_Q: return KEYCODE_Q;
    case KEY_R: return KEYCODE_R;
    case KEY_S: return KEYCODE_S;
    case KEY_T: return KEYCODE_T;
    case KEY_U: return KEYCODE_U;
    case KEY_V: return KEYCODE_V;
    case KEY_W: return KEYCODE_W;
    case KEY_X: return KEYCODE_X;
    case KEY_Y: return KEYCODE_Y;
    case KEY_Z: return KEYCODE_Z;

    case KEY_ENTER:     return KEYCODE_ENTER;
    case KEY_SPACE:     return KEYCODE_SPACE;
    case KEY_BACKSPACE: return KEYCODE_BACKSPACE;
    case KEY_LEFTMETA:  return KEYCODE_LEFT_META;
    case KEY_RIGHTMETA: return KEYCODE_RIGHT_META;
    case KEY_LEFTCTRL:  return KEYCODE_LEFT_CTRL;
    case KEY_RIGHTCTRL: return KEYCODE_RIGHT_CTRL;
    case KEY_LEFTALT:   return KEYCODE_LEFT_ALT;
    case KEY_RIGHTALT:  return KEYCODE_RIGHT_ALT;
    case KEY_ESC:       return KEYCODE_ESC;
    case KEY_TAB:       return KEYCODE_TAB;

    case KEY_DOWN:      return ARROW_DOWN;
    case KEY_LEFT:      return ARROW_LEFT;
    case KEY_RIGHT:     return ARROW_RIGHT;
    case KEY_UP:        return ARROW_UP;

    case KEY_F1: return KEYCODE_F1;
    case KEY_F2: return KEYCODE_F2;
    case KEY_F3: return KEYCODE_F3;
    case KEY_F4: return KEYCODE_F4;
    case KEY_F5: return KEYCODE_F5;
    case KEY_F6: return KEYCODE_F6;
    case KEY_F7: return KEYCODE_F7;
    case KEY_F8: return KEYCODE_F8;
    case KEY_F9: return KEYCODE_F9;

    default:return -1;
    }
}

/* Actual code for Header */

struct input_event event;
int event_file;

// Input-API | Setup file | 0 = Success
unsigned char input_key_setup_api() {
    event_file = open("/dev/input/event4", O_RDONLY | O_NONBLOCK);
    return (event_file <= 0) ? 1 : 0;
}

// Input-API | Handler to scan for keys | Use it at the beginning of the while loop
unsigned char input_key_handler_api() {
    input_reset();
    
    while (read(event_file, &event, sizeof(event)) > 0) {
        if (event.type != EV_KEY) continue;
        input_key_callback(api_key_map(event.code), event.value);
    }
    return 0;
}

#endif