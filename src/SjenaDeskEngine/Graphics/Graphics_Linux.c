#include "SjenaDeskEngine/Graphics/Graphics.h"



#if defined(__linux__)

unsigned char graphic_render_text(Object* object, HDC* hdc, HBRUSH* brush) {
	return 0;
}
unsigned char graphic_render_button(Object* object, HDC* hdc, HBRUSH* brush) {
	return 0;
}
unsigned char graphic_render_object(Object* object, HDC* hdc, HBRUSH* brush) {
	return 0;
}



// Graphic | Register a Window | 0 = Success
unsigned char graphic_register_window(Window* window, const char* class) {
	return 0;
}

// Graphic | Creates a Window | 0 = Success
unsigned char graphic_create_window(Window* window, const char* name, long window_style, const long x, const long y, const long width, const long height) {
	return 0;
}

// Graphic | Show/Hidde a Window | 0 = Success
unsigned char graphic_show_window(Window* window, const unsigned char show) {
	return 0;
}

// Graphic | Destroy a Window | 0 = Success
unsigned char graphic_destroy_window(Window* window) {
    return 0;
}

#endif