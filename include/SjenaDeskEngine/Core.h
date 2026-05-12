#pragma once

#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef enum ComponentProperties{
    LOCKED_DATA    = 1<<0,
    LOCKED_TYPE    = 1<<1,
    REGISTERED_MGR = 1<<2,
    REGISTERED_SYS = 1<<3,
}ComponentProperties;

typedef struct Component{
    void* data;

    unsigned int size;

    unsigned char properties;
    unsigned char type;
    unsigned char id;
    unsigned char u_data;
}Component;

typedef struct ComponentManager{
    Component *components;
    long long size;
}ComponentManager;

unsigned char component_create(Component* cmp, unsigned char properties, unsigned int type, unsigned char id, void* data, size_t data_size);

unsigned char component_free(Component* cmp);

ComponentManager component_mgr_create(unsigned int size);

unsigned char component_mgr_free(ComponentManager* mgr);
#ifdef __cplusplus
}
#endif
