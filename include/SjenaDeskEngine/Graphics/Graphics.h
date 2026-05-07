#pragma once

#include <stdlib.h>
#include <string.h>
#include "SjenaDeskEngine/Math/Vector.h"

#define WINDOW_MAX_CLASS_SIZE 24
#define OBJECT_TYPE_BUTTON 12
#define OBJECT_TYPE_TEXT 5

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

typedef struct Object {
	Window* parent_window;
	long  type;
	void* object;
	long  size;
	void* data;
	size_t size;
	uVec2 position, size;
}Object;

typedef struct Text {
	unsigned char font_size;
	unsigned char font;
	unsigned char style;

	Color color;
}Text;

typedef struct Button {
	unsigned char id;
	unsigned char is_active;
	unsigned char is_pressed;

	unsigned char color_strength;
	unsigned char style;
	unsigned char border_roundness;

	Color color_over;
	Color color_on_click;
	Color color_active;
	Color color_deactive;

}Button;

#ifdef __cplusplus
extern "C"{
#endif
// Testen bitte!!!
typedef unsigned char (*Graphics_Input_Callback)(int value);

unsigned char graphic_register_window	(Window* window, const char* class);
unsigned char graphic_create_window		(Window* window, const char* name, long window_style, const long x, const long y, const long width, const long height);
unsigned char graphic_show_window		(Window* window, const unsigned char show);
unsigned char graphic_destroy_window	(Window* window);

unsigned char graphic_register_object	(Object* object, Object* dst, unsigned char size);
unsigned char graphic_remove_object		(Object* object, Object* src, unsigned char size);
unsigned char graphic_create_text		(Object* object, Window* window, uVec2 position, uVec2 size, Text* text_object, const char* text);
unsigned char graphic_create_button		(Object* object, Window* window, uVec2 position, uVec2 size, Button* button		, const char* text);
unsigned char graphic_create_object		(Object* object, Window* window, Color* color);
unsigned char graphic_destroy_object	(Object* object);
unsigned char graphic_get_object_type   (Object* object);

#ifdef __cplusplus
}
#endif
