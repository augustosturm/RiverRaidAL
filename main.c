#include <stdbool.h>
#include "raylib.h"
#include "Entidades/entidade.h"
#include "Entidades/jogador.h"
#include "Entidades/inimigo.h"
#include "Menu/menuPrincipal.h"


int main(void) {
    const int larguraTela = 800;
    const int alturaTela = 450;
    
    int opcao = 1;
    int teclaPressionada;
    enum ConjuntoTela tela = Titulo;

    //-------------------------------------------------------------------------
    const Vector2 tamanhoJogador = {20.0f, 20.0f};
    const Vector2 posicaoInicialJogador = {larguraTela / 2.0f - tamanhoJogador.x / 2.0f, alturaTela - tamanhoJogador.y * 2.0f};
    const float velocidadeJogador = 200.0f;
    Jogador jogador = criaJogador(posicaoInicialJogador, tamanhoJogador, velocidadeJogador);
    //-------------------------------------------------------------------------
    const Vector2 tamanhoMissil = {5.0f, 5.0f};
    const float velocidadeMissil = 400.0f;
    Missil missil;

    const Vector2 tamanhoInimigo = {20.0f, 20.0f};
    Inimigo inimigos[2];
    inimigos[0] = criaInimigo((Vector2){400.0f, 100.0f}, tamanhoInimigo, 100.0f, 350, 500);
    inimigos[1] = criaInimigo((Vector2){200.0f, 200.0f}, tamanhoInimigo, 150.0f, 150, 350);

    InitWindow(larguraTela, alturaTela, "Teste");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (tela != Jogo) {
            teclaPressionada = GetKeyPressed();
        }
   
        if (tela == Titulo) {
            desenhaTelaTitulo();
            
            if (teclaPressionada == KEY_ENTER) {
                tela = MenuPrincipal;
            }
        } else if (tela == MenuPrincipal) {
            if (teclaPressionada == KEY_DOWN && opcao < 4) {
                opcao++;
            }
            if (teclaPressionada == KEY_UP && opcao > 1) {
                opcao--;
            }

            if (teclaPressionada == KEY_ENTER && opcao == 1) {
                tela = Jogo;
            }

            if (teclaPressionada == KEY_ENTER && opcao == 4) {
                CloseWindow();
                return 0;
            }
            
            BeginDrawing();
            ClearBackground(BLUE);
            DrawText("Novo jogo", 100, 150, 50, YELLOW);
            DrawText("Carregar jogo", 100, 200, 50, YELLOW);
            DrawText("Ranking", 100, 250, 50, YELLOW);
            DrawText("Sair", 100, 300, 50, YELLOW);

            switch (opcao)
            {
                case 1:
                    DrawRectangle(50, 170, 10, 10, YELLOW);
                    break;
                case 2:
                    DrawRectangle(50, 220, 10, 10, YELLOW);
                    break;
                case 3:
                    DrawRectangle(50, 270, 10, 10, YELLOW);
                    break;
                case 4:
                    DrawRectangle(50, 320, 10, 10, YELLOW);
                    break;
                default:
                    break;
            }


            EndDrawing();
        } else if (tela == Jogo) {
            const float tempoFrame = GetFrameTime();

            if (IsKeyDown(KEY_SPACE)) {
                disparaMissil(&jogador, &missil, tamanhoMissil, velocidadeMissil);
            }

            atualizaPosicaoMissil(&jogador, &missil, tempoFrame);

            if (IsKeyDown(KEY_RIGHT)) jogador.entidade.x += jogador.velocidade * tempoFrame;
            if (IsKeyDown(KEY_LEFT)) jogador.entidade.x -= jogador.velocidade * tempoFrame;
            if (IsKeyDown(KEY_UP)) jogador.entidade.y -= jogador.velocidade * tempoFrame;
            if (IsKeyDown(KEY_DOWN)) jogador.entidade.y += jogador.velocidade * tempoFrame;

            if (jogador.entidade.x < 0) jogador.entidade.x = 0;
            if (jogador.entidade.y < 0) jogador.entidade.y = 0;
            if (jogador.entidade.x + jogador.entidade.width > larguraTela) jogador.entidade.x = larguraTela - jogador.entidade.width;
            if (jogador.entidade.y + jogador.entidade.height > alturaTela) jogador.entidade.y = alturaTela - jogador.entidade.height;

            for (int i = 0; i < 2; i++) {
                //MODIFICAR
                Inimigo *inimigo = &inimigos[i];
                if (inimigo->morto) {
                    continue;
                }
                //---------
                moveInimigo(inimigo);

                if (CheckCollisionRecs(missil.entidade, inimigo->entidade)) {
                    inimigo->morto = 1;
                    jogador.missilDisparado = false;
                }

                if (verificaColisaoInimigo(jogador.entidade, inimigo->entidade)) {
                    CloseWindow();
                    return 0;
                }
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangleRec(jogador.entidade, RED);

            if (jogador.missilDisparado) {
                DrawRectangleRec(missil.entidade, GREEN);
            }

            for (int i = 0; i < 2; i++) {
                if (!inimigos[i].morto) {
                    DrawRectangleRec(inimigos[i].entidade, BLUE);
                }
            }

            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}
