#include "pontuacao.h"

#define PONTOPERDIDOSMORTE 500

void adicionaPontos(PONTUACAO *pontuacao, int pontosRecebidos) {
    pontuacao->pontos += pontosRecebidos;
}

void perdePontosMorte(PONTUACAO *pontuacao) {
    int pontuacaoSubtraida = pontuacao->pontos - PONTOPERDIDOSMORTE;

    if (pontuacaoSubtraida < 0) {
        pontuacaoSubtraida = 0;
    } 

    pontuacao->pontos = pontuacaoSubtraida;
}