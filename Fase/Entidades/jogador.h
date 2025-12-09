#ifndef JOGADOR_H
#define JOGADOR_H

#include <stdbool.h>
#include "raylib.h"

#define NUMHITBOX 2

typedef struct {
    Rectangle entidade;
    float velocidade;
    bool missilDisparado;
    Rectangle sprite;
    Rectangle hitboxes[NUMHITBOX];
} JOGADOR;

typedef struct {
    Rectangle entidade;
    float velocidade;
    Rectangle sprite;
} MISSIL;

enum HitBoxJogador {
    Parado,
    MovDireira,
    MovEsquerda
};

/**
 * @brief Cria um jogador com posicao inicial, tamanho da hitbox e velocidade.
 *
 * @param posicao Posicao inicial do jogador.
 * @param tamanhoHitbox Tamanho da hitbox (largura x altura).
 * @param velocidade Velocidade base do jogador.
 * @param sprite Recorte inicial da textura da nave.
 * @return Estrutura JOGADOR com missilDisparado = false.
 */
JOGADOR criaJogador(Vector2 posicao, Vector2 tamanhoHitbox, float velocidade, Rectangle sprite);

/**
 * @brief Aplica sprite e hitboxes condizentes com o estado atual do jogador.
 *
 * @param jogador Jogador a ser atualizado.
 * @param sprite Novo recorte da textura.
 * @param hitboxEstado Enum que indica qual conjunto de hitboxes deve ser usado.
 */
void atualizaSpriteEHitboxesJogador(JOGADOR *jogador, Rectangle sprite, enum HitBoxJogador hitboxEstado);

/**
 * @brief Calcula a hitbox superior do jogador conforme o estado da animação.
 *
 * @param entidadeJogador Retângulo base atual do jogador (posição e tamanho).
 * @param hitBoxAtualParams Enum que indica se o jogador está parado, indo para a direita ou esquerda.
 * @return Rectangle correspondente à porção frontal (topo) do avião já ajustada para esse estado.
 */
Rectangle atualizaHitboxSuperiorJogador(Rectangle entidadeJogador, enum HitBoxJogador hitBoxAtualParams);

/**
 * @brief Calcula a hitbox inferior do jogador conforme o estado da animação.
 *
 * @param entidadeJogador Retângulo base atual do jogador (posição e tamanho).
 * @param hitBoxAtualParams Enum que indica se o jogador está parado, indo para a direita ou esquerda.
 * @return Rectangle correspondente à porção traseira (corpo/asa) do avião já ajustada para esse estado.
 */
Rectangle atualizaHitboxInferiorJogador(Rectangle entidadeJogador, enum HitBoxJogador hitBoxAtualParams);

/**
 * @brief Checa colisao entre jogador e inimigo usando as duas hitboxes pre-ajustadas.
 *
 * @param hitboxesJogador Vetor com as hitboxes superior e inferior calculadas para o jogador.
 * @param entidadeInimigo Retangulo atual do inimigo.
 * @return true se qualquer hitbox do jogador intersectar o inimigo.
 */
bool verificaColisaoInimigo(Rectangle hitboxesJogador[], Rectangle entidadeInimigo);


/**
 * @brief Cria um missil alinhado ao jogador.
 *
 * @param jogador Jogador usado como referencia de posicao.
 * @param tamanhoMissil Tamanho do missil.
 * @param velocidade Velocidade vertical do missil.
 * @param sprite Posicao da textura que tem o sprite do missil 
 * @return Estrutura MISSIL inicializada.
 */
MISSIL criaMissil(JOGADOR jogador, Vector2 tamanhoMissil, float velocidade, Rectangle sprite);

/**
 * @brief Dispara um missil se nenhum estiver ativo.
 *
 * @param jogador Ponteiro para o jogador.
 * @param missil Ponteiro para o missil a ser inicializado.
 * @return void
 */
void disparaMissil(JOGADOR *jogador, MISSIL *missil);

/**
 * @brief Atualiza a posicao Y do missil.
 *
 * @param jogador Ponteiro para o jogador.
 * @param missil Ponteiro para o missil ativo.
 * @param tempoDecorrido Tempo decorrido em segundos desde o ultimo quadro.
 * @return void
 */
void atualizaPosicaoMissil(JOGADOR *jogador, MISSIL *missil, float tempoDecorrido);

/**
 * @brief Desenha o missil usando os dados atuais de transformacao.
 *
 * @param missil Estrutura que contem o retangulo e o sprite do missil.
 * @param textura Textura carregada que possui o sprite do missil.
 * @return void
 */
void desenhaMissil(MISSIL missil, Texture2D textura);

/**
 * @brief Desenha o jogador e suas hitboxes usando a textura informada.
 *
 * @param jogador Ponteiro constante para o jogador com sprite atualizado.
 * @param textura Textura carregada que contém o sprite do jogador.
 */
void desenhaJogador(const JOGADOR *jogador, Texture2D textura);

#endif
