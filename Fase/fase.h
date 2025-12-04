#ifndef FASE_FASE_H
#define FASE_FASE_H

#include <stdbool.h>
#include "raylib.h"
#include "Entidades/jogador.h"
#include "Entidades/inimigo.h"
#include "Pontuacao/pontuacao.h"

/**
 * @brief Executa um ciclo completo da fase, tratando entrada, atualização e renderização.
 *
 * Processa o input do jogador, move o míssil e os inimigos, ajusta sprites/hitboxes,
 * verifica colisões e desenha todos os elementos do quadro atual.
 *
 * @param jogador Ponteiro para a entidade do jogador que será atualizada e desenhada.
 * @param missil Ponteiro para o míssil associado ao jogador (disparo, movimento e colisão).
 * @param inimigos Vetor de inimigos ativos que serão movimentados, testados e desenhados.
 * @param larguraTela Limite horizontal usado para restringir o movimento do jogador.
 * @param alturaTela Limite vertical usado para restringir o movimento do jogador.
 * @param textura Spritesheet usada para renderizar o jogador com o recorte correto.
 * @param pontuacao Estrutura que acumula os pontos ganhos ao destruir inimigos.
 */
void executaJogo(JOGADOR *jogador, MISSIL *missil, INIMIGO *inimigos, int larguraTela, int alturaTela, Texture2D textura, PONTUACAO *pontuacao, int numArq);

#endif
