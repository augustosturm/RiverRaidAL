#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "Fase/Entidades/entidade.h"
#include "Fase/Entidades/jogador.h"
#include "Fase/Entidades/inimigo.h"
#include "Fase/Entidades/gasolina.h"
#include "Fase/Pontuacao/pontuacao.h"
#include "Fase/fase.h"
#include "Menu/menuPrincipal.h"
#include "Fase/Mapa/mapa.h"
#include "Menu/MenuScore/nomeJogador.h"
#include "Menu/MenuScore/sistemaPontuacao.h"

int main(void) {
    const int larguraTela = 960;
    const int alturaTela = 800;
    int numArq = 3;  // número de mapas
    char mapa[20 * numArq][24]; // 20 linhas por mapa, 24 colunas
    Rectangle terrenos[15000];
    int numTerreno;

    Camera2D camera = {0};
    camera.target = (Vector2){0.0f, 0.0f};   // Ponto do mundo que a câmera "olha"
    camera.offset = (Vector2){0.0f, 0.0f}; // Centro da tela
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    InitAudioDevice();
    
    Music music = LoadMusicStream("eye.mp3");

    SetMusicVolume(music, 0.2f);
    PlayMusicStream(music);


    Sound tiro = LoadSound("tiro.wav");
    Sound explosion = LoadSound("explosion.wav");
    Sound morreu = LoadSound("morreu.wav");
    Sound venceu = LoadSound("winner.mp3");

    enum OpcaoMenuPrincipal opcao = 0;
    int teclaPressionada;
    enum ConjuntoTela tela = Titulo;

    Vector2 inimigosPos[50];
    int numInimigos = 0;
    Vector2 postosPos[50];
    int numPostos = 0;

    int gasolina = 100;
    int contagem = 60;

    Vector2 posicaoIni;

    leMapa(mapa, numArq, inimigosPos, &numInimigos, postosPos, &numPostos, &posicaoIni);

    const Vector2 tamanhoJogador = {56.0f, 51.0f};
    const float velocidadeJogador = 150.0f;
    const Rectangle spriteAviao = {102, 70, 56, 51};
    JOGADOR jogador = criaJogador(posicaoIni, tamanhoJogador, velocidadeJogador, spriteAviao);

    MISSIL missil;
    PONTUACAO pontuacao = {0};

    SetRandomSeed((unsigned)time(NULL));

    GASOLINA postos[numPostos];
    INIMIGO inimigos[numInimigos];

    printf("\n\n%d\n\n", numInimigos);

    for(int i = 0; i < numInimigos; i++){
        inimigos[i] = criaInimigoAleatorio(inimigosPos[i], (inimigosPos[i].x - 50), (inimigosPos[i].x + 50));
    }
    for(int i = 0; i < numPostos; i++){
        postos[i] = criaPostoGasolina(postosPos[i], (Vector2){54, 76});
    }

    InitWindow(larguraTela, alturaTela, "Teste");
    SetTargetFPS(60);

    const Texture2D textura = LoadTexture("sprites.png");

    while (!WindowShouldClose()) {
        if (tela != Jogo) {
            teclaPressionada = GetKeyPressed();
        }
   
        if (tela == Titulo) {
            desenhaTelaTitulo();
            
            avancaTelaInicio(teclaPressionada, &tela);
        } else if (tela == MenuPrincipal) {
            opcao = escolheOpcaoMenuPrincipal(teclaPressionada, opcao);

            entraTela(teclaPressionada, opcao, &tela);

            desenhaTelaMenuPrincipal(opcao);
        } else if (tela == Jogo) {

            UpdateMusicStream(music);

            if(camera.target.y >= ((numArq-1)*-800)+3)
                camera.target.y = jogador.entidade.y - alturaTela + 150;

            BeginDrawing();
            BeginMode2D(camera);

            desenhaMapa(mapa, numArq, terrenos, &numTerreno);
            executaJogo(&jogador, &missil, inimigos, larguraTela, alturaTela, textura, &pontuacao, numArq, terrenos, numTerreno, numInimigos, postos, numPostos, &gasolina, &tela, tiro, explosion, morreu, venceu);
            
            EndMode2D();

            gasolina = consomeGasolina(gasolina, &contagem);
            
            DrawRectangle(0, 750, 960, 50, GRAY);
            DrawText(TextFormat("Score: %d", pontuacao.pontos), 10, 770, 20, BLACK);
            DrawText(TextFormat("Gasolina: %d/100", gasolina), 150, 770, 20, BLACK);

            EndDrawing();
        } else if (tela == JogadoresPontos) {
            if (teclaPressionada == KEY_ENTER) {
                tela = MenuPrincipal;
            }

            BeginDrawing();
            ClearBackground(BLUE);

            JogadorPontos ranking[MAXRANKING] = {0};
            int totalJogadores = leRanking(ranking, MAXRANKING);

            if (totalJogadores < 0) {
                tela = MenuPrincipal;
            } else {
                if (totalJogadores > 0) {
                    ordenaRankingPorPontuacao(ranking, totalJogadores);
                    imprimeRankingJogadores(ranking, totalJogadores);

                    DrawText("Pressione ENTER para voltar ao menu.", 20, 740, 30, YELLOW);
                } else {
                    DrawText("Nenhum jogador com pontuação salva.", 20, 40, 30, YELLOW);
                }
            }

            EndDrawing();

        } else if (tela == Morte) {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("MORREU", 270, 300, 100, RED);
            DrawText("Para sair, pressione esc!", 270, 400, 20, RED);
            DrawText(TextFormat("Score final: %d", pontuacao.pontos), 10, 770, 20, RED);
            //Salva progresso aqui
            EndDrawing();

        } else if (tela == endGame) {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("PARABÉNS, CHEGOU AO FINAL", 10, 300, 60, BLUE);
            DrawText("Para sair, pressione esc!", 10, 360, 20, BLUE);
            DrawText(TextFormat("Score final: %d", pontuacao.pontos), 10, 770, 20, BLUE);
            //Salva progresso aqui
            EndDrawing();


        } else if (tela == Saida) {
            UnloadSound(tiro);
            UnloadSound(explosion);
            UnloadSound(morreu);
            UnloadSound(venceu);
            CloseAudioDevice();
            CloseWindow();
            return 0;
        }
    }

    UnloadSound(tiro);
    UnloadSound(explosion);
    UnloadSound(morreu);
    UnloadSound(venceu);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
