#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistemaPontuacao.h"
#include "nomeJogador.h"

static int ordenaPorPontuacaoDesc(const void *a, const void *b) {
    const JogadorPontos *entradaA = (const JogadorPontos *)a;
    const JogadorPontos *entradaB = (const JogadorPontos *)b;

    return entradaB->pontos - entradaA->pontos;
}

int leRanking(JogadorPontos *ranking, int maxEntradas) {
    int totalJogadores = 0;
    FILE *arq = fopen("Menu/MenuScore/JogadoresPontos.txt", "r");

    if (arq == NULL) {
        return -1;
    } else {
        while (!feof(arq) && totalJogadores < maxEntradas) {
            if (fscanf(arq, "%31s %d", ranking[totalJogadores].nome, &ranking[totalJogadores].pontos) == 2) {
                totalJogadores++;
            }
        }
    
        fclose(arq);
    
        return totalJogadores;
    }
}

void ordenaRankingPorPontuacao(JogadorPontos *ranking, int totalJogadores) {
    if (ranking == NULL || totalJogadores <= 1) {
        return;
    }

    qsort(ranking, totalJogadores, sizeof(JogadorPontos), ordenaPorPontuacaoDesc);
}

void imprimeRankingJogadores(const JogadorPontos *ranking, int totalJogadores) {
    if (ranking == NULL || totalJogadores <= 0) {
        return;
    }

    for (int i = 0; i < totalJogadores; i++) {
        imprimeNomeJogador(ranking[i].nome, ranking[i].pontos, i);
    }
}
