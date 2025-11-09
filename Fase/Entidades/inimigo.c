#include "entidade.h"
#include "inimigo.h"

INIMIGO criaInimigo(Vector2 posicao, Vector2 tamanhoHitbox, float velocidade, int minimoX, int maximoX) {
    Rectangle entidade = criaEntidade(posicao, tamanhoHitbox);

    INIMIGO inimigo = {
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

void moveInimigo(INIMIGO *inimigo, int jogadorPosicaoY) {
    if (inimigo->movendo) {
        atualizaPosicaoInimigo(inimigo);
    } else {
        if (verificaJogadorProximo(inimigo, jogadorPosicaoY)) {
            inimigo->movendo = 1;
        }
    }
}

void atualizaPosicaoInimigo(INIMIGO *inimigo) {
    inimigo->entidade.x += inimigo->velocidade * inimigo->direcao * GetFrameTime();
    
    mudaDirecaoInimigo(inimigo);
}

void mudaDirecaoInimigo(INIMIGO *inimigo) {
    if (inimigo->entidade.x > inimigo->maximoX || inimigo->entidade.x < inimigo->minimoX) {
        inimigo->direcao *= -1;
    }
}

bool verificaJogadorProximo(INIMIGO *inimigo, int jogadorPosicaoY) {
    int distanciaAteJogador = jogadorPosicaoY - inimigo->entidade.y;
    return distanciaAteJogador < DIFPOS;
}

