#include <stdbool.h>
#include "mainMenu.h"


int getUserSelection(bool playing) {
    int keyPressed;
    
    if (!playing) {
        keyPressed = GetKeyPressed();
    } else {
        keyPressed = 0;
    }

    return keyPressed;
}

void drawTitleScreen() {
    BeginDrawing();
    ClearBackground(BLUE);
    DrawText("RiverRaid AL Edition +", 100, 100, 50, YELLOW);
    EndDrawing();
}