#include "SjenaDesk_Components.h"

unsigned char component_set(Component* component_slot, const char* type, void* data, size_t data_size){
    if(!component_slot) return 1;
    if (component_slot->data) free(component_slot->data);
    component_slot->data = NULL;
    size_t length = strlen(type);
    if(length>=24)return 1;
    if(data_size < 1)return 1;
    component_slot->data = malloc(data_size);
    if(component_slot->data == NULL) return 1;
    memcpy(component_slot->type, type, length + 1);
    memcpy(component_slot->data, data, data_size);
    return 0;
}

unsigned char component_remove(Component* component){
    if(!component) return 1;
    if(!component->data) return 1;
    free(component->data);
    component->data = NULL;
    memset(component->type, 0, sizeof(component->type));
    return 0;
}

void* component_get(const Component* component_arr, const unsigned char length, const char* type){
    for (int i = 0; i < length; i++){
        if(strcmp(component_arr[i].type, type) == 0)return component_arr[i].data;
    }
    return NULL;
}