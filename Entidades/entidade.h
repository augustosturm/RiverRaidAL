#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "raylib.h"

/**
 * @brief Cria um retangulo a partir da posicao e tamanho da hitbox.
 *
 * @param posicao Posicao inicial.
 * @param tamanhoHitbox Tamanho da hitbox.
 * @return Retangulo com a posicao e tamanho informados.
 */
Rectangle criaEntidade(Vector2 posicao, Vector2 tamanhoHitbox);

#endif
