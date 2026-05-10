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
unsigned char graphic_create_text(Object* object, Window* parent_window, uVec2 position, uVec2 size, const char* text, Text* properties, Extra extra, unsigned int id) {
	if(!object, !parent_window, !text, !properties) return 1;
	
	#if defined(_WIN32)
	if (!parent_window->hwnd) return 1;
	#elif defined(__linux__)
	if (!parent_window->hwnd) return 1;
	#endif

	size_t text_size = strlen(text)+1;
	object->data = malloc(text_size);
	if(!object->data){
		free(object->data);
		memset(object, 0, sizeof(Object));
		return 1;
	}

	object->properties = malloc(sizeof(Text));
	if(!object->properties){
		memset(object, 0, sizeof(Object));
		return 1;
	}

	memcpy(object->properties, properties, sizeof(Text));
	memcpy(object->data, text, text_size);

	object->parent_window = parent_window;
	object->data_size = text_size;
	object->position = position;
	object->extra = extra;
	object->size = size;
	object->type = OBJECT_TYPE_TEXT;
	object->id = id;
	return 0;
}

// Graphic | UI | Create Button Object | 0 = Success
unsigned char graphic_create_button(Object* object, Window* parent_window, uVec2 position, uVec2 size, const char* text, Button* properties, Extra extra, unsigned int id) {
	if (!object, !parent_window, !properties) return 1;

	#if defined(_WIN32)
	if (!parent_window->hwnd) return 1;
	#elif defined(__linux__)
	if (!parent_window->hwnd) return 1;
	#endif

	size_t data_size = (text) ? strlen(text)+1 : 0;

	if(text){
		object->data = malloc(data_size);
		if(!object->data)return 1;
	}

	object->properties = malloc(sizeof(Button));
	if(!object->properties){
		if(object->data)free(object->data);
		memset(object, 0, sizeof(Object));
		return 1;
	}

	memcpy(object->properties, properties, sizeof(Button));
	if(object->data)memcpy(object->data, text, strlen(text)+1);

	object->parent_window = parent_window;
	object->data_size = data_size;
	object->position = position;
	object->extra = extra;
	object->size = size;
	object->type = OBJECT_TYPE_BUTTON;
	object->id = id;

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
