#pragma once

#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Component{
    void* data;        //  8 Bytes
    size_t size;       //  4 Bytes
    unsigned int type; //  4 Bytes
}Component;            // 16 Bytes

// Components | Set a Component | 0 : OK
unsigned char component_set(Component* component_slot, unsigned int type, void* data, size_t data_size);

// Components | Remove the Component | 0 : OK
unsigned char component_remove(Component* componentSlot);

// Components | Search and get the Data | null : ERROR else OK.
Component* component_get(Component* component_arr, unsigned char length, unsigned int type);

#ifdef __cplusplus
}
#endif
