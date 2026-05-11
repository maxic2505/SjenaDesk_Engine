#include "SjenaDeskEngine/Core.h"

// Component | Set a Component | NULL : Failed
unsigned char component_create(Component* cmp, unsigned int type, void* data, size_t data_size){
    if(!cmp || cmp->data)return 1;
    if(data_size < 1)return 1;

    cmp->data = malloc(data_size);
    if(!cmp->data) return 1;

    memcpy(cmp->data, data, data_size);
    cmp->type = type;
    cmp->size = data_size;
    return 0;
}

// Component | Delete a Component | 0 : Success
unsigned char component_free(Component* component){
    if(!component) return 1;
    if(!component->data) return 1;
    free(component->data);
    memset(component, 0, sizeof(Component));
    return 0;
}
