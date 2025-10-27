#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <stdbool.h>
#include "raylib.h"

enum ScreenSet {
    Title,
    MainMenu,
    Game
};

int getUserSelection(bool playing);

void drawTitleScreen();

#endif
