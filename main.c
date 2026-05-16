#include <stdio.h>

#include "SjenaDeskEngine/Input/Input.h"
#include "SjenaDeskEngine/Graphics/Graphics.h"

int main(){
	input_key_setup_api();

	Window m_window = {0};
	graphic_register_window(&m_window, "SjenaDesk");
	graphic_create_window(&m_window, "SjenaDeskEngine", WS_EX_OVERLAPPEDWINDOW, 0, 0, 1000, 1000);
	graphic_show_window(&m_window, 1);

	unsigned char running = 1;
	unsigned char follow_c = 0;
	while (running)
	{
		input_key_handler_api();
		if(getKeyDown(KEYCODE_ESC))running = 0;
		if(getKeyDown(KEYCODE_W))graphic_show_window(&m_window, 1);
		if(getKeyDown(KEYCODE_S))graphic_show_window(&m_window, 0);
		if(getKeyDown(MOUSE_MIDDLE))follow_c = !follow_c;
		if(follow_c)graphic_set_pos_window(&m_window, input_mouse_get_position());
	}
	return 0;
}