#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include <stdbool.h>
#include "raylib.h"

enum ConjuntoTela {
    Titulo,
    MenuPrincipal,
    Jogo
};

int obtemSelecaoUsuario(bool jogando);

void desenhaTelaTitulo(void);

#endif
