#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"

typedef struct {
    Rectangle entidade;
    float velocidade;
    int direcao;
    int minimoX;
    int maximoX;
    int morto;
} Inimigo;

/**
 * @brief Cria um inimigo com velocidade, direcao e alcance de movimento.
 *
 * @param posicao Posicao inicial.
 * @param tamanhoHitbox Tamanho da caixa de colisao.
 * @param minimoX Limite minimo no eixo X.
 * @param maximoX Limite maximo no eixo X.
 * @return Inimigo representado por um Rectangle.
 */
Inimigo criaInimigo(Vector2 posicao, Vector2 tamanhoHitbox, float velocidade, int minimoX, int maximoX);

/**
 * @brief Move um inimigo pelo eixo X.
 *
 * @param inimigo Ponteiro do inimigo.
 * @return void
 */
void moveInimigo(Inimigo *inimigo);

/**
 * @brief Troca a direcao do inimigo quando atinge o limite do movimento.
 *
 * @param inimigo Ponteiro do inimigo.
 * @return void
 */
void mudaDirecaoInimigo(Inimigo *inimigo);

#endif
