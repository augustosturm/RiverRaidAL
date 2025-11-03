#include "raylib.h"
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
        0 // Comeca vivo
    };

    return inimigo;
}

void moveInimigo(Inimigo *inimigo) {
    inimigo->entidade.x += inimigo->velocidade * inimigo->direcao * GetFrameTime();

    mudaDirecaoInimigo(inimigo);
}

void mudaDirecaoInimigo(Inimigo *inimigo) {
    if (inimigo->entidade.x > inimigo->maximoX || inimigo->entidade.x < inimigo->minimoX) {
        inimigo->direcao *= -1;
    }
}
