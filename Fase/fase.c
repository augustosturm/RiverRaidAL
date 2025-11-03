#include <stdbool.h>
#include "raylib.h"
#include "fase.h"
#include "Entidades/jogador.h"
#include "Entidades/inimigo.h"

void executaJogo(Jogador *jogador, Missil *missil, Inimigo *inimigos, int larguraTela, int alturaTela) {
    const float tempoFrame = GetFrameTime();

    if (IsKeyDown(KEY_SPACE)) {
        disparaMissil(jogador, missil, (Vector2) {5.0f, 5.0f}, 400.0f);
    }

    atualizaPosicaoMissil(jogador, missil, tempoFrame);

    if (IsKeyDown(KEY_RIGHT)) jogador->entidade.x += jogador->velocidade * tempoFrame;
    if (IsKeyDown(KEY_LEFT)) jogador->entidade.x -= jogador->velocidade * tempoFrame;
    if (IsKeyDown(KEY_UP)) jogador->entidade.y -= jogador->velocidade * tempoFrame;
    if (IsKeyDown(KEY_DOWN)) jogador->entidade.y += jogador->velocidade * tempoFrame;

    if (jogador->entidade.x < 0) 
        jogador->entidade.x = 0;
    if (jogador->entidade.y < 0) 
        jogador->entidade.y = 0;
    if (jogador->entidade.x + jogador->entidade.width > larguraTela) 
        jogador->entidade.x = larguraTela - jogador->entidade.width;
    if (jogador->entidade.y + jogador->entidade.height > alturaTela) 
        jogador->entidade.y = alturaTela - jogador->entidade.height;

    for (int i = 0; i < 2; i++) {
        //MODIFICAR
        Inimigo *inimigo = &inimigos[i];
        if (inimigo->morto) {
            continue;
        }
        //-----------------------------
        moveInimigo(inimigo);

        if (CheckCollisionRecs(missil->entidade, inimigo->entidade)) {
            inimigo->morto = 1;
            jogador->missilDisparado = false;
        }

        if (verificaColisaoInimigo(jogador->entidade, inimigo->entidade)) {
            CloseWindow();
            return;
        }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangleRec(jogador->entidade, RED);

    if (jogador->missilDisparado) {
        DrawRectangleRec(missil->entidade, GREEN);
    }

    for (int i = 0; i < 2; i++) {
        if (!inimigos[i].morto) {
            DrawRectangleRec(inimigos[i].entidade, BLUE);
        }
    }

    EndDrawing();
}
