#pragma once

#include "SjenaDeskEngine/Input/KeyLayout.h"
#include "SjenaDeskEngine/Math/Vector.h"





#ifdef __linux__
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define KEYS_AVAILABLE 60
#endif

#ifdef _WIN32
#include <Windows.h>

#define KEYS_AVAILABLE 63
#endif





#ifdef __cplusplus
extern "C"{
#endif

typedef struct Input{
    Key key[KEYS_AVAILABLE];
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