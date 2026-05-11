#include <stdio.h>

#include "SjenaDeskEngine/Math/Vector.h"
#include "SjenaDeskEngine/Core.h"

int main(){
	Component component[64] = { 0 };
	component_set(&component[21], 1, &(Vec2){25, 25}, sizeof(Vec2));
	Component* temp = component_get(&component, 64, 1);
	printf("Component | type:%u - data:(%2.2f|%2.2f) - size:%u", temp->type, ((Vec2*)temp->data)->x, ((Vec2*)temp->data)->y, temp->size);
	return 0;
}
