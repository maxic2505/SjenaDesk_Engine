#include "SjenaDeskEngine/Input/Input.h"

Input input = {0};

unsigned char getKey(const int keycode){ // Check if a Key is being Held
    return input.key[keycode].isPressed;
}
unsigned char getKeyDown(const int keycode){ // Check if a Key was Pressed
    return input.key[keycode].state == DOWN;
}
unsigned char getKeyUp(const int keycode){ // Check if a Key was Released
    return input.key[keycode].state == UP;
}


unsigned char is_modifier(int code){
    return ((38 < code) && (code < 45));
}

// For APIs to set the input value
int input_key_callback(int code, int value){
    if(code < 0)return 0; // -1 => KEY OUT OF RANGE

    if(!(input.key[code].isConsumed))return 0; // Value 0 => KEY NOT CONSUMED
    input.key[code].isConsumed = 0;

    input.key[code].isPressed = (value > 0);

    if(is_modifier(code)){
        switch(value){
            case 0:  input.key[code].state = UP;   return 1;
            case 1:  input.key[code].state = DOWN; return 1;
            case 2:  input.key[code].state = DOWN; return 1;
            default: input.key[code].state = UP;   return -1;
        }
        return 0;
    }

    switch(value){
        case 0:  input.key[code].state = (getKeyUp  (code)) ? 0 : 1; return 2;
        case 1:  input.key[code].state = (getKeyDown(code)) ? 0 : 2; return 2;
        case 2:  input.key[code].state = 0; return 2;
        default: input.key[code].state = 0; return -2;
    }
}
void input_reset(){
    for(int i = 0; i<KEYS_AVAILABLE;i++){
        // Set Consumed Because of non Sync Platforms like Windows
        input.key[i].isConsumed = 1;

        // ONE SHOT KEYS RESET
        if(is_modifier(i)) continue;
        input.key[i].state = 0;
    }
}