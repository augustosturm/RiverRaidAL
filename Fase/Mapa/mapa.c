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

void desenhaMapa(char mapa[][24], int numArq, Rectangle terrenos[]){

    int yNormal = ((numArq-1)*-20);

    ClearBackground(RAYWHITE);

    for(int i = 0; i < (numArq*20); i++){

        for(int j = 0; j < 24; j++){
            float posx = j*40;
            float posy = yNormal*40;
            float width = 40;
            float height = 40;

            if(mapa[i][j] == 'T'){
                DrawRectangle(posx, posy, width, height, GREEN);
                if ((i % 20) >= 3 && (i % 20) <= 6){
                    terrenos[(i%20)*j] = (Rectangle){posx, posy, width, height};
                }
            }
            else if(mapa[i][j] == ' ')
                DrawRectangle(posx, posy, width, height, SKYBLUE);
            else if(mapa[i][j] == 'X')
                DrawRectangle(posx, posy, width, height, SKYBLUE);
            else if(mapa[i][j] == 'A')
                DrawRectangle(posx, posy, width, height, SKYBLUE);
        }

        yNormal++;
        if ((i % 20) == 19) {
            for (int j = 0; j < 24; j++) {
                DrawRectangle(j * 40, yNormal * 40, 40, 40, BROWN);
            }
            yNormal++;
        }
    }
}
