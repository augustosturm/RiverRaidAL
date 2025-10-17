#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define LARGURA 600
#define ALTURA 600

int main(){
    InitWindow(LARGURA, ALTURA, "Teclas"); //Inicializa janela, com certo tamanho e titulo
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

	int posx = 280, posy = 280;

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose())
    {
	// Trata entrada do usuario e atualiza estado do jogo
	if (IsKeyPressed(KEY_RIGHT)) {
	    posx += 20;
	}
	if (IsKeyPressed(KEY_LEFT)) {
	    posx -= 20;
	}
	if (IsKeyPressed(KEY_UP)) {
	    posy -= 20;
	}
	if (IsKeyPressed(KEY_DOWN)) {
	    posy += 20;
	}

	// Atualiza o que eh mostrado na tela a partir do estado do jogo
	BeginDrawing(); //Inicia o ambiente de desenho na tela
	ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
	DrawRectangle(posx, posy, 20, 20, GREEN); //Desenha um texto, com posicao, tamanho e cor
	EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
}
