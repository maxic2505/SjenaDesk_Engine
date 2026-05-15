#pragma once

enum KEYSTATE{
    NONE,
    UP,
    DOWN
};

// KEYMAP
typedef enum{
    // NUMMER

    KEYCODE_0,
    KEYCODE_1,
    KEYCODE_2,
    KEYCODE_3,
    KEYCODE_4,
    KEYCODE_5,
    KEYCODE_6,
    KEYCODE_7,
    KEYCODE_8,
    KEYCODE_9,

    // ABC

    KEYCODE_A,
    KEYCODE_B,
    KEYCODE_C,
    KEYCODE_D,
    KEYCODE_E,
    KEYCODE_F,
    KEYCODE_G,
    KEYCODE_H,
    KEYCODE_I,
    KEYCODE_J,
    KEYCODE_K,
    KEYCODE_L,
    KEYCODE_M,
    KEYCODE_N,
    KEYCODE_O,
    KEYCODE_P,
    KEYCODE_Q,
    KEYCODE_R,
    KEYCODE_S,
    KEYCODE_T,
    KEYCODE_U,
    KEYCODE_V,
    KEYCODE_W,
    KEYCODE_X,
    KEYCODE_Y,
    KEYCODE_Z,

    // SPECIAL_KEYS

    KEYCODE_ENTER,
    KEYCODE_SPACE,
    KEYCODE_BACKSPACE,
    KEYCODE_LEFT_META,
    KEYCODE_RIGHT_META,
    KEYCODE_LEFT_CTRL,
    KEYCODE_RIGHT_CTRL,
    KEYCODE_LEFT_ALT,
    KEYCODE_RIGHT_ALT,
    KEYCODE_ESC,
    KEYCODE_TAB,

    // ARROW_KEYS

    ARROW_DOWN,
    ARROW_LEFT,
    ARROW_RIGHT,
    ARROW_UP,

    // FN_KEYS

    KEYCODE_F1,
    KEYCODE_F2,
    KEYCODE_F3,
    KEYCODE_F4,
    KEYCODE_F5,
    KEYCODE_F6,
    KEYCODE_F7,
    KEYCODE_F8,
    KEYCODE_F9,

    // MOUSE
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE
} KeyCode;

typedef struct Key{
    unsigned state;
    unsigned char isPressed;
    unsigned char isConsumed;
} Key;