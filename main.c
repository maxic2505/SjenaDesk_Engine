#include <stdio.h>

#include "Engine/Graphics/SjenaDesk_Graphics.h"
#include "Engine/Input/SjenaDesk_Input.h"
#include "Engine/SjenaDesk_Engine.h"
#include "Engine/SjenaDesk_Components.h"
#include "Engine/Math/SjenaDesk_Vector.h"

int main(){
    unsigned char test[5];

    Window main_window = { 0 };
    Object text_obj;

    test[0] = graphic_register_window(&main_window, "MainWindow");
    test[1] = graphic_create_window(&main_window, "User", WS_EX_OVERLAPPEDWINDOW | WS_EX_LAYERED, 0, 0, 1000, 1000);
   
    test[2] = graphic_create_text(&text_obj, &main_window, (uVec2) { 25, 25 }, (uVec2) { 50, 25 }, & (Text) { 0, 10, 10, 0, (Color) { 0, 0, 0, 255 }, NULL }, "HELLO WORLD");

    printf("| Data: %s\n", ((Text*)text_obj.data)->data);

    test[3] = graphic_destroy_object(&text_obj);
    test[4] = graphic_destroy_window(&main_window);

    for (int i = 0; i < 5; i++) {
        printf("Test[%d] : %d\n", i, test[i]);
    }

    return 0;
}