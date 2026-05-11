#include "SjenaDeskEngine/Core.h"

// Component | Set a Component | 0 = Success
unsigned char component_set(Component* component_slot, unsigned int type, void* data, size_t data_size){
    if(!component_slot) return 1;
    if (component_slot->data) return 1;
    if(data_size < 1)return 1;

    component_slot->data = malloc(data_size);
    if(component_slot->data == NULL) return 1;

    memcpy(component_slot->data, data, data_size);
    component_slot->type = type;
    component_slot->size = data_size;
    return 0;
}

// Component | Delete a Component | 0 = Success
unsigned char component_remove(Component* component){
    if(!component) return 1;
    if(!component->data) return 1;
    free(component->data);
    memset(component, 0, sizeof(Component));
    return 0;
}

Component* component_get(Component* component_arr, unsigned char length, unsigned int type){
    for (int i = 0; i < length; i++){
        if(component_arr[i].type == type)return &component_arr[i];
    }
    return NULL;
}
