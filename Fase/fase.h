#ifndef FASE_FASE_H
#define FASE_FASE_H

#include <stdbool.h>
#include "raylib.h"
#include "Entidades/jogador.h"
#include "Entidades/inimigo.h"

void executaJogo(JOGADOR *jogador, MISSIL *missil, INIMIGO *inimigos, int larguraTela, int alturaTela, Texture2D textura);

#endif
