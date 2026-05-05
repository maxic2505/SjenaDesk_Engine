#include "SjenaDesk_Engine.h"

// Math | sqrt | recommended accuarcy is 4 or greater
float fast_sqrt(float x, unsigned char accuarcy){
    // Newton method
    if(x < 0.1f)return 0.0f;
    float num = x;
    for(unsigned char i = 0; i<accuarcy; i++){
        num = 0.5f*(num + x / num);
    }
    return num;

    // CPU assembly methode
}