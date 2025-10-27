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

void imprimeNomeJogador(char nomeJogador[]) {
    // So teste
    // Quando fizer a tela de placar, vai ter que mudar aqui
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(nomeJogador, 20, 70, 30, BLACK);
    EndDrawing();
}
