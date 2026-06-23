#include "SjenaDeskEngine/Graphics/Graphics.h"



#if defined(_WIN32)

/*
int FillRect(
  [in] HDC        hDC,
  [in] const RECT *lprc,
  [in] HBRUSH     hbr
);
x, y, w, h
r, g , b, a

*/

unsigned char graphic_render_text(Object* object, HDC* hdc, HBRUSH* brush) {
	return 0;
}
unsigned char graphic_render_button(Object* object, HDC* hdc, HBRUSH* brush) {
	return 0;
}
unsigned char graphic_render_object(Object* object, HDC* hdc, HBRUSH* brush) {
	return 0;
}



HINSTANCE hInstance = {0};
Object* objects;

// CALLBACK for Inputs
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Graphic | Register a Window | 0 = Success
unsigned char graphic_register_window(Window* window, const char* class) {
	if (!window || !class)return 1;

	if (!hInstance)hInstance = GetModuleHandle(NULL);

	if(window->class){
		free(window->class);
		window->class = NULL;
	}

	size_t class_size = strlen(class)+1;
	window->class = malloc(class_size);
	if(!window->class)return 1;
	memcpy(window->class, class, class_size);

	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL; 
	wc.lpszClassName = window->class;

	unsigned char status = (RegisterClassEx(&wc) == 0) ? ((GetLastError() != ERROR_CLASS_ALREADY_EXISTS) ? 1 : 0) : 0;
	if(status){
		free(window->class);
		window->class = NULL;
	}
	return status;
}

// Graphic | Creates a Window | 0 = Success
unsigned char graphic_create_window(Window* window, const char* name, long window_style, const long x, const long y, const long width, const long height) {
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
	return 0;
}

// Graphic | Show/Hidde a Window | 0 = Success
unsigned char graphic_show_window(Window* window, const unsigned char show) {
	if (!window || !window->hwnd) return 1;
	ShowWindow(window->hwnd, (show == 1) ? SW_SHOW : SW_HIDE);
	return 0;
}

unsigned char graphic_set_pos_window(Window* window, uVec2 pos){
	if(!window)return 1;
	SetWindowPos(window->hwnd, NULL, pos.x, pos.y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	UpdateWindow(window->hwnd);
	return 0;
}

// Graphic | Destroy a Window | 0 = Success
unsigned char graphic_destroy_window(Window* window) {
	if (window && window->hwnd && DestroyWindow(window->hwnd)) {
		memset(window, 0, sizeof(Window));
	}else return 1;

    return 0;
}

#endif