#pragma once

#include "SjenaDesk_Key.h"
#include "../Math/SjenaDesk_Vector.h"

#ifdef __linux__
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#endif

#ifdef _WIN32
#include <Windows.h>

#define USING_WINDOWS_INPUT 1
#endif

#define KEYS_AVAILABLE 60

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Input{
    Key key[KEYS_AVAILABLE];
}Input;

extern Input input;

unsigned char getKey(const int keycode);
unsigned char getKeyDown(const int keycode);
unsigned char getKeyUp(const int keycode);

uVec2 input_mouse_get_position();

unsigned char input_key_setup_api();
unsigned char input_key_handler_api();

int input_key_handler();

#ifdef __cplusplus
}
#endif