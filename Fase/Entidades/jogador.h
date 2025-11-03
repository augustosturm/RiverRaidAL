#ifndef JOGADOR_H
#define JOGADOR_H

#include <stdbool.h>
#include "raylib.h"

typedef struct {
    Rectangle entidade;
    float velocidade;
    bool missilDisparado;
} Jogador;

typedef struct {
    Rectangle entidade;
    float velocidade;
} Missil;

/**
 * @brief Cria um jogador com posicao inicial, tamanho da hitbox e velocidade.
 *
 * @param posicao Posicao inicial do jogador.
 * @param tamanhoHitbox Tamanho da hitbox (largura x altura).
 * @param velocidade Velocidade base do jogador.
 * @return Estrutura Jogador com missilDisparado = false.
 */
Jogador criaJogador(Vector2 posicao, Vector2 tamanhoHitbox, float velocidade);

/**
 * @brief Checa colisao retangular entre jogador e inimigo.
 *
 * @param retanguloJogador Retangulo do jogador.
 * @param retanguloInimigo Retangulo do inimigo.
 * @return true se os retangulos se sobrepoem; false caso contrario.
 */
bool verificaColisaoInimigo(Rectangle retanguloJogador, Rectangle retanguloInimigo);


/**
 * @brief Cria um missil alinhado ao jogador.
 *
 * @param jogador Jogador usado como referencia de posicao.
 * @param tamanhoMissil Tamanho do missil.
 * @param velocidade Velocidade vertical do missil.
 * @return Estrutura Missil inicializada.
 */
Missil criaMissil(Jogador jogador, Vector2 tamanhoMissil, float velocidade);

/**
 * @brief Dispara um missil se nenhum estiver ativo.
 *
 * @param jogador Ponteiro para o jogador.
 * @param missil Ponteiro para o missil a ser inicializado.
 * @param tamanhoMissil Tamanho do missil.
 * @param velocidadeMissil Velocidade vertical do missil.
 * @return void
 */
void disparaMissil(Jogador *jogador, Missil *missil, Vector2 tamanhoMissil, float velocidadeMissil);

/**
 * @brief Atualiza a posicao Y do missil.
 *
 * @param jogador Ponteiro para o jogador.
 * @param missil Ponteiro para o missil ativo.
 * @param tempoDecorrido Tempo decorrido em segundos desde o ultimo quadro.
 * @return void
 */
void atualizaPosicaoMissil(Jogador *jogador, Missil *missil, float tempoDecorrido);

#endif
