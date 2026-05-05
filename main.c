#include <stdio.h>

//#include "Engine/Graphics/SjenaDesk_Graphics.h"
//#include "Engine/Input/SjenaDesk_Input.h"
//#include "Engine/SjenaDesk_Engine.h"
#include "Engine/SjenaDesk_Components.h"
#include "Engine/Math/SjenaDesk_Vector.h"

int main(){
	Component component = {0};
	component_set(&component, 1, &(Vec2){25, 25}, sizeof(Vec2));
	printf("Component | type:%u - data:(%2.2f|%2.2f) - size:%lu", component.type, ((Vec2*)component.data)->x, ((Vec2*)component.data)->y, component.size);
	return 0;
}
