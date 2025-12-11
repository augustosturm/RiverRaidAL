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

void salvaPontuacao(const char *nome, int pontos) {
    if (nome == NULL || nome[0] == '\0') {
        return; // Não salva se o nome estiver vazio
    }

    JogadorPontos ranking[MAXRANKING + 1];
    int totalJogadores = leRanking(ranking, MAXRANKING);

    // Se o arquivo não existe/está vazio, leRanking retorna < 0. Começamos do zero.
    if (totalJogadores < 0) {
        totalJogadores = 0;
    }

    // Adiciona a nova pontuação ao final da lista lida
    strcpy(ranking[totalJogadores].nome, nome);
    ranking[totalJogadores].pontos = pontos;
    totalJogadores++;

    // Ordena a lista completa
    ordenaRankingPorPontuacao(ranking, totalJogadores);

    // Decide quantos scores salvar (no máximo MAXRANKING)
    int scoresParaSalvar = (totalJogadores > MAXRANKING) ? MAXRANKING : totalJogadores;

    // Reabre o arquivo em modo de escrita para apagar o conteúdo antigo
    FILE *arq = fopen("Menu/MenuScore/JogadoresPontos.txt", "w");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo de pontuações para escrita");
        return;
    }

    // Salva os scores do topo do ranking
    for (int i = 0; i < scoresParaSalvar; i++) {
        fprintf(arq, "%s %d\n", ranking[i].nome, ranking[i].pontos);
    }

    fclose(arq);
}