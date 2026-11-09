#pragma once

#include "SjenaDeskEngine/Graphics/Graphics.h"
#include "SjenaDeskEngine/Input/KeyLayout.h"
#include "SjenaDeskEngine/Math/Vector.h"

#define SJENADESK_INPUT_LIB 1

#ifdef __linux__
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

// DEVICE
typedef struct Keyboard{
    unsigned long long is_pressed_keys;
    unsigned long long pressed_states;
    #ifdef __cplusplus
    unsigned char get_key           (const KeyCode code);
    unsigned char get_key_down      (const KeyCode code);

    unsigned char set_key           (const KeyCode code, const unsigned char state);
    unsigned char set_key_state_down(const KeyCode code);
    unsigned char remove_state      (const KeyCode code);

    unsigned char callback(KeyCode code, int value);
    #endif
}Keyboard;

unsigned char keyboard_get_key          (Keyboard* keyboard, const KeyCode code);
unsigned char keyboard_get_key_down     (Keyboard* keyboard, const KeyCode code);

unsigned char keyboard_set_key              (Keyboard* keyboard, const KeyCode code, const unsigned char state);
unsigned char keyboard_set_key_state_down   (Keyboard* keyboard, const KeyCode code);
unsigned char keyboard_remove_state         (Keyboard* keyboard, const KeyCode code);

unsigned char keyboard_callback(Keyboard* keyboard, KeyCode code, int value);

typedef struct Mouse{
    iVec2 position;
    iVec2 acceleration;
    short scroll_x;
    short scroll_y;
    unsigned char events;
}Mouse;

typedef enum DeviceHeader{
    MOUSE_STATUS    = 1<<0,
    MOUSE_BG        = 1<<1,
    MOUSE_IN_FG     = 1<<2,
    KEYBOARD_STATUS = 1<<3,
    KEYBOARD_BG     = 1<<4,
    KEYBOARD_IN_FG  = 1<<5,
    U1              = 1<<6,
    U2              = 1<<7,
}DeviceHeader;

#ifdef _WIN32
typedef struct HookSlot{
    HHOOK hook;
    DeviceHeader header;
    unsigned int id;
    #ifdef __cplusplus
    unsigned char hook(DeviceHeader type);
    unsigned char unhook();
    #endif
}HookSlot;

unsigned char hookslot_hook(HookSlot* slot, DeviceHeader type);
unsigned char hookslot_unhook(HookSlot* slot);

typedef struct HookManager{
    HookSlot* slots;
    unsigned int size;
    #ifdef __cplusplus
    unsigned char setup();
    unsigned char add(HHOOK hook, DeviceHeader type);
    unsigned char remove_by_id(unsigned int id);
    unsigned char remove_by_type(DeviceHeader type);
    unsigned char destroy();
    #endif
}HookManager;

unsigned char hookmanager_setup(HookManager* mgr);
unsigned char hookmanager_add(HookManager* mgr, HHOOK hook, DeviceHeader type);
unsigned char hookmanager_remove_by_id(HookManager* mgr, unsigned int id);
unsigned char hookmanager_remove_by_type(HookManager* mgr, DeviceHeader type);
unsigned char hookmanager_destroy(HookManager* mgr);

#endif

typedef struct Input{
    Keyboard keyboard;
    Mouse mouse;

    #ifdef _WIN32
    HWND hWnd;
    #endif

    DeviceHeader header;

    #ifdef __cplusplus
    unsigned char setup(Window* window);
    unsigned char destroy();
    unsigned char callback(unsigned long long code, unsigned long long data);
    unsigned char handler();
    unsigned char reset();
    #endif
}Input;

unsigned char input_callback(void* class_ptr, unsigned long long code, unsigned long long data);
unsigned char input_handler(Input* input);
unsigned char input_reset(Input* input);

unsigned char getKey(const int keycode);
unsigned char getKeyDown(const int keycode);
unsigned char getKeyUp(const int keycode);

unsigned char input_key_setup_api();
unsigned char input_key_handler_api();

// DO NOT USE THIS METHODE FOR YOURSELF
int input_key_callback(int code, int value);
void input_reset();

#ifdef __cplusplus
}
#endif