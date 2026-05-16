#include "SjenaDeskEngine/Graphics/Graphics.h"

// Graphic | UI | Create Text Object | 0 = Success
unsigned char graphic_create_text(Object* object, uVec2 position, uVec2 size, const char* text, Text* properties, Extra extra, unsigned int id) {
	if(!object || !text || !properties) return 1;

	size_t text_size = strlen(text)+1;
	object->data = malloc(text_size);
	if(!object->data)return 1;

	object->properties = malloc(sizeof(Text));
	if(!object->properties){
		free(object->data);
		object->data = NULL;
		return 1;
	}

	memcpy(object->properties, properties, sizeof(Text));
	memcpy(object->data, text, text_size);

	object->data_size = text_size;
	object->position = position;
	object->extra = extra;
	object->size = size;
	object->type = OBJECT_TYPE_TEXT;
	object->id = id;
	return 0;
}

// Graphic | UI | Create Button Object | 0 = Success
unsigned char graphic_create_button(Object* object, uVec2 position, uVec2 size, void* data, size_t data_size, Button* properties, Extra extra, unsigned int id) {
	if (!object || !properties) return 1;

	if(extra & USE_TEXT) data_size = (data) ? strlen(data)+1 : 0;

	if(data && data_size>0){
		object->data = malloc(data_size);
		if(!object->data)return 1;
	}

	object->properties = malloc(sizeof(Button));
	if(!object->properties){
		if(object->data)free(object->data);
		object->data = NULL;
		return 1;
	}

	memcpy(object->properties, properties, sizeof(Button));
	if(object->data)memcpy(object->data, data, data_size);

	object->data_size = data_size;
	object->position = position;
	object->extra = extra;
	object->size = size;
	object->type = OBJECT_TYPE_BUTTON;
	object->id = id;

	return 0;
}
// Graphic | UI | Create Plain Object | 0 = Success
unsigned char graphic_create_object(Object* object, Color* color) {
	return 0;
}
// Graphic | UI | Destroy Object | 0 = Success
unsigned char graphic_destroy_object(Object* object) {
	if (!object) return 1;
	if (object->properties)free(object->properties);
	if (object->data)free(object->data);
	memset(object, 0, sizeof(Object));
	return 0;
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
