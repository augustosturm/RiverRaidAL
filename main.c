#include <stdbool.h>
#include "raylib.h"
#include "Fase/Entidades/entidade.h"
#include "Fase/Entidades/jogador.h"
#include "Fase/Entidades/inimigo.h"
#include "Fase/fase.h"
#include "Menu/menuPrincipal.h"

int main(void) {
    const int larguraTela = 800;
    const int alturaTela = 450;
    
    enum OpcaoMenuPrincipal opcao = 0;
    int teclaPressionada;
    enum ConjuntoTela tela = Titulo;

    const Vector2 tamanhoJogador = {56.0f, 51.0f};
    const Vector2 posicaoInicialJogador = {larguraTela / 2.0f - tamanhoJogador.x / 2.0f, alturaTela - tamanhoJogador.y * 2.0f};
    const float velocidadeJogador = 200.0f;
    const Rectangle spriteAviao = {102, 70, 56, 51};
    JOGADOR jogador = criaJogador(posicaoInicialJogador, tamanhoJogador, velocidadeJogador, spriteAviao);

    MISSIL missil;

    const Vector2 tamanhoInimigo = {20.0f, 20.0f};
    INIMIGO inimigos[2];
    inimigos[0] = criaNavio((Vector2){400.0f, 100.0f}, 350, 500);
    inimigos[1] = criaHelicoptero((Vector2){200.0f, 200.0f}, 150, 350);
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
            executaJogo(&jogador, &missil, inimigos, larguraTela, alturaTela, textura);
        } else if (tela == Saida) {
            CloseWindow();
            return 0;
        }
    }

    CloseWindow();
    return 0;
}
