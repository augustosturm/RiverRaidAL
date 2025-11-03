#include <stdbool.h>
#include "raylib.h"
#include "entidade.h"
#include "jogador.h"

Jogador criaJogador(Vector2 posicao, Vector2 tamanhoHitbox, float velocidade) {
    Rectangle entidade = criaEntidade(posicao, tamanhoHitbox);

    Jogador jogador = {
        entidade,
        velocidade,
        false
    };

    return jogador;
}

bool verificaColisaoInimigo(Rectangle retanguloJogador, Rectangle retanguloInimigo) {
    return CheckCollisionRecs(retanguloJogador, retanguloInimigo);
}

Missil criaMissil(Jogador jogador, Vector2 tamanhoMissil, float velocidade) {
    Vector2 posicaoMissil = {
        jogador.entidade.x + jogador.entidade.width / 2.0f - tamanhoMissil.x / 2.0f,
        jogador.entidade.y
    };

    Rectangle entidadeMissil = criaEntidade(posicaoMissil, tamanhoMissil);

    Missil missil = {
        entidadeMissil,
        velocidade
    };

    return missil;
}

void disparaMissil(Jogador *jogador, Missil *missil, Vector2 tamanhoMissil, float velocidadeMissil) {
    if (jogador->missilDisparado) {
        return;
    }

    *missil = criaMissil(*jogador, tamanhoMissil, velocidadeMissil);
    jogador->missilDisparado = true;
}

void atualizaPosicaoMissil(Jogador *jogador, Missil *missil, float tempoDecorrido) {
    if (!jogador->missilDisparado) {
        return;
    }

    missil->entidade.y -= missil->velocidade * tempoDecorrido;
    if (missil->entidade.y + missil->entidade.height < 0) {
        jogador->missilDisparado = false;
    }
}
