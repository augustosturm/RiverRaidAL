#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

void leMapa(char mapa[][24], int numArq) {
    char nome[50];

    for (int i = 0; i < numArq; i++) {  
        sprintf(nome, "Fase/Mapa/Arquivos/map%d.txt", (numArq-i));

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

    for(int i = 0; i < (numArq*20); i++){
        for(int j = 0; j < 24; j++){
            printf(" %c", mapa[i][j]);
            mapa[i][j] = mapa[i][j];
        }
        printf("\n");
    }
}

void desenhaMapa(char mapa[][24], int numArq){

    int yNormal = ((numArq-1)*-20);

    ClearBackground(RAYWHITE);
    for(int i = 0; i < (numArq*20); i++){
        for(int j = 0; j < 24; j++){
            
            if(mapa[i][j] == 'T')
                DrawRectangle(j*40, yNormal*40, 40, 40, GREEN);
            else if(mapa[i][j] == ' ')
                DrawRectangle(j*40, yNormal*40, 40, 40, SKYBLUE);
            else if(mapa[i][j] == 'X')
                DrawRectangle(j*40, yNormal*40, 40, 40, SKYBLUE);
        }
    yNormal++;
    }
    //EndDrawing();
}