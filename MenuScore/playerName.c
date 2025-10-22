#include "raylib.h"
#include "playerName.h"
#include <ctype.h> 

void putPlayerName(int lenName, int *pos, char *playerName) {
    int key = GetCharPressed();
    int posLocal = *pos;

    if (key >= 32 && key <= 125 && posLocal < lenName) {
        playerName[posLocal] = toupper((char)key);
        posLocal++;
        playerName[posLocal] = '\0';
    }

    if (IsKeyPressed(KEY_BACKSPACE) && posLocal > 0) {
        posLocal--;
        playerName[posLocal] = '\0';
    }

    *pos = posLocal;
}

void printPlayerName(char playerName[]) {
    //Só teste
    //Quando fizer a tela de score, vai ter que mudar aqui
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(playerName, 20, 70, 30, BLACK);
    EndDrawing();
}
