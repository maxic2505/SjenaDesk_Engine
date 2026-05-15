#include <stdio.h>

#include "SjenaDeskEngine/Input/Input.h"

int main(){
	input_key_setup_api();
	
	unsigned char running = 1;
	while (running)
	{
		input_key_handler_api();
		if(getKeyDown(KEYCODE_ESC))running = 0;
		if(getKeyDown(KEYCODE_W) && getKeyDown(KEYCODE_LEFT_CTRL))printf("Moving Left\n");
		if(getKeyDown(KEYCODE_S))printf("Moving Down\n");
		if(getKeyDown(MOUSE_LEFT))printf("MOUSE LEFT\n");
		if(getKeyDown(MOUSE_MIDDLE))printf("MOUSE MIDDLE\n");
		if(getKeyDown(MOUSE_RIGHT))printf("MOUSE RIGHT\n");
	}
	return 0;
}