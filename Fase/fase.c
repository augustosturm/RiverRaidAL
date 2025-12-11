#include <stdbool.h>
#include "raylib.h"
#include "fase.h"
#include "Menu/menuPrincipal.h"
#include "Entidades/jogador.h"
#include "Entidades/inimigo.h"
#include "Entidades/gasolina.h"
#include "Pontuacao/pontuacao.h"
#include "Mapa/mapa.h"

static const Rectangle SPRITE_PARADO = {102, 71, 56, 51};
static const Rectangle SPRITE_DIREITA = {161, 74, 49, 55};
static const Rectangle SPRITE_ESQUERDA = {41, 74, 49, 55};

void executaJogo(JOGADOR *jogador, MISSIL *missil, INIMIGO *inimigos, int larguraTela, int alturaTela, Texture2D textura, PONTUACAO *pontuacao, int numArq, Rectangle Terrenos[], int numTerreno, int numInimigos, GASOLINA postos[], int numPostos, int *gasolina, enum ConjuntoTela *tela, Sound tiro, Sound explosion, Sound morreu, Sound venceu) {
    const float tempoFrame = GetFrameTime();
    const float deslocamento = jogador->velocidade * tempoFrame;
    enum HitBoxJogador hitBoxJogadorArea = Parado;
    Rectangle spriteAtual = SPRITE_PARADO;

    if(jogador->entidade.y <= ((numArq-1)*(-800))+1){
        adicionaPontos(pontuacao, 100);
        PlaySound(venceu);
        *tela = endGame;
    }

    if (IsKeyDown(KEY_SPACE)) {
        disparaMissil(jogador, missil, tiro);
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
    jogador->entidade.y -= deslocamento;

    if (IsKeyDown(KEY_UP)) jogador->entidade.y -= deslocamento*0.5;
    if (IsKeyDown(KEY_DOWN)) jogador->entidade.y += deslocamento*0.5;

    if (jogador->entidade.x < 0) 
        jogador->entidade.x = 0;
    if (jogador->entidade.y < ((numArq-1)*-800)) 
        jogador->entidade.y = ((numArq-1)*-800);
    if (jogador->entidade.x + jogador->entidade.width > larguraTela) 
        jogador->entidade.x = larguraTela - jogador->entidade.width;
    if (jogador->entidade.y + jogador->entidade.height > alturaTela) 
        jogador->entidade.y = alturaTela - jogador->entidade.height;

    atualizaSpriteEHitboxesJogador(jogador, spriteAtual, hitBoxJogadorArea);

    for (int i = 0; i < numInimigos; i++) {
        //MODIFICAR
        INIMIGO *inimigo = &inimigos[i];
        if (inimigo->morto) {
            continue;
        }
        //-----------------------------
        moveInimigo(inimigo, jogador->entidade.y);

        if (CheckCollisionRecs(missil->entidade, inimigo->entidade)) {
            PlaySound(explosion); 
            inimigo->morto = 1;
            jogador->missilDisparado = false;
            adicionaPontos(pontuacao, inimigo->pontos);
        }

        if (verificaColisaoInimigo(jogador->hitboxes, inimigo->entidade)) {
            *tela = Morte;
            PlaySound(morreu);
            //CloseWindow();
            return;
        }
    }

    for (int i = 0; i < numPostos; i++) {
        //MODIFICAR
        GASOLINA *posto = &postos[i];
        if (posto->morto) {
            continue;
        }

        if (CheckCollisionRecs(missil->entidade, posto->entidade)) {
            PlaySound(explosion);
            posto->morto = 1;
            jogador->missilDisparado = false;
            adicionaPontos(pontuacao, posto->pontos);
        }

        if (verificaColisaoPosto(jogador->hitboxes, posto->entidade)) {
            *gasolina = 100;
        }
    }

    if (*gasolina <= 0) {
        *tela = Morte;
        PlaySound(morreu);
        //CloseWindow();
        return;
    }

    if (verificaColisaoTerreno(jogador->hitboxes, Terrenos, numTerreno)) {
        *tela = Morte;
        PlaySound(morreu);
        //CloseWindow();
        return;
    }

    for (int i = 0; i < numPostos; i++) {
        desenhaPosto(postos[i], textura);
    }

    desenhaJogador(jogador, textura);

    if (jogador->missilDisparado) {
        desenhaMissil(*missil, textura);
    }

    for (int i = 0; i < numInimigos; i++) {
        atualizaAnimacaoHelice(&inimigos[i]);
        desenhaInimigo(inimigos[i], textura);
    }
}