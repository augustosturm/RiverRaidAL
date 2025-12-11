#include "Menu/menuPrincipal.h"

int obtemSelecaoUsuario(bool jogando) {
    int teclaPressionada;
    
    if (!jogando) {
        teclaPressionada = GetKeyPressed();
    } else {
        teclaPressionada = 0;
    }

    return teclaPressionada;
}

void desenhaTelaTitulo(void) {
    BeginDrawing();
    ClearBackground(BLUE);
    DrawText("RiverRaid AL Edicao +", 100, 100, 50, YELLOW);
    DrawText("Ver. Alpha 1.1.1.1.1", 100, 160, 30, YELLOW);
    DrawText("Pressione ENTER para jogar", 100, 210, 25, YELLOW);
    EndDrawing();
}

void avancaTelaInicio(int teclaPressionada, enum ConjuntoTela *tela) {
    if (teclaPressionada == KEY_ENTER) {
        *tela = MenuPrincipal;
    }
}

enum OpcaoMenuPrincipal escolheOpcaoMenuPrincipal(int teclaPressionada, enum OpcaoMenuPrincipal opcao) {
    if (teclaPressionada == KEY_DOWN && opcao < Sair) {
        opcao++;
    }
    if (teclaPressionada == KEY_UP && opcao > NovoJogo) {
        opcao--;
    }

    return opcao;
}

void entraTela(int teclaPressionada, enum OpcaoMenuPrincipal opcao, enum ConjuntoTela *tela) {
    if (teclaPressionada == KEY_ENTER && opcao == NovoJogo) {
        *tela = NomeJogador;
    }

    if (teclaPressionada == KEY_ENTER && opcao == Sair) {
        *tela = Saida;
    }

    if (teclaPressionada == KEY_ENTER && opcao == Ranking) {
        *tela = JogadoresPontos;
    }
}

void desenhaTelaMenuPrincipal(enum OpcaoMenuPrincipal opcao) {
    BeginDrawing();
    ClearBackground(BLUE);
    DrawText("Novo jogo", 100, 150, 50, YELLOW);
    DrawText("Carregar jogo", 100, 200, 50, YELLOW);
    DrawText("Ranking", 100, 250, 50, YELLOW);
    DrawText("Sair", 100, 300, 50, YELLOW);

    switch (opcao) {
    case NovoJogo:
        DrawRectangle(50, 170, 10, 10, YELLOW);
        break;
    case CarregarJogo:
        DrawRectangle(50, 220, 10, 10, YELLOW);
        break;
    case Ranking:
        DrawRectangle(50, 270, 10, 10, YELLOW);
        break;
    case Sair:
        DrawRectangle(50, 320, 10, 10, YELLOW);
        break;
    default:
        break;
    }

    EndDrawing();
}

