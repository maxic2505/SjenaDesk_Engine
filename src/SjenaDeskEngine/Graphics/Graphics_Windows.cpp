#include "SjenaDeskEngine/Graphics/Graphics.h"



#if defined(_WIN32)

//HWND MANAGER
typedef struct HWND_SLOT{
	HWND hwnd;
	Window_Message msg_ptr;
	WINDOW_MSG_CODE flags;
}HWND_SLOT;

typedef struct HWND_MGR{
	HWND_SLOT* data;
	size_t size;

	Window_Message get_msg_ptr_by_hwnd(const HWND hwnd){
		if(!data)return NULL;
		for(size_t i = 0; i<=size;i++){
			if(data[i].hwnd == hwnd)return data[i].msg_ptr;
		}
		return NULL;
	}
	HWND_SLOT* get_slot_by_hwnd(const HWND hwnd){
		if(!data)return NULL;
		for(size_t i = 0; i<=size;i++){
			if(data[i].hwnd == hwnd)return &data[i];
		}
		return NULL;
	}
	unsigned char add(HWND hwnd, Window_Message msg_ptr, WINDOW_MSG_CODE flags){
		if(!hwnd || !msg_ptr) return 1;
		void* ptr = realloc(data, (size+1) * sizeof(HWND_SLOT));
		if(!ptr)return 4;
		((HWND_SLOT*)ptr)[size++] = HWND_SLOT{hwnd, msg_ptr, flags};
		data = (HWND_SLOT*)ptr;
		return 0;
	};

	Window_Message remove(HWND hwnd){
		Window_Message msg = get_msg_ptr_by_hwnd(hwnd);
		if(!msg) return NULL;
		HWND_SLOT* ptr = (HWND_SLOT*)malloc((size-1) * sizeof(HWND_SLOT));
		int added = 0;
		for(int i = 0; i<=size; i++){
			if(data[i].hwnd == hwnd)continue;
			ptr[added++] = data[i];
		}
		free(data);
		data = ptr;
		return msg;
	}
	void destroy(){
		if(data)free(data);
		data = NULL;
		size = 0;
	}
}HWND_MGR;

Object* objects;

HWND_MGR mgr = {0};

// https://learn.microsoft.com/de-de/windows/win32/api/winuser/nc-winuser-wndproc
// CALLBACK for Inputs
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HWND_SLOT* ptr = mgr.get_slot_by_hwnd(hwnd);
	if(ptr){
		WINDOW_MSG_CODE code = MSG_EMPTY;
		switch (uMsg){
		//CYCLE
		case WM_CREATE:
			code = MSG_CYCLE_CREATE;
		break;
		case WM_CLOSE:
			code = MSG_CYCLE_CLOSE;
		break;
		case WM_NCDESTROY:
			mgr.remove(hwnd);
			break;
		case WM_DESTROY:
			code = MSG_CYCLE_DESTROY;
			PostQuitMessage(0);
		break;

		//WINDOW
		case WM_SIZE:
			code = MSG_WINDOW_SIZE;
		break;
		case WM_MOVE:
			code = MSG_WINDOW_MOVE;
		break;
		case WM_SETFOCUS:
			code = MSG_WINDOW_SETFOCUS;
		break;
		case WM_KILLFOCUS:
			code = MSG_WINDOW_KILLFOCUS;
		break;
		case WM_ACTIVATE:
			code = MSG_WINDOW_ACTIVATE;
		break;
		case WM_PAINT:
			code = MSG_WINDOW_PAINT;
		break;
		case WM_ENTERSIZEMOVE:
			code = MSG_WINDOW_ENTERRESIZE;
		break;
		case WM_EXITSIZEMOVE:
			code = MSG_WINDOW_EXITRESIZE;
		break;
		
		// For Text usefull
		case WM_CHAR:
			code = MSG_CHAR;
		break;
		
		// RAWINPUT
		case WM_INPUT:
			code = MSG_INPUT;
		break;
		case WM_INPUT_DEVICE_CHANGE: break;
		default:break;
		}
		if (ptr->msg_ptr(code, wParam, (unsigned long long)lParam) == 0xff) PostMessage(hwnd, WM_CLOSE, 0, 0);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// CPP - MAIN

// Graphic | Register a Window | 0 = Success
unsigned char Window::register_window(const char* class_name){
	if (!class_name)return 1;

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
	wc.hInstance = GetModuleHandle(NULL);
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
unsigned char Window::create(Window_Message msg, WINDOW_MSG_CODE flags, const char* name, long window_style, const long x, const long y, const long width, const long height){
	if (this->hwnd) return 1;
	this->hwnd = CreateWindowExA(
		0,
		this->class_name,
		name,
		window_style,
		x, y, width, height,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	if (!this->hwnd) return 1;
	mgr.add(hwnd, msg, flags);
	return 0;
}

// Graphic | Show/Hidde a Window | 0 = Success
unsigned char Window::set_visibility(const unsigned char visibility){
	if (!this->hwnd) return 1;
	ShowWindow(this->hwnd, (visibility == 1) ? SW_SHOW : SW_HIDE);
	return 0;
}

// Graphic | Set/Change a Window pos. | 0 = Success
unsigned char Window::set_pos(iVec2 pos){
	if(!this->hwnd)return 1;
	SetWindowPos(this->hwnd, NULL, pos.x, pos.y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	UpdateWindow(this->hwnd);
	return 0;
}
unsigned char Window::handler(){
	MSG msg;
    // Keep Windows Thread alive
    while (GetMessage(&msg, nullptr, 0, 0)>0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if(msg.message == WM_QUIT)return 1;
    }
    return 0;
}

// Graphic | Destroy a Window | 0 = Success
unsigned char Window::destroy(){
	if(this->hwnd && IsWindow(this->hwnd))DestroyWindow(this->hwnd);
	mgr.remove(this->hwnd);
	if(this->class_name){
		UnregisterClassA(this->class_name, GetModuleHandle(nullptr));
		free(this->class_name);
		this->class_name = nullptr;
	}
	memset(this, 0, sizeof(Window));
	return 0;
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

#endif