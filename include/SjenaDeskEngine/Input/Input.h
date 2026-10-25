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
    unsigned long long released_states;
    unsigned long long consumed_states;
    #ifdef __cplusplus
    unsigned char get_key           (const KeyCode code);
    unsigned char get_key_consumed  (const KeyCode code);
    unsigned char get_key_down      (const KeyCode code);
    unsigned char get_key_up        (const KeyCode code);

    unsigned char set_key           (const KeyCode code, const unsigned char state);
    unsigned char set_key_consumed  (const KeyCode code, const unsigned char state);
    unsigned char set_key_state_down(const KeyCode code);
    unsigned char set_key_state_up  (const KeyCode code);
    unsigned char remove_state      (const KeyCode code);

    #endif
}Keyboard;

unsigned char keyboard_get_key          (Keyboard* keyboard, const KeyCode code);
unsigned char keyboard_get_key_consumed (Keyboard* keyboard, const KeyCode code);
unsigned char keyboard_get_key_down     (Keyboard* keyboard, const KeyCode code);
unsigned char keyboard_get_key_up       (Keyboard* keyboard, const KeyCode code);

unsigned char keyboard_set_key              (Keyboard* keyboard, const KeyCode code, const unsigned char state);
unsigned char keyboard_set_key_consumed     (Keyboard* keyboard, const KeyCode code, const unsigned char state);
unsigned char keyboard_set_key_state_down   (Keyboard* keyboard, const KeyCode code);
unsigned char keyboard_set_key_state_up     (Keyboard* keyboard, const KeyCode code);
unsigned char keyboard_remove_state         (Keyboard* keyboard, const KeyCode code);

typedef struct Mouse{
    uVec2 position;
    uVec2 last_position;
    Vec2 acceleration;
    float wheel_acceleration;
    MouseEvent events;
}Mouse;

typedef enum DeviceHeader{
    STATUS        = 1<<0,
    TYPE_MOUSE    = 1<<1,
    TYPE_KEYBOARD = 1<<2,
    TYPE_JOYSTICK = 1<<3,
    TYPE_UNKNOWN  = 1<<4,
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

typedef struct Device{
    #ifdef _WIN32
    HWND hwnd;
    #endif
    void* data;
    DeviceHeader header;

    #ifdef __cplusplus
    unsigned char is_ready();
    unsigned char is_type(DeviceHeader type);
    unsigned char setup_mouse();
    unsigned char setup_keyboard();
    unsigned char destroy();
    #endif
}Device;


typedef struct Input{
    Device* devices;
    unsigned int size;
    unsigned int header;

    #ifdef _WIN32
    HookManager mgr;
    #endif

    #ifdef __cplusplus
    unsigned char get_key(const int keycode);
    unsigned char get_key_down(const int keycode);
    unsigned char get_key_up(const int keycode);
    #endif
}Input;

unsigned char getKey(const int keycode);
unsigned char getKeyDown(const int keycode);
unsigned char getKeyUp(const int keycode);

uVec2 input_mouse_get_position();

unsigned char input_key_setup_api();
unsigned char input_key_handler_api();

// DO NOT USE THIS METHODE FOR YOURSELF
int input_key_callback(int code, int value);
void input_reset();

#ifdef __cplusplus
}
#endif