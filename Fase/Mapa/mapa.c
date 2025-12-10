#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

void leMapa(char mapa[][24], int numArq, Vector2 inimigosPos[], int *numInimigos, Vector2 *posicaoIni) {
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

    int yNormal = ((numArq-1)*-20);

    for(int i = 0; i < (numArq*20); i++){

        for(int j = 0; j < 24; j++){

            float posx = j*40;
            float posy = yNormal*40;

            printf(" %c", mapa[i][j]);
            if (mapa[i][j] == 'X')
            {
                printf("\n%f e %f", posx, posy);
                inimigosPos[*numInimigos] = (Vector2){posx, posy}; 
                *numInimigos += 1;
            }
            if (mapa[i][j] == 'A')
            {
                *posicaoIni = (Vector2){posx, posy};
            }
        }
        printf("\n");
        yNormal++;
        if ((i % 20) == 19){
            yNormal++;
        }
    }
}

void desenhaMapa(char mapa[][24], int numArq, Rectangle terrenos[], int *numTerreno){

    int yNormal = ((numArq-1)*-20);
    *numTerreno = 0;

    ClearBackground(RAYWHITE);

    for(int i = 0; i < (numArq*20); i++){

        for(int j = 0; j < 24; j++){
            float posx = j*40;
            float posy = yNormal*40;
            float width = 40;
            float height = 40;

            if(mapa[i][j] == 'T'){
                DrawRectangle(posx, posy, width, height, GREEN);
                terrenos[*numTerreno] = (Rectangle){posx, posy, width, height};
                *numTerreno += 1;
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
