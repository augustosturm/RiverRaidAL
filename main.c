#include <stdbool.h>
#include "raylib.h"
#include "Fase/Entidades/entidade.h"
#include "Fase/Entidades/jogador.h"
#include "Fase/Entidades/inimigo.h"
#include "Fase/fase.h"
#include "Menu/menuPrincipal.h"
#include "Fase/Mapa/mapa.h"


int main(void) {
    const int larguraTela = 960;
    const int alturaTela = 800;
    int numArq = 2;  // número de mapas
    char mapa[20 * numArq][24]; // 20 linhas por mapa, 24 colunas
    
    enum OpcaoMenuPrincipal opcao = 0;
    int teclaPressionada;
    enum ConjuntoTela tela = Titulo;

    const Vector2 tamanhoJogador = {20.0f, 20.0f};
    const Vector2 posicaoInicialJogador = {larguraTela / 2.0f - tamanhoJogador.x / 2.0f, alturaTela - tamanhoJogador.y * 2.0f};
    const float velocidadeJogador = 200.0f;
    Jogador jogador = criaJogador(posicaoInicialJogador, tamanhoJogador, velocidadeJogador);

    leMapa(mapa, numArq);

    // const Vector2 tamanhoMissil = {5.0f, 5.0f};
    // const float velocidadeMissil = 400.0f;
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
            
            avancaTelaInicio(teclaPressionada, &tela);
        } else if (tela == MenuPrincipal) {
            opcao = escolheOpcaoMenuPrincipal(teclaPressionada, opcao);

            entraTela(teclaPressionada, opcao, &tela);

            desenhaTelaMenuPrincipal(opcao);
        } else if (tela == Jogo) {
            BeginDrawing();
            desenhaMapa(mapa, numArq);
            executaJogo(&jogador, &missil, inimigos, larguraTela, alturaTela);
            EndDrawing();
        } else if (tela == Saida) {
            CloseWindow();
            return 0;
        }
    }

    CloseWindow();
    return 0;
}
