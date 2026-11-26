#include "SjenaDeskEngine/Input/Input.h"
#include "SjenaDeskEngine/Input/KeyLayout.h"


#if defined(_WIN32)

// KEYMAP | WINDOWS (SCANCODE)
KeyCode api_key_map(int code) {
    switch (code) {
    case 0x0B: return SJENA_KEY_0;
    case 0x02: return SJENA_KEY_1;
    case 0x03: return SJENA_KEY_2;
    case 0x04: return SJENA_KEY_3;
    case 0x05: return SJENA_KEY_4;
    case 0x06: return SJENA_KEY_5;
    case 0x07: return SJENA_KEY_6;
    case 0x08: return SJENA_KEY_7;
    case 0x09: return SJENA_KEY_8;
    case 0x0A: return SJENA_KEY_9;

    case 0x1E: return SJENA_KEY_A;
    case 0x30: return SJENA_KEY_B;
    case 0x2E: return SJENA_KEY_C;
    case 0x20: return SJENA_KEY_D;
    case 0x12: return SJENA_KEY_E;
    case 0x21: return SJENA_KEY_F;
    case 0x22: return SJENA_KEY_G;
    case 0x23: return SJENA_KEY_H;
    case 0x17: return SJENA_KEY_I;
    case 0x24: return SJENA_KEY_J;
    case 0x25: return SJENA_KEY_K;
    case 0x26: return SJENA_KEY_L;
    case 0x32: return SJENA_KEY_M;
    case 0x31: return SJENA_KEY_N;
    case 0x18: return SJENA_KEY_O;
    case 0x19: return SJENA_KEY_P;
    case 0x10: return SJENA_KEY_Q;
    case 0x13: return SJENA_KEY_R;
    case 0x1F: return SJENA_KEY_S;
    case 0x14: return SJENA_KEY_T;
    case 0x16: return SJENA_KEY_U;
    case 0x2F: return SJENA_KEY_V;
    case 0x11: return SJENA_KEY_W;
    case 0x2D: return SJENA_KEY_X;
    case 0x15: return SJENA_KEY_Y;
    case 0x2C: return SJENA_KEY_Z;

    case 0x1C: return SJENA_KEY_ENTER;
    case 0x39: return SJENA_KEY_SPACE;
    case 0x0E: return SJENA_KEY_BACKSPACE;
    case 0x1D: return SJENA_KEY_CTRL;
    case 0x38: return SJENA_KEY_LEFT_ALT;
    case 0x01: return SJENA_KEY_ESC;
    case 0x0F: return SJENA_KEY_TAB;

    case 0x138: return SJENA_KEY_RIGHT_ALT;
    case 0x15B: return SJENA_KEY_META;
    case 0x150: return SJENA_KEY_ARROW_DOWN;
    case 0x14B: return SJENA_KEY_ARROW_LEFT;
    case 0x14D: return SJENA_KEY_ARROW_RIGHT;
    case 0x148: return SJENA_KEY_ARROW_UP;

    case 0x3B: return SJENA_KEY_F1;
    case 0x3C: return SJENA_KEY_F2;
    case 0x3D: return SJENA_KEY_F3;
    case 0x3E: return SJENA_KEY_F4;
    case 0x3F: return SJENA_KEY_F5;
    case 0x40: return SJENA_KEY_F6;
    case 0x41: return SJENA_KEY_F7;
    case 0x42: return SJENA_KEY_F8;
    case 0x43: return SJENA_KEY_F9;

    default:return (KeyCode)0ULL;
    }
}

// Registers Devices to a Window and returns the header that got applied
unsigned char Input::setup(Window* window, unsigned char settings){
    if(!window || !window->hwnd) return 0;
    unsigned char header = 0;

    // Setup
    // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/hid-architecture#hid-clients-supported-in-windows
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawinputdevice
    // Sets RIDEV_NOLEGACY to avoid unnecesarry calls with or without background collection(INPUTSINK)
    RAWINPUTDEVICE rid_mouse[1] = {0};
    if(settings & DeviceHeader::MOUSE){
        // 0x01 / 0x02 MOUSE
        rid_mouse[0].usUsagePage = 0x01;
        rid_mouse[0].usUsage = 0x02;
        rid_mouse[0].dwFlags = ((settings & MOUSE_BG) ? RIDEV_INPUTSINK : 0);
        rid_mouse[0].hwndTarget = window->hwnd;
        
        if(RegisterRawInputDevices(rid_mouse, 1, sizeof(RAWINPUTDEVICE))){
            header |= DeviceHeader::MOUSE;
            if(settings & MOUSE_BG)header |= MOUSE_BG;
            else header &= ~MOUSE_BG;
        }
    }
    if(settings & DeviceHeader::KEYBOARD){
        // 0x01 / 0x06 KEYBOARD
        RAWINPUTDEVICE rid_kb[1] = {0};
        rid_kb[0].usUsagePage = 0x01;
        rid_kb[0].usUsage = 0x06;
        rid_kb[0].dwFlags = ((settings & KEYBOARD_BG) ? RIDEV_INPUTSINK : 0);
        rid_kb[0].hwndTarget = window->hwnd;
        header |= DeviceHeader::KEYBOARD;
        if(RegisterRawInputDevices(rid_kb, 1, sizeof(RAWINPUTDEVICE))){
            header |= DeviceHeader::KEYBOARD;
            if(settings & KEYBOARD_BG)header |= KEYBOARD_BG;
            else header &= ~KEYBOARD_BG;
        }
    }

    this->full_reset();
    this->header = header;
    return header;
}

//Unregisters RawInputDevice and returns Devices that got Unregistered
unsigned char Input::destroy(){
    unsigned char header = 0;

    // Setup
    // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/hid-architecture#hid-clients-supported-in-windows
    RAWINPUTDEVICE rid_mouse[1] = {0};
    if(this->header & DeviceHeader::MOUSE){
        // 0x01 / 0x02 MOUSE
        rid_mouse[0].usUsagePage = 0x01;
        rid_mouse[0].usUsage = 0x02;
        rid_mouse[0].dwFlags = RIDEV_REMOVE;
        rid_mouse[0].hwndTarget = nullptr;
        
        if(RegisterRawInputDevices(rid_mouse, 1, sizeof(RAWINPUTDEVICE))){
            header |= DeviceHeader::MOUSE;
        }
    }
    if(this->header & DeviceHeader::KEYBOARD){
        // 0x01 / 0x06 KEYBOARD
        RAWINPUTDEVICE rid_kb[1] = {0};
        rid_kb[0].usUsagePage = 0x01;
        rid_kb[0].usUsage = 0x06;
        rid_kb[0].dwFlags = RIDEV_REMOVE;
        rid_kb[0].hwndTarget = nullptr;
        header |= DeviceHeader::KEYBOARD;
        if(RegisterRawInputDevices(rid_kb, 1, sizeof(RAWINPUTDEVICE))){
            header |= DeviceHeader::KEYBOARD;
        }
    }

    this->full_reset();
    this->header = 0;
    return header;
}

unsigned char Input::callback(WINDOW_MSG_CODE msg, unsigned long long code, unsigned long long data){
    // TODO: Optimize and try to check if windows lost focus without global input & if global input blocked because app with admin is in Foreground
    if((msg & MSG_WINDOW_KILLFOCUS)){
        if(!(this->header & MOUSE_BG)) this->mouse.reset(0);
        if(!(this->header & KEYBOARD_BG)){
            // Keyboard
            this->keyboard.pressed_states = 0ULL;
            this->keyboard.is_pressed_keys = 0ULL;
        }
        this->header &= (MOUSE | MOUSE_BG | KEYBOARD | KEYBOARD_BG);
        return 0;
    }

    if(msg & MSG_INPUT){
        // Get RAWINPUT Struct
        RAWINPUT ri;
        UINT ri_size = sizeof(ri);
        if(GetRawInputData((HRAWINPUT)data, RID_INPUT, &ri, &ri_size, sizeof(RAWINPUTHEADER)) == (UINT)-1)return 3;
        switch (ri.header.dwType)
        {
            case RIM_TYPEMOUSE: {
                if(!GET_RAWINPUT_CODE_WPARAM(code))this->header |= MOUSE_IN_FG;
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
                if(!GET_RAWINPUT_CODE_WPARAM(code))this->header |= KEYBOARD_IN_FG;
                if(ri.data.keyboard.Flags & RI_KEY_E1)break;
                unsigned char down = !(ri.data.keyboard.Flags & RI_KEY_BREAK);
                unsigned char e0   = ri.data.keyboard.Flags & RI_KEY_E0;
                if(e0 && (ri.data.keyboard.MakeCode == 0x2A || ri.data.keyboard.MakeCode == 0x36))break;
                this->keyboard.callback(api_key_map(ri.data.keyboard.MakeCode | (e0 ? 0x100 : 0)), down);
                break;
            }
        
            default: break;
        }
        return 0;
    }
    return 0;
}

unsigned char Input::handler(){
    return this->reset();
}

#endif
