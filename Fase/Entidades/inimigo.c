#include "entidade.h"
#include "inimigo.h"

Inimigo criaInimigo(Vector2 posicao, Vector2 tamanhoHitbox, float velocidade, int minimoX, int maximoX) {
    Rectangle entidade = criaEntidade(posicao, tamanhoHitbox);

    Inimigo inimigo = {
        entidade,
        velocidade,
        1, // Futuramente ira mudar isso
        minimoX,
        maximoX,
        0, // Comeca vivo
        0
    };

    return inimigo;
}

void moveInimigo(Inimigo *inimigo, int jogadorPosicaoY) {
    if (inimigo->movendo) {
        atualizaPosicaoInimigo(inimigo);
    } else {
        if (verificaJogadorProximo(inimigo, jogadorPosicaoY)) {
            inimigo->movendo = 1;
        }
    }
}

void atualizaPosicaoInimigo(Inimigo *inimigo) {
    inimigo->entidade.x += inimigo->velocidade * inimigo->direcao * GetFrameTime();
    
    mudaDirecaoInimigo(inimigo);
}

void mudaDirecaoInimigo(Inimigo *inimigo) {
    if (inimigo->entidade.x > inimigo->maximoX || inimigo->entidade.x < inimigo->minimoX) {
        inimigo->direcao *= -1;
    }
}

bool verificaJogadorProximo(Inimigo *inimigo, int jogadorPosicaoY) {
    int distanciaAteJogador = jogadorPosicaoY - inimigo->entidade.y;
    return distanciaAteJogador < DIFPOS;
}

