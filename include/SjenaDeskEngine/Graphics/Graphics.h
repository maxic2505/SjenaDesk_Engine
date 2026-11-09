#pragma once

#include <stdlib.h>
#include <string.h>
#include "SjenaDeskEngine/Math/Vector.h"

#define SJENADESK_WINDOW_LIB 1

#define WINDOW_MAX_CLASS_SIZE 24
#define OBJECT_TYPE_BUTTON 6
#define OBJECT_TYPE_TEXT 2

#ifdef _WIN32
#include <Windows.h>
#endif

typedef struct Color { unsigned char r, g, b, a; } Color;

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
	#ifdef __cplusplus
	unsigned char create(Color* color);
	unsigned char create_text(uVec2 position, uVec2 size, const char* text, Text* properties, Extra extra, unsigned int id);
	unsigned char create_button(uVec2 position, uVec2 size, void* data, size_t data_size, Button* properties, Extra extra, unsigned int id);
	unsigned char destroy();
	#endif
}Object;

typedef unsigned char(*Window_Message)(void* class_ptr, unsigned long long code, unsigned long long data);

typedef enum WINDOW_MSG_CODE : unsigned long long{
	MSG_INPUT			 = 1ULL<<0,
	MSG_CYCLE_CREATE	 = 1ULL<<1,
	MSG_CYCLE_CLOSE		 = 1ULL<<2,
	MSG_CYCLE_DESTROY	 = 1ULL<<3,
	MSG_CHAR			 = 1ULL<<4,
	MSG_WINDOW_MOVE		 = 1ULL<<5,
	MSG_WINDOW_SIZE		 = 1ULL<<6,
	MSG_WINDOW_PAINT	 = 1ULL<<7,
	MSG_WINDOW_ACTIVATE	 = 1ULL<<8,
	MSG_WINDOW_SETFOCUS	 = 1ULL<<9,
	MSG_WINDOW_KILLFOCUS = 1ULL<<10,
	MSG_WINDOW_ENTERRESIZE = 1ULL<<11,
	MSG_WINDOW_EXITRESIZE  = 1ULL<<12,
	MSG_FOREGROUND		 = 1ULL<<13, 
	MSG_BACKGROUND		 = 1ULL<<14,
}WINDOW_MSG_CODE;

#define MSG_WINDOW (MSG_WINDOW_MOVE | MSG_WINDOW_SIZE | MSG_WINDOW_PAINT | MSG_WINDOW_ACTIVATE | MSG_WINDOW_SETFOCUS | MSG_WINDOW_KILLFOCUS)
#define MSG_CYCLE (MSG_CYCLE_CREATE | MSG_CYCLE_CLOSE | MSG_CYCLE_DESTROY)
typedef struct Window {
	char* class_name;
	Object* objects;
	unsigned long long size;

	#if defined(_WIN32)
	HWND hwnd;
	#elif defined(__linux__)
	void* hwnd;
	#endif

	#ifdef __cplusplus
	unsigned char register_window	(const char* class_name);
	unsigned char create			(Window_Message msg, void* msg_class, WINDOW_MSG_CODE flags, const char* name, long window_style, const long x, const long y, const long width, const long height);
	unsigned char set_visibility	(const unsigned char visibility);
	unsigned char set_pos			(uVec2 pos);
	unsigned char destroy			();
	#endif
}Window;

#ifdef __cplusplus
extern "C"{
#endif

unsigned char graphic_register_window	(Window* window, const char* class_name);
unsigned char graphic_create_window		(Window* window, Window_Message msg, void* msg_class, WINDOW_MSG_CODE flags, const char* name, long window_style, const long x, const long y, const long width, const long height);
unsigned char graphic_set_visibility	(Window* window, const unsigned char visibility);
unsigned char graphic_set_pos_window	(Window* window, uVec2 pos);
unsigned char graphic_destroy_window	(Window* window);

unsigned char graphic_create_text		(Object* object, uVec2 position, uVec2 size, const char* text, Text* properties, Extra extra, unsigned int id);
unsigned char graphic_create_button		(Object* object, uVec2 position, uVec2 size, void* data, size_t data_size, Button* properties, Extra extra, unsigned int id);
unsigned char graphic_create_object		(Object* object, Color* color);
unsigned char graphic_destroy_object	(Object* object);

unsigned char graphic_register_object	(Object* object, Object* dst, unsigned char size);
unsigned char graphic_remove_object		(Object* object, Object* src, unsigned char size);

#ifdef __cplusplus
}
#endif
