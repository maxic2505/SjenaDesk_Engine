#include "SjenaDeskEngine/Input/Input.h"

#define POINTER_ERR 0XFF

unsigned char Keyboard::get_key         (const SjenaKeyCode code){return (held_keys & code) ? 1 : 0;}

unsigned char Keyboard::get_key_down    (const SjenaKeyCode code){return (pressed_keys & code) ? 1 : 0;}

unsigned char Keyboard::set_key(const SjenaKeyCode code, const unsigned char state){
    held_keys = (held_keys & ~code) | (state ? code : 0);
    return state;
}
unsigned char Keyboard::set_key_down(const SjenaKeyCode code){
    pressed_keys |= code;
    return 0;
}

unsigned char Keyboard::callback(SjenaKeyCode code, int value){
    if(code == 0ULL)return 0XFF;
    unsigned char down = value > 0;
    unsigned char was_down = this->get_key(code);

    this->set_key(code, down);

    return (down && !was_down) ? this->set_key_down(code) : 0;
}

// 0xFF = POINER_ERR
unsigned char keyboard_get_key(Keyboard* keyboard, const SjenaKeyCode code){
    return (keyboard) ? keyboard->get_key(code) : POINTER_ERR;
}
// 0xFF = POINER_ERR
unsigned char keyboard_get_key_down(Keyboard* keyboard, const SjenaKeyCode code){
    return (keyboard) ? keyboard->get_key_down(code) : POINTER_ERR;
}
    
unsigned char keyboard_set_key(Keyboard* keyboard, const SjenaKeyCode code, const unsigned char state){
    return (keyboard) ? keyboard->set_key(code, state) : POINTER_ERR;
}
unsigned char keyboard_set_key_down(Keyboard* keyboard, const SjenaKeyCode code){
    return (keyboard) ? keyboard->set_key_down(code) : POINTER_ERR;
}

unsigned char keyboard_callback(Keyboard* keyboard, SjenaKeyCode code, int value){
    return (keyboard) ? keyboard->callback(code, value) : POINTER_ERR;
}

unsigned char is_modifier(SjenaKeyCode code){
    return (code & MODIFIER_KEYS) ? 1 : 0;
}





unsigned char Mouse::get(MouseEvent event){
    return (this->events & event) ? 1 : 0;
}

unsigned char Mouse::reset(unsigned char except_e){
    // Mouse
    this->acceleration = iVec2{0, 0};
    this->scroll_x = 0;
    this->scroll_y = 0;
    this->events &= except_e;
    return 0;
}

unsigned char mouse_get(Mouse* mouse, MouseEvent event){
    return (mouse) ? mouse->get(event) : POINTER_ERR;
}

unsigned char mouse_reset(Mouse* mouse, unsigned char except_e){
    return (mouse) ? mouse->reset(except_e) : POINTER_ERR;
}





// Input.reset() / will reset your getkeydown keys. Place it idealy between your Input Requests and callback/handler frame
unsigned char Input::reset(){
    // Keyboard
    this->keyboard.pressed_keys = 0ULL;

    // Remove every Mpuse Input Except Mouse held Keys
    this->mouse.acceleration = iVec2{0, 0};
    this->mouse.scroll_x = 0;
    this->mouse.scroll_y = 0;
    this->mouse.events &= SJENA_MOUSE_STATE_ALL;

    // Input
    this->header &= (SJENA_INPUT_CONFIG_BG_ALL);
    return 0;
}
unsigned char Input::full_reset(){
    // Keyboard
    this->keyboard.pressed_keys = 0ULL;
    this->keyboard.held_keys = 0ULL;

    // Mouse
    this->mouse.acceleration = iVec2{0, 0};
    this->mouse.scroll_x = 0;
    this->mouse.scroll_y = 0;
    this->mouse.events = 0;

    // Input
    this->header &= (SJENA_INPUT_CONFIG_BG_ALL);
    return 0;
}
// Don't use this
unsigned char input_callback(void* class_ptr, WINDOW_MSG_CODE msg, unsigned long long code, unsigned long long data){
    return ((Input*)class_ptr)->callback(msg, code, data);
}
unsigned char input_handler(Input* input){
    return (input) ? input->handler() : POINTER_ERR;
}
// Don't use this
unsigned char input_reset(Input* input){
    return (input) ? input->reset() : POINTER_ERR;
}
unsigned char input_full_reset(Input* input){
    return (input) ? input->full_reset() : POINTER_ERR;
}