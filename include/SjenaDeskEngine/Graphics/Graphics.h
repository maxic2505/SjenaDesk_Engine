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

typedef struct Window {
	#if defined(_WIN32)
	HWND hwnd;
	#elif defined(__linux__)
	void* hwnd;
	#endif

	char class[WINDOW_MAX_CLASS_SIZE];
}Window;

typedef enum Extra{
	IS_ACTIVE =      1<<0,
	IS_VISIBLE =     1<<1,
	IS_CLICKABLE =   1<<2,
	USE_IMG =        1<<3,
	USE_TEXT =       1<<4,
	USE_BORDER =   	 1<<5,
	USE_BG_COLOR =   1<<6,
	COLOR_OVER =	 1<<7,
	COLOR_ON_CLICK = 1<<8,
}Extra;

typedef struct Object {
	void* parent_window;
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

#ifdef __cplusplus
extern "C"{
#endif
// Test required | Undone
typedef unsigned char (*Graphics_Input_Callback)(int value);

unsigned char graphic_register_window	(Window* window, const char* class);
unsigned char graphic_create_window		(Window* window, const char* name, long window_style, const long x, const long y, const long width, const long height);
unsigned char graphic_show_window		(Window* window, const unsigned char show);
unsigned char graphic_destroy_window	(Window* window);

unsigned char graphic_register_object	(Object* object, Object* dst, unsigned char size);
unsigned char graphic_remove_object		(Object* object, Object* src, unsigned char size);
unsigned char graphic_create_text		(Object* object, Window* parent_window, uVec2 position, uVec2 size, const char* text, Text* properties, Extra extra, unsigned int id);
unsigned char graphic_create_button		(Object* object, Window* parent_window, uVec2 position, uVec2 size, void* data, size_t data_size, Button* properties, Extra extra, unsigned int id);
unsigned char graphic_create_object		(Object* object, Window* window, Color* color);
unsigned char graphic_destroy_object	(Object* object);
unsigned char graphic_get_object_type   (Object* object);

#ifdef __cplusplus
}
#endif
