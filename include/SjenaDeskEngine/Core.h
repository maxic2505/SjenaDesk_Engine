#pragma once

#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef enum ComponentProperties{
    REGISTERED = 1<<0,
    LOCKED     = 1<<1,
    READ_ONLY  = 1<<2,
}ComponentProperties;

typedef struct Component{
    void* data;
    unsigned int size;
    unsigned char properties;
}Component;

typedef struct ComponentManager{
    Component *components;
    long long size;
}ComponentManager;

Component component_create(unsigned int type, void* data, size_t data_size);

unsigned char component_free(Component* componentSlot);

ComponentManager component_mgr_create(unsigned int size);

unsigned char component_mgr_free(ComponentManager* mgr);
#ifdef __cplusplus
}
#endif
