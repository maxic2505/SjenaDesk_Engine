#include "SjenaDeskEngine/Input/Input.h"

//DEVICE
unsigned char Keyboard::get_key         (const KeyCode code){return (is_pressed_keys  & code) ? 1 : 0;}
unsigned char Keyboard::get_key_down    (const KeyCode code){return (pressed_states   & code) ? 1 : 0;}

unsigned char Keyboard::set_key(const KeyCode code, const unsigned char state){
    is_pressed_keys = (is_pressed_keys & ~code) | (state ? code : 0);
    return state;
}
unsigned char Keyboard::set_key_state_down(const KeyCode code){
    pressed_states |= code;
    return 0;
}
unsigned char Keyboard::remove_state(const KeyCode code){
    pressed_states &= ~code;
    return 0;
}

unsigned char Keyboard::callback(KeyCode code, int value){
    printf("Keyboard.callback(): Recived\n");
    if(code == 0ULL)return 0XFF;
    printf("Keyboard.callback(): Code Available\n");
    unsigned char down = value > 0;
    unsigned char was_down = this->get_key(code);

    this->set_key(code, down);

    return (down && !was_down) ? this->set_key_state_down(code) : 0;
}

unsigned char keyboard_get_key(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->get_key(code) : 0;
}
unsigned char keyboard_get_key_down(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->get_key_down(code) : 0;
}

#define POINTER_ERR 0XFF
    
unsigned char keyboard_set_key(Keyboard* keyboard, const KeyCode code, const unsigned char state){
    return (keyboard) ? keyboard->set_key(code, state) : POINTER_ERR;
}
unsigned char keyboard_set_key_state_down(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->set_key_state_down(code) : POINTER_ERR;
}
unsigned char keyboard_remove_state(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->remove_state(code) : POINTER_ERR;
}

unsigned char keyboard_callback(Keyboard* keyboard, KeyCode code, int value){
    return (keyboard) ? keyboard->callback(code, value) : POINTER_ERR;
}

unsigned char is_modifier(KeyCode code){
    return (code & MODIFIER_KEYS) ? 1 : 0;
}

// Don't use this
unsigned char Input::reset(){
    // Keyboard
    this->keyboard.pressed_states = 0ULL;

    // Mouse
    this->mouse.acceleration = iVec2{0, 0};
    this->mouse.scroll_x = 0;
    this->mouse.scroll_y = 0;
    this->mouse.events &= (LEFT_BTN_STATE | MIDDLE_BTN_STATE | RIGHT_BTN_STATE);
    return 0;
}
// Don't use this
unsigned char input_callback(void* class_ptr, unsigned long long code, unsigned long long data){
    return ((Input*)class_ptr)->callback(code, data);
}
unsigned char input_handler(Input* input){
    return (input) ? input->handler() : POINTER_ERR;
}
// Don't use this
unsigned char input_reset(Input* input){
    return (input) ? input->reset() : POINTER_ERR;
}