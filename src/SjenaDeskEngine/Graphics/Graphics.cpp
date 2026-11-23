#include "SjenaDeskEngine/Graphics/Graphics.h"



// C - BRIDGE

// Graphic | Register a Window | 0 = Success
unsigned char graphic_register_window(Window* window, const char* class_name) {
	return (window) ? window->register_window(class_name) : 1;
}

// Graphic | Creates a Window | 0 = Success
unsigned char graphic_create_window(Window* window, Window_Message msg, WINDOW_MSG_CODE flags, const char* name, long window_style, const long x, const long y, const long width, const long height) {
	return (window) ? window->create(msg, flags, name, window_style, x, y, width, height) : 1;
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

// CPP - MAIN

// Graphic | UI | Create Plain Object | 0 = Success
unsigned char Object::create(Color* color){
	return 0;
}

// Graphic | UI | Create Text Object | 0 = Success
unsigned char Object::create_text(uVec2 position, uVec2 size, const char* text, Text* properties, Extra extra, unsigned int id){
	if(!text || !properties) return 1;

	size_t text_size = strlen(text)+1;
	this->data = malloc(text_size);
	if(!this->data)return 1;

	this->properties = malloc(sizeof(Text));
	if(!this->properties){
		free(this->data);
		this->data = NULL;
		return 1;
	}

	memcpy(this->properties, properties, sizeof(Text));
	memcpy(this->data, text, text_size);

	this->data_size = text_size;
	this->position = position;
	this->extra = extra;
	this->size = size;
	this->type = OBJECT_TYPE_TEXT;
	this->id = id;
	return 0;
}

// Graphic | UI | Create Button Object | 0 = Success
unsigned char Object::create_button(uVec2 position, uVec2 size, void* data, size_t data_size, Button* properties, Extra extra, unsigned int id){
	if (!properties) return 1;

	size_t data_s = data ? ((extra & USE_TEXT) ? strlen((char*)data)+1 : data_s) : 0;

	if(data && (extra & USE_TEXT) ? data_s>0 : data_size){
		this->data = malloc(data_s);
		if(!this->data)return 1;
	}

	this->properties = malloc(sizeof(Button));
	if(!this->properties){
		if(this->data)free(this->data);
		this->data = NULL;
		return 1;
	}

	memcpy(this->properties, properties, sizeof(Button));
	if(this->data)memcpy(this->data, data, data_s);

	this->data_size = data_s;
	this->position = position;
	this->extra = extra;
	this->size = size;
	this->type = OBJECT_TYPE_BUTTON;
	this->id = id;

	return 0;
}

// Graphic | UI | Destroy Object | 0 = Success
unsigned char Object::destroy(){
	if (this->properties)free(this->properties);
	if (this->data)free(this->data);
	memset(this, 0, sizeof(Object));
	return 0;
}

// Graphic | UI | Register Object | 0 = Success

// Graphic | UI | Remove Object | 0 = Success

// C - BRIDGE

// Graphic | UI | Create Plain Object | 0 = Success
unsigned char graphic_create_object(Object* object, Color* color) {
	return 0;
}

// Graphic | UI | Create Text Object | 0 = Success
unsigned char graphic_create_text(Object* object, uVec2 position, uVec2 size, const char* text, Text* properties, Extra extra, unsigned int id) {
	return (object) ? object->create_text(position, size, text, properties, extra, id) : 1;
}

// Graphic | UI | Create Button Object | 0 = Success
unsigned char graphic_create_button(Object* object, uVec2 position, uVec2 size, void* data, size_t data_size, Button* properties, Extra extra, unsigned int id) {
	return (object) ? object->create_button(position, size, data, data_size, properties, extra, id) : 1;
}

// Graphic | UI | Destroy Object | 0 = Success
unsigned char graphic_destroy_object(Object* object) {
	return (object) ? object->destroy() : 1;
}

// Graphic | UI | Register Object | 0 = Success
unsigned char graphic_register_object(Object* object, Object* dst, unsigned char size) {
	if (!object | !dst) return 1;
	return 0;
}
// Graphic | UI | Remove Object | 0 = Success
unsigned char graphic_remove_object(Object* object, Object* src, unsigned char size) {
	if (!object | !src) return 1;
	return 0;
}
