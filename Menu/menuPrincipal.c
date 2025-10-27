#include <stdbool.h>
#include "menuPrincipal.h"


int obtemSelecaoUsuario(bool jogando) {
    int teclaPressionada;
    
    if (!jogando) {
        teclaPressionada = GetKeyPressed();
    } else {
        teclaPressionada = 0;
    }

    return teclaPressionada;
}

void desenhaTelaTitulo(void) {
    BeginDrawing();
    ClearBackground(BLUE);
    DrawText("RiverRaid AL Edicao +", 100, 100, 50, YELLOW);
    EndDrawing();
}
