#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include <stdbool.h>
#include "raylib.h"

enum ConjuntoTela {
    Titulo,
    MenuPrincipal,
    Jogo,
    Saida,
    JogadoresPontos
};

enum OpcaoMenuPrincipal {
    NovoJogo,
    CarregarJogo,
    Ranking,
    Sair
};

int obtemSelecaoUsuario(bool jogando);

void desenhaTelaTitulo(void);

void avancaTelaInicio(int teclaPressionada, enum ConjuntoTela *tela);

enum OpcaoMenuPrincipal escolheOpcaoMenuPrincipal(int teclaPressionada, enum OpcaoMenuPrincipal opcao);

void entraTela(int teclaPressionada, enum OpcaoMenuPrincipal opcao, enum ConjuntoTela *tela);

void desenhaTelaMenuPrincipal(enum OpcaoMenuPrincipal opcao);

#endif
