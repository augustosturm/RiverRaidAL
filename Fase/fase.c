#include <stdbool.h>
#include "raylib.h"
#include "fase.h"
#include "Entidades/jogador.h"
#include "Entidades/inimigo.h"
#include "Pontuacao/pontuacao.h"
#include "Mapa/mapa.h"

static const Rectangle SPRITE_PARADO = {102, 70, 56, 51};
static const Rectangle SPRITE_DIREITA = {161, 74, 49, 55};
static const Rectangle SPRITE_ESQUERDA = {41, 74, 49, 55};

void executaJogo(JOGADOR *jogador, MISSIL *missil, INIMIGO *inimigos, int larguraTela, int alturaTela, Texture2D textura, PONTUACAO *pontuacao) {
    const float tempoFrame = GetFrameTime();
    const float deslocamento = jogador->velocidade * tempoFrame;
    enum HitBoxJogador hitBoxJogadorArea = Parado;
    Rectangle spriteAtual = SPRITE_PARADO;

    if (IsKeyDown(KEY_SPACE)) {
        disparaMissil(jogador, missil);
    }

    atualizaPosicaoMissil(jogador, missil, tempoFrame);

    if (IsKeyDown(KEY_RIGHT)) {
        jogador->entidade.x += deslocamento;
        hitBoxJogadorArea = MovDireira;
        spriteAtual = SPRITE_DIREITA;
    } else if (IsKeyDown(KEY_LEFT)) {
        jogador->entidade.x -= deslocamento;
        hitBoxJogadorArea = MovEsquerda;
        spriteAtual = SPRITE_ESQUERDA;
    }
    
    if (IsKeyDown(KEY_UP)) jogador->entidade.y -= deslocamento;
    if (IsKeyDown(KEY_DOWN)) jogador->entidade.y += deslocamento;

    if (jogador->entidade.x < 0) 
        jogador->entidade.x = 0;
    if (jogador->entidade.y < 0) 
        jogador->entidade.y = 0;
    if (jogador->entidade.x + jogador->entidade.width > larguraTela) 
        jogador->entidade.x = larguraTela - jogador->entidade.width;
    if (jogador->entidade.y + jogador->entidade.height > alturaTela) 
        jogador->entidade.y = alturaTela - jogador->entidade.height;

    atualizaSpriteEHitboxesJogador(jogador, spriteAtual, hitBoxJogadorArea);

    for (int i = 0; i < 2; i++) {
        //MODIFICAR
        INIMIGO *inimigo = &inimigos[i];
        if (inimigo->morto) {
            continue;
        }
        //-----------------------------
        moveInimigo(inimigo, jogador->entidade.y);

        if (CheckCollisionRecs(missil->entidade, inimigo->entidade)) {
            inimigo->morto = 1;
            jogador->missilDisparado = false;
            adicionaPontos(pontuacao, inimigo->pontos);
        }

        if (verificaColisaoInimigo(jogador->hitboxes, inimigo->entidade)) {
            CloseWindow();
            return;
        }
    }

    DrawTextureRec(textura, jogador->sprite, (Vector2){ jogador->entidade.x, jogador->entidade.y }, RAYWHITE);

    if (jogador->missilDisparado) {
        desenhaMissil(*missil, textura);
    }

    for (int i = 0; i < 2; i++) {
        atualizaAnimacaoHelice(&inimigos[i], GetFrameTime());
        desenhaInimigo(inimigos[i], textura);
    }

    DrawText(TextFormat("Score: %d", pontuacao->pontos), 10, 10, 20, BLACK);

}
