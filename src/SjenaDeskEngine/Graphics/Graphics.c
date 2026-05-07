#include "SjenaDeskEngine/Graphics/Graphics.h"

#ifdef _WIN32

unsigned char graphic_render_text(Object* object, HDC* hdc, HBRUSH* brush) {

}
unsigned char graphic_render_button(Object* object, HDC* hdc, HBRUSH* brush) {

}
unsigned char graphic_render_object(Object* object, HDC* hdc, HBRUSH* brush) {

}

HINSTANCE hInstance = {0};
Object* objects;

// CALLBACK for Inputs
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_PAINT : {
			PAINTSTRUCT ps = { 0 };
			HDC hdc = BeginPaint(hwnd, &ps);
			RECT r = {
				.bottom = 5,
				.left = 5,
				.right = 105,
				.top = 105
			};
			HBRUSH br = CreateSolidBrush(RGB(255, 0, 0));
			FillRect(hdc, &r, br);
			EndPaint(hwnd, &ps);
			DeleteObject(br);
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#endif

// Graphic | Register a Window | 0 = Success
unsigned char graphic_register_window(Window* window, const char* class) {
	if (!window)return 1;

	#if defined(_WIN32)
	if (!hInstance)hInstance = GetModuleHandle(NULL);
	unsigned char class_size = strlen(class)+1;
	if (class_size >= WINDOW_MAX_CLASS_SIZE)return 1;
	memcpy(window->class, class, class_size);
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 
	wc.lpszClassName = window->class;
	unsigned char status = (RegisterClassEx(&wc) == 0) ? ((GetLastError() != ERROR_CLASS_ALREADY_EXISTS) ? 1 : 0) : 0;
	if(status)memset(window->class, 0, WINDOW_MAX_CLASS_SIZE);
	return status;
	#elif defined(__linux)
	return 0;
	#endif
}

// Graphic | Creates a Window | 0 = Success
unsigned char graphic_create_window(Window* window, const char* name, long window_style, const long x, const long y, const long width, const long height) {
	#if defined(_WIN32)
	if (!window || window->hwnd) return 1;
	if(!hInstance)return 1;
	window->hwnd = CreateWindowEx(
		0,
		window->class,
		name,
		window_style,
		x, y, width, height,
		NULL, NULL, hInstance, NULL);
	if (!window->hwnd) return 1;
	#elif defined(__linux__)

	#endif
	return 0;
}
// Graphic | Show/Hidde a Window | 0 = Success
unsigned char graphic_show_window(Window* window, const unsigned char show) {
	#if defined(_WIN32)
	if (!window || !window->hwnd) return 1;
	ShowWindow(window->hwnd, (show == 1) ? SW_SHOW : SW_HIDE);
	#elif defined(__linux)

	#endif
	return 0;
}
// Graphic | Destroy a Window | 0 = Success
unsigned char graphic_destroy_window(Window* window) {
	#if defined(_WIN32)
	if (window && window->hwnd && DestroyWindow(window->hwnd)) {
		memset(window, 0, sizeof(Window));
	}else return 1;
	#elif defined(__linux__)

	#endif
	return 0;
}

// Graphic | UI | Create Text Object | 0 = Success
unsigned char graphic_create_text(Object* object, Window* window, uVec2 position, uVec2 size, Text* text_object, const char* text) {
	#if defined(_WIN32)
	if (!object, !window, !window->hwnd, !text_object, !text) return 1;
	#elif defined(__linux__)

	#endif
	unsigned char data_size = strlen(text)+1;
	if (data_size >= OBJECT_TEXT_MAX_DATA_SIZE)return 1;

	object->data = malloc(sizeof(Text));
	if(!object->data)return 1;

	object->parent_window = window;
	object->position = position;
	object->size = size;

	memcpy(object->data, &(Text){
		.type = 1,
		.font_size = text_object->font_size,
		.font = text_object->font,
		.style = text_object->style,
		.color = text_object->color,
	}, sizeof(Text));
	memcpy(((Text*)object->data)->data, text, data_size); // 30.04.2026 | new, untested | remove if tested & compiled
	return 0;
}
// Graphic | UI | Create Button Object | 0 = Success | 30.04.2026 >> new, untested
unsigned char graphic_create_button(Object* object, Window* window, uVec2 position, uVec2 size, Button* button, const char* text) {
	if (!object, !window, !button) return 1;

	// ... object data

	if (text){
		unsigned char data_text_size = (strlen(text)+1);
		if(data_text_size >= OBJECT_BUTTON_MAX_TEXT_SIZE)return 1;
		memcpy(((Button*)object->data)->text, text, data_text_size);
	}
	return 0;
}
// Graphic | UI | Create Plain Object | 0 = Success
unsigned char graphic_create_object(Object* object, Window* window, Color* color) {
	return 0;
}
// Graphic | UI | Regíster Object | 0 = Success
unsigned char graphic_register_object(Object* object, Object* dst, unsigned char size) {
	if (!object | !dst) return 1;
	return 0;
}
// Graphic | UI | Remove Object | 0 = Success
unsigned char graphic_remove_object(Object* object, Object* src, unsigned char size) {
	if (!object | !src) return 1;
	return 0;
}
// Graphic | UI | Destroy Object | 0 = Success
unsigned char graphic_destroy_object(Object* object) {
	if (!object) return 1;
	return 0;
}

/*
int FillRect(
  [in] HDC        hDC,
  [in] const RECT *lprc,
  [in] HBRUSH     hbr
);
x, y, w, h
r, g , b, a

*/
