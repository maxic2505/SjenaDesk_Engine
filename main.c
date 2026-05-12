#include <stdio.h>

#include "SjenaDeskEngine/Math/Vector.h"
#include "SjenaDeskEngine/Core.h"

int main(){
	Component cmp = {0};
	component_create(&cmp, LOCKED_DATA, 1, 0, &(Vec2){67, 67}, sizeof(Vec2));
	printf("FREE CREATE: %s\n", (component_free(&cmp)) ? "FAILED" : "SUCCESS");
	cmp.properties &= ~LOCKED_DATA;
	printf("FREE CREATE: %s\n", (component_free(&cmp)) ? "FAILED" : "SUCCESS");
	return 0;
}
