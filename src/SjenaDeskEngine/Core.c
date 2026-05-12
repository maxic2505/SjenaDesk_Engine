#include "SjenaDeskEngine/Core.h"

// Component | Set a Component | 0 : Success
unsigned char component_create(Component* cmp, unsigned char properties, unsigned int type, unsigned char id, void* data, size_t data_size){
    if(!cmp || cmp->data)return 1;
    if(data_size < 1)return 1;

    cmp->data = malloc(data_size);
    if(!cmp->data) return 1;

    memcpy(cmp->data, data, data_size);
    cmp->properties = properties;
    cmp->type = type;
    cmp->id = id;
    return 0;
}

// Component | Delete a Component | 0 : Success
unsigned char component_free(Component* cmp){
    if(!cmp) return 1;
    if(!cmp->data) return 1;
    if(cmp->properties & (LOCKED_DATA | REGISTERED_SYS | REGISTERED_MGR)) return 1;
    free(cmp->data);
    memset(cmp, 0, sizeof(Component));
    return 0;
}
