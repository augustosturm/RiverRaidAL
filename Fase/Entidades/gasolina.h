#ifndef GASOLINA_H
#define GASOLINA_H

#include "raylib.h"
#include <stdbool.h>

typedef struct {
    Rectangle entidade;
    int morto;
    Rectangle sprite;
    int pontos;
} GASOLINA;

GASOLINA criaPostoGasolina(Vector2 posicao, Vector2 tamanhoHitbox);

void desenhaPosto(GASOLINA posto, Texture2D textura);

int consomeGasolina(int gasolina, int *contagem);

#endif