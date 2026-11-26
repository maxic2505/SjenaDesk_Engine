#pragma once

#include "SjenaDeskEngine/Graphics/Graphics.h"
#include "SjenaDeskEngine/Input/KeyLayout.h"
#include "SjenaDeskEngine/Math/Vector.h"
#include <stdio.h>

#define SJENADESK_INPUT_LIB 1

#ifdef __linux__
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

// DEVICE
typedef struct Keyboard{
    SjenaKeyMask pressed_keys;
    SjenaKeyMask held_keys;
    #ifdef __cplusplus
    unsigned char get_key(const SjenaKeyCode code);
    unsigned char get_key_down(const SjenaKeyCode code);

    unsigned char set_key(const SjenaKeyCode code, const unsigned char state);
    unsigned char set_key_down(const SjenaKeyCode code);

    unsigned char callback(SjenaKeyCode code, int value);
    #endif
}Keyboard;

unsigned char keyboard_get_key(Keyboard* keyboard, const SjenaKeyCode code);
unsigned char keyboard_get_key_down(Keyboard* keyboard, const SjenaKeyCode code);

unsigned char keyboard_set_key(Keyboard* keyboard, const SjenaKeyCode code, const unsigned char state);
unsigned char keyboard_set_key_down(Keyboard* keyboard, const SjenaKeyCode code);

unsigned char keyboard_callback(Keyboard* keyboard, SjenaKeyCode code, int value);
// TODO: Mouse.events struct own name with Mask at end
typedef struct Mouse{
    iVec2 position;
    iVec2 acceleration;
    short scroll_x;
    short scroll_y;
    unsigned char events;
    #ifdef __cplusplus
    unsigned char get(MouseEvent event);
    unsigned char reset(unsigned char except_e);
    #endif
}Mouse;

unsigned char mouse_get(Mouse* mouse, MouseEvent event);
unsigned char mouse_reset(Mouse* mouse, unsigned char except_e);

typedef enum SjenaInputHeaderFlags : unsigned char{
    SJENA_INPUT_DEVICE_MOUSE            = 1<<0,
    SJENA_INPUT_DEVICE_KEYBOARD         = 1<<1,
    SJENA_INPUT_SETTING_MOUSE_BG        = 1<<2,
    SJENA_INPUT_SETTING_KEYBOARD_BG     = 1<<3,
    SJENA_INPUT_STATE_FOCUSED           = 1<<4,
    SJENA_INPUT_STATE_KEYBOARD_IN_FG    = 1<<5,
    SJENA_INPUT_EVENT_MOUSE             = 1<<6,
    SJENA_INPUT_EVENT_KEYBOARD          = 1<<7
}SjenaInputHeaderFlags;

typedef unsigned char SjenaInputHeaderMask;

#define SJENA_INPUT_DEVICE_ALL (SJENA_INPUT_DEVICE_KEYBOARD | SJENA_INPUT_DEVICE_MOUSE)
#define SJENA_INPUT_CONFIG_BG_MOUSE (SJENA_INPUT_DEVICE_MOUSE | SJENA_INPUT_SETTING_MOUSE_BG)
#define SJENA_INPUT_CONFIG_BG_KEYBOARD (SJENA_INPUT_DEVICE_KEYBOARD | SJENA_INPUT_SETTING_KEYBOARD_BG)
#define SJENA_INPUT_CONFIG_BG_ALL (SJENA_INPUT_CONFIG_BG_MOUSE | SJENA_INPUT_CONFIG_BG_KEYBOARD)

typedef struct Input{
    Mouse mouse;
    Keyboard keyboard;

    // TODO: give method to easily check events & states
    SjenaInputHeaderMask header;

    #ifdef __cplusplus
    unsigned char setup(Window* window, SjenaInputHeaderMask settings);
    unsigned char destroy();
    unsigned char callback(WINDOW_MSG_CODE msg, unsigned long long code, unsigned long long data);
    unsigned char handler();
    unsigned char reset();
    unsigned char full_reset();
    #endif
}Input;

unsigned char input_callback(void* class_ptr, WINDOW_MSG_CODE msg, unsigned long long code, unsigned long long data);
unsigned char input_handler(Input* input);
unsigned char input_reset(Input* input);
unsigned char input_full_reset(Input* input);

#ifdef __cplusplus
}
#endif