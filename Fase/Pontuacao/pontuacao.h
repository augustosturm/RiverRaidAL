#ifndef PONTUACAO_H
#define PONTUACAO_H

#include "raylib.h"

typedef struct {
    char nomeJogador[10];
    int pontos;
} PONTUACAO;

/**
 * @brief Incrementa a pontuacao atual com os pontos recebidos.
 *
 * @param pontuacao Estrutura de pontuacao que sera atualizada.
 * @param pontosRecebidos Quantidade de pontos conquistada.
 */
void adicionaPontos(PONTUACAO *pontuacao, int pontosRecebidos);

/**
 * @brief Aplica a penalidade de morte sem deixar a pontuacao negativa.
 *
 * @param pontuacao Estrutura de pontuacao que sofrera a penalidade.
 */
void perdePontosMorte(PONTUACAO *pontuacao);

#endif
