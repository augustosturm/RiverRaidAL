#include "raylib.h"
#include "nomeJogador.h"
#include <ctype.h> 

void insereNomeJogador(int tamanhoNome, int *posicao, char *nomeJogador) {
    int tecla = GetCharPressed();
    int posicaoLocal = *posicao;

    if (tecla >= 32 && tecla <= 125 && posicaoLocal < tamanhoNome) {
        nomeJogador[posicaoLocal] = toupper((char)tecla);
        posicaoLocal++;
        nomeJogador[posicaoLocal] = '\0';
    }

    if (IsKeyPressed(KEY_BACKSPACE) && posicaoLocal > 0) {
        posicaoLocal--;
        nomeJogador[posicaoLocal] = '\0';
    }

    *posicao = posicaoLocal;
}

void imprimeNomeJogador(const char *nomeJogador, int pontos, int posRanking) {
    const int posVertical = posRanking * 40 + 70;

    DrawText(TextFormat("%02d. %s", posRanking + 1, nomeJogador), 20, posVertical, 30, YELLOW);
    DrawText(TextFormat("%d", pontos), 400, posVertical, 30, YELLOW);
}
