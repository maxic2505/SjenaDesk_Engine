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

// Graphic | Register a Window | 0 = Success
unsigned char graphic_register_window(Window* window, const char* class) {
	if (!window)return 1;

	if (!hInstance)hInstance = GetModuleHandle(NULL);

	size_t class_size = strlen(class)+1;
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
}

// Graphic | Creates a Window | 0 = Success
unsigned char graphic_create_window(Window* window, const char* name, long window_style, const long x, const long y, const long width, const long height) {
	if (!window && window->hwnd) return 1;
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
	if (!window && !window->hwnd) return 1;
	ShowWindow(window->hwnd, (show == 1) ? SW_SHOW : SW_HIDE);
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