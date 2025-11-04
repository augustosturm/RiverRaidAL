#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

void desenhaMapa() {
    char nome[50];
    int numArq = 2;  // número de mapas
    char mapa[20 * numArq][24];  // 20 linhas por mapa, 24 colunas

    for (int i = 0; i < numArq; i++) {  
        sprintf(nome, "Arquivos/map%d.txt", (numArq-i));

        FILE *arquivo = fopen(nome, "r");

        if (arquivo) {
            for(int j = (i*20); j < ((i+1)*20) ; j++){
                fgets(mapa[j], 26, arquivo);
            }

            fclose(arquivo);

        } else {
            printf("Erro ao abrir %s\n", nome);
            break;
        }
    }

    BeginDrawing();
    for(int i = 0; i < (numArq*20); i++){
        for(int j = 0; j < 24; j++){
            printf(" %c", mapa[i][j]);
            DrawRectangle(i*16, (j+1)*16, 16, 16, BLUE);
        }
        printf("\n");
    }
    EndDrawing();
}