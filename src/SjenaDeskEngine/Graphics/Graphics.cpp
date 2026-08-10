#include "SjenaDeskEngine/Graphics/Graphics.h"

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
	
	if(extra & USE_TEXT) data_size = (data) ? strlen((char*)data)+1 : 0;

	if(data && data_size>0){
		this->data = malloc(data_size);
		if(!this->data)return 1;
	}

	this->properties = malloc(sizeof(Button));
	if(!this->properties){
		if(this->data)free(this->data);
		this->data = NULL;
		return 1;
	}

	memcpy(this->properties, properties, sizeof(Button));
	if(this->data)memcpy(this->data, data, data_size);

	this->data_size = data_size;
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
