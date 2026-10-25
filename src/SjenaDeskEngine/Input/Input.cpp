#include "SjenaDeskEngine/Input/Input.h"

//DEVICE
unsigned char Keyboard::get_key         (const KeyCode code){return (is_pressed_keys  & code) ? 1 : 0;}
unsigned char Keyboard::get_key_consumed(const KeyCode code){return (consumed_states  & code) ? 1 : 0;}
unsigned char Keyboard::get_key_down    (const KeyCode code){return (pressed_states   & code) ? 1 : 0;}
unsigned char Keyboard::get_key_up      (const KeyCode code){return (released_states  & code) ? 1 : 0;}

unsigned char Keyboard::set_key(const KeyCode code, const unsigned char state){
    is_pressed_keys = (is_pressed_keys & ~code) | (state ? code : 0);
    return state;
}
unsigned char Keyboard::set_key_consumed(const KeyCode code, const unsigned char state){
    consumed_states = (consumed_states & ~code) | (state ? code : 0);
    return state;
}
unsigned char Keyboard::set_key_state_down(const KeyCode code){
    pressed_states |= code;
    released_states &= ~code;
    return 0;
}
unsigned char Keyboard::set_key_state_up(const KeyCode code){
    pressed_states &= ~code;
    released_states |= code;
    return 0;
}
unsigned char Keyboard::remove_state(const KeyCode code){
    pressed_states &= ~code;
    released_states &= ~code;
}

unsigned char keyboard_get_key(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->get_key(code) : 0;
}
unsigned char keyboard_get_key_consumed(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->get_key_consumed(code) : 0;
}
unsigned char keyboard_get_key_down(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->get_key_down(code) : 0;
}
unsigned char keyboard_get_key_up(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->get_key_up(code) : 0;
}

#define POINTER_ERR 0XFF
    
unsigned char keyboard_set_key(Keyboard* keyboard, const KeyCode code, const unsigned char state){
    return (keyboard) ? keyboard->set_key(code, state) : POINTER_ERR;
}
unsigned char keyboard_set_key_consumed(Keyboard* keyboard, const KeyCode code, const unsigned char state){
    return (keyboard) ? keyboard->set_key_consumed(code, state) : POINTER_ERR;
}
unsigned char keyboard_set_key_state_down(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->set_key_state_down(code) : POINTER_ERR;
}
unsigned char keyboard_set_key_state_up(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->set_key_state_up(code) : POINTER_ERR;
}
unsigned char keyboard_remove_state(Keyboard* keyboard, const KeyCode code){
    return (keyboard) ? keyboard->set_key_state_up(code) : POINTER_ERR;
}

unsigned char is_modifier(KeyCode code){
    return (code & MODIFIER_KEYS) ? 1 : 0;
}

// For APIs to set the input value
Keyboard* keyboard;
int input_key_callback(KeyCode code, int value){
    if(!keyboard)return 0; // KEYBOARD NOT SET WITH SETUP API

    if(!keyboard->get_key_consumed(code))return 0; // Value 0 => KEY NOT CONSUMED
    keyboard->set_key_consumed(code, 0);

    keyboard->set_key(code, (value > 0) ? 1 : 0);

    if(is_modifier(code)){
        switch(value){
            case 0:  
                keyboard->set_key_state_up(code);
            return 1;
            case 1:  
                keyboard->set_key_state_down(code);
            return 1;
            case 2:  
                keyboard->set_key_state_down(code);
            return 1;
            default: 
                keyboard->set_key_state_up(code);
            return -1;
        }
        return 0;
    }

    // 0 = UP
    // 1 = DOWN
    // 2 = HELD
    switch(value){
        // Turning up
        case 0:
            if(keyboard->get_key_up(code))keyboard->remove_state(code);
            else keyboard->set_key_state_up(code);
        return 2;
        // Turning Down
        case 1:
            if(keyboard->get_key_down(code))keyboard->remove_state(code);
            else keyboard->set_key_state_down(code);
        return 2;
        // Nothing is happenning
        case 2:
            keyboard->remove_state(code);
        return 2;
        default:
            keyboard->remove_state(code);
        return -2;
    }
}
void input_reset(){
    KeyCode code = (KeyCode)(1ULL<<0);
    for(int i = 0; i<KEYCODE_SIZE_IN_BITS;i++){
        // Set Consumed Because of A-Sync Platforms like Windows
        keyboard->set_key_consumed(code, 1);

        // ONE SHOT KEYS RESET
        if(!is_modifier(code))keyboard->remove_state(code);
        code = (KeyCode)((unsigned long long)code<<1);
    }
}