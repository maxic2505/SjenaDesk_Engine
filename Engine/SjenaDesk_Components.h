#pragma once

#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Component{
    char type[24]; // 24 Bytes
    void* data;    //  8 Bytes
}Component;        // 32 Bytes

// Components | Set a Component | 0 : OK    
unsigned char component_set(Component* component_slot, const char* type, void* data, size_t data_size);

// Components | Remove the Component | 0 : OK
unsigned char component_remove(Component* componentSlot);

// Components | Search and get the Data | null : ERROR else OK.
void* component_get(const Component* component_arr, const unsigned char length, const char* type);

#ifdef __cplusplus
}
#endif