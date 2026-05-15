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
	}
	return 0;
}