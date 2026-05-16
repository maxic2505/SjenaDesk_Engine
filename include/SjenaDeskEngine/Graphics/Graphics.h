#pragma once

#include <stdlib.h>
#include <string.h>
#include "SjenaDeskEngine/Math/Vector.h"

#define WINDOW_MAX_CLASS_SIZE 24
#define OBJECT_TYPE_BUTTON 6
#define OBJECT_TYPE_TEXT 2

#ifdef _WIN32
#include <Windows.h>
#endif

typedef struct Color { unsigned char r, g, b, a; } Color;

typedef enum Extra{
	IS_REGISTERED =  1<<0,
	IS_ACTIVE =      1<<1,
	IS_VISIBLE =     1<<2,
	IS_CLICKABLE =   1<<3,
	USE_IMG =        1<<4,
	USE_TEXT =       1<<5,
	USE_BORDER =   	 1<<6,
	USE_BG_COLOR =   1<<7,
	COLOR_OVER =	 1<<8,
	COLOR_ON_CLICK = 1<<9,
}Extra;

typedef struct Object {
	void* properties;
	void* data;
	unsigned long long data_size;
	unsigned long long extra;
	uVec2 position, size;
	unsigned int type, id;
}Object;

typedef struct Text {
	Color text_color;
	Color bg_color;
}Text;

typedef struct Button {
	Color color_text;
	Color color_over;
	Color color_on_click;
	Color color_active;
	Color color_deactive;
	Color color_border;
}Button;

typedef struct Window {
	#if defined(_WIN32)
	HWND hwnd;
	#elif defined(__linux__)
	void* hwnd;
	#endif

	char* class;

	Object* objects;
	unsigned long long size;
}Window;

#ifdef __cplusplus
extern "C"{
#endif
// Test required | Undone
typedef unsigned char (*Graphics_Input_Callback)(int value);

unsigned char graphic_register_window	(Window* window, const char* class);
unsigned char graphic_create_window		(Window* window, const char* name, long window_style, const long x, const long y, const long width, const long height);
unsigned char graphic_show_window		(Window* window, const unsigned char show);
unsigned char graphic_set_pos_window(Window* window, uVec2 pos);
unsigned char graphic_destroy_window	(Window* window);

unsigned char graphic_create_text		(Object* object, uVec2 position, uVec2 size, const char* text, Text* properties, Extra extra, unsigned int id);
unsigned char graphic_create_button		(Object* object, uVec2 position, uVec2 size, void* data, size_t data_size, Button* properties, Extra extra, unsigned int id);
unsigned char graphic_create_object		(Object* object, Color* color);
unsigned char graphic_destroy_object	(Object* object);

unsigned char graphic_get_object_type   (Object* object);
unsigned char graphic_register_object	(Object* object, Object* dst, unsigned char size);
unsigned char graphic_remove_object		(Object* object, Object* src, unsigned char size);

#ifdef __cplusplus
}
#endif
