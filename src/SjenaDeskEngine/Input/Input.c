#include "SjenaDeskEngine/Input/Input.h"

Input input = {0};

unsigned char getKey(const int keycode){ // Check if a Key is being Held
    return input.key[keycode].isPressed;
}
unsigned char getKeyDown(const int keycode){ // Check if a Key was Pressed
    return input.key[keycode].state == DOWN;
}
unsigned char getKeyUp(const int keycode){ // Check if a Key was Released
    return input.key[keycode].state == UP;
}


unsigned char is_modifier(int code){ // private for inputKeyHanler
    return ((38 < code) && (code < 45));
}

// Input | CALLBACK | Set Keys
int input_key_callback(int code, int value){
    if(code < 0)return 0; // -1 => KEY OUT OF RANGE

    if(!(input.key[code].isConsumed))return 0; // Value 0 => KEY NOT CONSUMED
    input.key[code].isConsumed = 0;

    input.key[code].isPressed = (value > 0);

    if(is_modifier(code)){
        switch(value){
            case 0:  input.key[code].state = UP;   return 1;
            case 1:  input.key[code].state = DOWN; return 1;
            case 2:  input.key[code].state = DOWN; return 1;
            default: input.key[code].state = UP;   return -1;
        }
        return 0;
    }

    switch(value){
        case 0:  input.key[code].state = (getKeyUp  (code)) ? 0 : 1; return 2;
        case 1:  input.key[code].state = (getKeyDown(code)) ? 0 : 2; return 2;
        case 2:  input.key[code].state = 0; return 2;
        default: input.key[code].state = 0; return -2;
    }
}

// Put it at the end of the fixed update for a key reset to avoid undetected States per frame.
int input_key_handler(){
    for(int i = 0; i<KEYS_AVAILABLE;i++){
        input.key[i].isConsumed = 1;

        // ONE SHOT KEYS RESET
        if(!(input.key[i].state > 0) || is_modifier(i)) continue;
        input.key[i].state = 0;
    }
    return 1;
}


// LINUX INPUT SYSTEM

#ifdef __linux__
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
    while (read(event_file, &event, sizeof(event)) > 0) {
        if (event.type != EV_KEY) continue;
        input_key_callback(api_key_map(event.code), event.value);
    }
    return 0;
}
#endif


// WINDOWS INPUT SYSTEM

#ifdef _WIN32
// KEYMAP | WINDOWS (SCANCODE)
int api_key_map(int code) {
    switch (code) {
    case 0x0B: return KEYCODE_0;
    case 0x02: return KEYCODE_1;
    case 0x03: return KEYCODE_2;
    case 0x04: return KEYCODE_3;
    case 0x05: return KEYCODE_4;
    case 0x06: return KEYCODE_5;
    case 0x07: return KEYCODE_6;
    case 0x08: return KEYCODE_7;
    case 0x09: return KEYCODE_8;
    case 0x0A: return KEYCODE_9;

    case 0x1E: return KEYCODE_A;
    case 0x30: return KEYCODE_B;
    case 0x2E: return KEYCODE_C;
    case 0x20: return KEYCODE_D;
    case 0x12: return KEYCODE_E;
    case 0x21: return KEYCODE_F;
    case 0x22: return KEYCODE_G;
    case 0x23: return KEYCODE_H;
    case 0x17: return KEYCODE_I;
    case 0x24: return KEYCODE_J;
    case 0x25: return KEYCODE_K;
    case 0x26: return KEYCODE_L;
    case 0x32: return KEYCODE_M;
    case 0x31: return KEYCODE_N;
    case 0x18: return KEYCODE_O;
    case 0x19: return KEYCODE_P;
    case 0x10: return KEYCODE_Q;
    case 0x13: return KEYCODE_R;
    case 0x1F: return KEYCODE_S;
    case 0x14: return KEYCODE_T;
    case 0x16: return KEYCODE_U;
    case 0x2F: return KEYCODE_V;
    case 0x11: return KEYCODE_W;
    case 0x2D: return KEYCODE_X;
    case 0x15: return KEYCODE_Y;
    case 0x2C: return KEYCODE_Z;

    case 0x1C: return KEYCODE_ENTER;
    case 0x39: return KEYCODE_SPACE;
    case 0x0E: return KEYCODE_BACKSPACE;
    case 0x5B: return KEYCODE_LEFT_META;
    case 0x5C: return KEYCODE_RIGHT_META;
    case 0x1D: return KEYCODE_LEFT_CTRL;
    case 0x38: return KEYCODE_LEFT_ALT;
    case 0x01: return KEYCODE_ESC;
    case 0x0F: return KEYCODE_TAB;

    case 0x50: return ARROW_DOWN;
    case 0x4B: return ARROW_LEFT;
    case 0x4D: return ARROW_RIGHT;
    case 0x48: return ARROW_UP;

    case 0x3B: return KEYCODE_F1;
    case 0x3C: return KEYCODE_F2;
    case 0x3D: return KEYCODE_F3;
    case 0x3E: return KEYCODE_F4;
    case 0x3F: return KEYCODE_F5;
    case 0x40: return KEYCODE_F6;
    case 0x41: return KEYCODE_F7;
    case 0x42: return KEYCODE_F8;
    case 0x43: return KEYCODE_F9;

    default:return -1;
    }
}

HHOOK hook;
MSG msg;
unsigned char w_event[60];

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* k = (KBDLLHOOKSTRUCT*)lParam;
        unsigned char down = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) ? 1 : 0;
        unsigned char up = (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) ? 1 : 0;
        int key = api_key_map(k->scanCode);
        if (!(key < 0) && (down || up)) {
            if (down) {
                if (w_event[key] == 0)w_event[key] = 1;
                else w_event[key] = 2;
            }
            else {
                w_event[key] = 0;
            }
            input_key_callback(key, w_event[key]);
        }
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}

// Input-API | 0 = Success
unsigned char input_key_setup_api() {
    if (hook != NULL) return 1;
    hook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    return (hook == NULL) ? 1 : 0;
}

unsigned char input_key_handler_api() {
    // Keep Windows Thread alive
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

uVec2 input_mouse_get_position() {
    uVec2 point;
    if (GetCursorPos(&point) != 0) return (uVec2) { point.x, point.y};
    else return (uVec2) {0, 0};
}
#endif