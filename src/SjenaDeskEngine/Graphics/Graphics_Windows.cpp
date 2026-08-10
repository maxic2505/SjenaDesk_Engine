#include "SjenaDeskEngine/Graphics/Graphics.h"



#if defined(_WIN32)
HINSTANCE hInstance = {0};
Object* objects;

// CALLBACK for Inputs
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// CPP - MAIN

// Graphic | Register a Window | 0 = Success
unsigned char Window::register_window(const char* class_name){
	if (!class_name)return 1;

	if (!hInstance)hInstance = GetModuleHandle(NULL);

	if(this->class_name){
		free(this->class_name);
		this->class_name = NULL;
	}

	size_t class_size = strlen(class_name)+1;
	this->class_name = (char*)malloc(class_size);
	if(!this->class_name)return 1;
	memcpy(this->class_name, class_name, class_size);

	WNDCLASSEXA wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL; 
	wc.lpszClassName = this->class_name;

	unsigned char status = (RegisterClassExA(&wc) == 0) ? ((GetLastError() != ERROR_CLASS_ALREADY_EXISTS) ? 1 : 0) : 0;
	if(status){
		free(this->class_name);
		this->class_name = NULL;
	}
	return status;
}

// Graphic | Creates a Window | 0 = Success
unsigned char Window::create(const char* name, long window_style, const long x, const long y, const long width, const long height){
	if (this->hwnd) return 1;
	if(!hInstance)return 1;
	this->hwnd = CreateWindowExA(
		0,
		this->class_name,
		name,
		window_style,
		x, y, width, height,
		NULL, NULL, hInstance, NULL);
	if (!this->hwnd) return 1;
	return 0;
}

// Graphic | Show/Hidde a Window | 0 = Success
unsigned char Window::set_visibility(const unsigned char visibility){
	if (!this->hwnd) return 1;
	ShowWindow(this->hwnd, (visibility == 1) ? SW_SHOW : SW_HIDE);
	return 0;
}

// Graphic | Set/Change a Window pos. | 0 = Success
unsigned char Window::set_pos(uVec2 pos){
	if(!this->hwnd)return 1;
	SetWindowPos(this->hwnd, NULL, pos.x, pos.y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	UpdateWindow(this->hwnd);
	return 0;
}

// Graphic | Destroy a Window | 0 = Success
unsigned char Window::destroy(){
	if (this->hwnd && DestroyWindow(this->hwnd)) {
		if(this->class_name)free(this->class_name);
		memset(this, 0, sizeof(Window));
		return 0;
	}else return 1;
}

unsigned char graphic_render_text(Object* object, HDC* hdc, HBRUSH* brush) {
	return 0;
}
unsigned char graphic_render_button(Object* object, HDC* hdc, HBRUSH* brush) {
	return 0;
}
unsigned char graphic_render_object(Object* object, HDC* hdc, HBRUSH* brush) {
	return 0;
}


// C - BRIDGE

// Graphic | Register a Window | 0 = Success
unsigned char graphic_register_window(Window* window, const char* class_name) {
	return (window) ? window->register_window(class_name) : 1;
}

// Graphic | Creates a Window | 0 = Success
unsigned char graphic_create_window(Window* window, const char* name, long window_style, const long x, const long y, const long width, const long height) {
	return (window) ? window->create(name, window_style, x, y, width, height) : 1;
}

// Graphic | Show/Hidde a Window | 0 = Success
unsigned char graphic_set_visibility(Window* window, const unsigned char visibility) {
	return (window) ? window->set_visibility(visibility) : 1;
}

// Graphic | Set/Change a Window pos. | 0 = Success
unsigned char graphic_set_pos_window(Window* window, uVec2 pos){
	return (window) ? window->set_pos(pos) : 1;
}

// Graphic | Destroy a Window | 0 = Success
unsigned char graphic_destroy_window(Window* window) {
	return (window) ? window->destroy() : 1;
}

#endif