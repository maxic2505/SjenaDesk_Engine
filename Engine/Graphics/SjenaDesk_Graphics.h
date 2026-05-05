#pragma once

#include "../Math/SjenaDesk_Vector.h"

#define WINDOW_MAX_CLASS_SIZE 24
#define OBJECT_TEXT_MAX_DATA_SIZE 56
#define OBJECT_BUTTON_MAX_TEXT_SIZE 40
#define OBJECT_TYPE_BUTTON 12
#define OBJECT_TYPE_TEXT 5

#ifdef _WIN32
#include <Windows.h>
#define ALIGN_TO_8 __declspec(align(8))
#endif

#ifdef _WIN32
typedef struct Window {
	HWND hwnd;

	char class[WINDOW_MAX_CLASS_SIZE];
}Window;
#endif

typedef struct Object {
	Window* parent_window;
	void* data;
	uVec2 position, size;
}Object;

typedef struct Color { unsigned char r, g, b, a; } Color;

ALIGN_TO_8
typedef struct Text {
	unsigned char type;

	unsigned char font_size;
	unsigned char font;
	unsigned char style;

	Color color;
	char data[OBJECT_TEXT_MAX_DATA_SIZE];
}Text;

ALIGN_TO_8
typedef struct Button {
	unsigned char type;

	unsigned char id;
	unsigned char is_active;
	unsigned char is_pressed;

	unsigned char color_strength;
	unsigned char style;
	unsigned char border_roundness;
	unsigned char data;

	Color color_over;
	Color color_on_click;
	Color color_active;
	Color color_deactive;

	char text[OBJECT_BUTTON_MAX_TEXT_SIZE];
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

unsigned char graphic_create_text		(Object* object, Window* window, uVec2 position, uVec2 size, Text* text_object, const char* text);
unsigned char graphic_create_button		(Object* object, Window* window, uVec2 position, uVec2 size, Button* button		, const char* text);
unsigned char graphic_create_object		(Object* object, Window* window, Color* color);
unsigned char graphic_register_object	(Object* object, Object* dst, unsigned char size);
unsigned char graphic_remove_object		(Object* object, Object* src, unsigned char size);
unsigned char graphic_destroy_object	(Object* object);
unsigned char graphic_get_object_type   (Object* object);

#ifdef __cplusplus
}
#endif