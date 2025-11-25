#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"
#include <stdbool.h>
#define DIFPOS 200

typedef struct {
    Rectangle entidade;
    float velocidade;
    int direcao;
    int minimoX;
    int maximoX;
    int morto;
    int movendo;
    Rectangle sprite;
    int pontos;
} INIMIGO;

/**
 * @brief Cria um helicoptero inimigo com sprite e limites horizontais definidos.
 *
 * @param posicao Posicao inicial no mapa.
 * @param minimoX Limite minimo que o helicoptero pode alcançar no eixo X.
 * @param maximoX Limite maximo que o helicoptero pode alcançar no eixo X.
 * @return Estrutura INIMIGO pronta para ser atualizada e desenhada.
 */
INIMIGO criaHelicoptero(Vector2 posicao, int minimoX, int maximoX);

/**
 * @brief Cria um navio inimigo configurado com hitbox e sprite especificos.
 *
 * @param posicao Posicao inicial do navio no mapa.
 * @param minimoX Limite inferior do movimento horizontal permitido.
 * @param maximoX Limite superior do movimento horizontal permitido.
 * @return Estrutura INIMIGO representando o navio.
 */
INIMIGO criaNavio(Vector2 posicao, int minimoX, int maximoX);

/**
 * @brief Escolhe aleatoriamente criar um navio ou helicoptero com os valores padrao.
 *
 * @return Estrutura INIMIGO representando o tipo sorteado.
 */
INIMIGO criaInimigoAleatorio(Vector2 posicao, int minimoX, int maximoX);

/**
 * @brief Cria um inimigo com velocidade, direcao e alcance de movimento.
 *
 * @param posicao Posicao inicial.
 * @param tamanhoHitbox Tamanho da caixa de colisao.
 * @param minimoX Limite minimo no eixo X.
 * @param maximoX Limite maximo no eixo X.
 * @param pontos Quantidade de pontos que o inimigo vale.
 * @return INIMIGO representado por um Rectangle.
 */
INIMIGO criaInimigo(Vector2 posicao, Vector2 tamanhoHitbox, float velocidade, int minimoX, int maximoX, Rectangle sprite, int pontos);

/**
 * @brief Escolhe aleatoriamente se o inimigo inicia movendo para a esquerda ou direita.
 *
 * @return -1 para esquerda e 1 para direita.
 */
int geraDirecaoInicial(void);

/**
 * @brief Inicia o movimento quando o jogador se aproxima e atualiza o deslocamento horizontal.
 *
 * @param inimigo Ponteiro do inimigo.
 * @param jogadorPosicaoY Posicao Y atual do jogador usada para ativar o inimigo.
 * @return void
 */
void moveInimigo(INIMIGO *inimigo, int jogadorPosicaoY);

/**
 * @brief Atualiza a posicao horizontal do inimigo quando ele esta em movimento.
 *
 * @param inimigo Ponteiro do inimigo.
 * @return void
 */
void atualizaPosicaoInimigo(INIMIGO *inimigo);

/**
 * @brief Troca a direcao do inimigo quando atinge o limite do movimento.
 *
 * @param inimigo Ponteiro do inimigo.
 * @return void
 */
void mudaDirecaoInimigo(INIMIGO *inimigo);

/**
 * @brief Verifica se o jogador esta dentro da distancia de ativacao do inimigo.
 *
 * @param inimigo Ponteiro do inimigo.
 * @param jogadorPosicaoY Posicao Y atual do jogador.
 * @return true se o jogador esta proximo, false caso contrario.
 */
bool verificaJogadorProximo(INIMIGO *inimigo, int jogadorPosicaoY);

/**
 * @brief Desenha o inimigo usando a textura e o sprite configurados.
 *
 * @param inimigo Estrutura contendo posicao e sprite atuais.
 * @param textura Spritesheet onde o sprite do inimigo esta localizado.
 */
void desenhaInimigo(INIMIGO inimigo, Texture2D textura);

/**
 * @brief Alterna o sprite da helice para simular a animacao do helicoptero.
 *
 * @param inimigo Ponteiro do inimigo que tera o sprite atualizado.
 * @param delta Tempo (em segundos) decorrido desde o ultimo frame.
 */
void atualizaAnimacaoHelice(INIMIGO *inimigo, float delta);

#endif
