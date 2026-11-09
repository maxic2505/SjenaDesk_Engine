#include "SjenaDeskEngine/Input/Input.h"
#include "SjenaDeskEngine/Input/KeyLayout.h"


#if defined(_WIN32)

// KEYMAP | WINDOWS (SCANCODE)
KeyCode api_key_map(int code) {
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
    case 0x1D: return KEYCODE_LEFT_CTRL;
    case 0x38: return KEYCODE_LEFT_ALT;
    case 0x01: return KEYCODE_ESC;
    case 0x0F: return KEYCODE_TAB;

    case 0x11D: return KEYCODE_RIGHT_CTRL;
    case 0x138: return KEYCODE_RIGHT_ALT;
    case 0x15B: return KEYCODE_LEFT_META;
    case 0x15C: return KEYCODE_RIGHT_META;
    case 0x150: return ARROW_DOWN;
    case 0x14B: return ARROW_LEFT;
    case 0x14D: return ARROW_RIGHT;
    case 0x148: return ARROW_UP;

    case 0x3B: return KEYCODE_F1;
    case 0x3C: return KEYCODE_F2;
    case 0x3D: return KEYCODE_F3;
    case 0x3E: return KEYCODE_F4;
    case 0x3F: return KEYCODE_F5;
    case 0x40: return KEYCODE_F6;
    case 0x41: return KEYCODE_F7;
    case 0x42: return KEYCODE_F8;
    case 0x43: return KEYCODE_F9;

    default:return (KeyCode)0ULL;
    }
}

unsigned char Input::callback(unsigned long long code, unsigned long long data){
    // Get RAWINPUT Struct
    RAWINPUT ri;
    UINT ri_size = sizeof(ri);
    if(GetRawInputData((HRAWINPUT)data, RID_INPUT, &ri, &ri_size, sizeof(RAWINPUTHEADER)) == (UINT)-1){
        //Fehler behandlung
        return 1;
    }
    switch (ri.header.dwType)
    {
        case RIM_TYPEMOUSE: {
            // Mouse Buttons
            const USHORT usButtonFlags = ri.data.mouse.usButtonFlags;
            if(usButtonFlags & RI_MOUSE_BUTTON_1_DOWN) this->mouse.events |= LEFT_BTN_STATE | LEFT_BTN_PRESSED;
            if(usButtonFlags & RI_MOUSE_BUTTON_1_UP) this->mouse.events = this->mouse.events & ~LEFT_BTN_STATE;

            if(usButtonFlags & RI_MOUSE_BUTTON_2_DOWN) this->mouse.events |= RIGHT_BTN_STATE | RIGHT_BTN_PRESSED;
            if(usButtonFlags & RI_MOUSE_BUTTON_2_UP) this->mouse.events = this->mouse.events & ~RIGHT_BTN_STATE;

            if(usButtonFlags & RI_MOUSE_BUTTON_3_DOWN) this->mouse.events |= MIDDLE_BTN_STATE | MIDDLE_BTN_PRESSED;
            if(usButtonFlags & RI_MOUSE_BUTTON_3_UP) this->mouse.events = this->mouse.events & ~MIDDLE_BTN_STATE;

            // Mouse Position & Acceleration
            if(!(ri.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE)){
                if(ri.data.mouse.lLastX || ri.data.mouse.lLastY)this->mouse.events |= SENSOR_EVENT;
                // Reset at Input.reset() necesary
                this->mouse.acceleration.x += ri.data.mouse.lLastX;
                this->mouse.acceleration.y += ri.data.mouse.lLastY;
                POINT point;
                if(GetCursorPos(&point))
                { this->mouse.position = iVec2{point.x, point.y}; }
            }
            
            // usButtonData
            if(ri.data.mouse.usButtonFlags & RI_MOUSE_HWHEEL){
                this->mouse.scroll_x += (short)ri.data.mouse.usButtonData;
                this->mouse.events |= SCROLL_EVENT;
            }
            if(ri.data.mouse.usButtonFlags & RI_MOUSE_WHEEL){
                this->mouse.scroll_y += (short)ri.data.mouse.usButtonData;
                this->mouse.events |= SCROLL_EVENT;
            }
            break;
        }
            
        case RIM_TYPEKEYBOARD: {
            if(ri.data.keyboard.Flags & RI_KEY_E1)break;
            unsigned char down = !(ri.data.keyboard.Flags & RI_KEY_BREAK);
            unsigned char e0   = ri.data.keyboard.Flags & RI_KEY_E0;
            if(e0 && (ri.data.keyboard.MakeCode == 0x2A || ri.data.keyboard.MakeCode == 0x36))break;
            this->keyboard.callback(api_key_map(ri.data.keyboard.MakeCode | e0 ? 0x100 : 0), down);
            break;
        }
            
        default: break;
    }
    return 0;
}

unsigned char Input::handler(){
    this->reset();
    // Keep Windows Thread alive
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HHOOK hook;
HHOOK mouse_hook;
MSG msg;
unsigned char w_event[60];
Keyboard event;

// TODO: UPDATE TO RAWINPUT
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* k = (KBDLLHOOKSTRUCT*)lParam;
        unsigned char down = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) ? 1 : 0;
        unsigned char up = (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) ? 1 : 0;
        unsigned long long key = api_key_map(k->scanCode);
        if ((key != 0) && (down || up)) {
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

// TODO: UPDATE TO RAWINPUT & FIX MOUSE CLICK
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam){
    if(nCode == HC_ACTION){
        unsigned long long key_num = wParam-0x0200;

        // MY EVENTS
        // NONE = 0
        //   UP = 1
        // DOWN = 2

        // CALCULATED EVENTS
        //  0 = DOWN
        //  1 = DOWN
        //  2 = UP

        if(key_num<10 && key_num>0){
            unsigned char key_state = ((unsigned char)key_num % 3);
            //unsigned char key   = ((unsigned char)key_num / 3) + MOUSE_LEFT; 
            //if(key_state == 0)key--;

            //input_key_callback(key, (key_state == 2) ? 0 : 1);
        }
    }
    return CallNextHookEx(mouse_hook, nCode, wParam, lParam);
}

// Input-API | 0 = Success
unsigned char input_key_setup_api() {
    if(!hook)      hook        = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if(!mouse_hook)mouse_hook  = SetWindowsHookExW(WH_MOUSE_LL,    LowLevelMouseProc, NULL, 0);

    return (!hook || !mouse_hook) ? 1 : 0;
}

unsigned char input_key_handler_api() {
    input_reset();

    

    return 0;
}

#endif
