#include <stdbool.h>
#include "raylib.h"
#include "entidade.h"
#include "jogador.h"


JOGADOR criaJogador(Vector2 posicao, Vector2 tamanhoHitbox, float velocidade, Rectangle sprite) {
    const Rectangle entidade = criaEntidade(posicao, tamanhoHitbox);

    JOGADOR jogador = {
        entidade,
        velocidade,
        false,
        sprite,
        {{0}, {0}}
    };

    atualizaSpriteEHitboxesJogador(&jogador, sprite, Parado);

    return jogador;
}

void atualizaSpriteEHitboxesJogador(JOGADOR *jogador, Rectangle sprite, enum HitBoxJogador hitboxEstado) {
    jogador->sprite = sprite;
    jogador->hitboxes[0] = atualizaHitboxSuperiorJogador(jogador->entidade, hitboxEstado);
    jogador->hitboxes[1] = atualizaHitboxInferiorJogador(jogador->entidade, hitboxEstado);
}

Rectangle atualizaHitboxSuperiorJogador(Rectangle entidadeJogador, enum HitBoxJogador hitBoxAtualParams) {
    float fracaoTopo;
    float porcentagemRecuoSup;

    switch (hitBoxAtualParams) {
        case Parado:
            fracaoTopo = 0.4f;
            porcentagemRecuoSup = 0.40f;
            break;
        case MovDireira:
            fracaoTopo = 0.4f;
            porcentagemRecuoSup = 0.40f;
            break;
        case MovEsquerda:
            fracaoTopo = 0.4f;
            porcentagemRecuoSup = 0.40f;
            break;
        default:
            break;
    }

    return (Rectangle) {
        entidadeJogador.x + entidadeJogador.width * porcentagemRecuoSup,
        entidadeJogador.y,
        entidadeJogador.width * (1.0f - 2.0f * porcentagemRecuoSup),
        entidadeJogador.height * fracaoTopo
    };
}

Rectangle atualizaHitboxInferiorJogador(Rectangle entidadeJogador, enum HitBoxJogador hitBoxAtualParams) {
    float fracaoTopo;
    float porcentagemRecuoInf;

    switch (hitBoxAtualParams) {
    case Parado:
        fracaoTopo = 0.4f;
        porcentagemRecuoInf = 0.10f;
        break;
    case MovDireira:
        fracaoTopo = 0.4f;
        porcentagemRecuoInf = 0.20f;
        break;
    case MovEsquerda:
        fracaoTopo = 0.4f;
        porcentagemRecuoInf = 0.20f;
        break;
    default:
        break;
    }

    return (Rectangle) {
        entidadeJogador.x + entidadeJogador.width * porcentagemRecuoInf,
        entidadeJogador.y + entidadeJogador.height * fracaoTopo,
        entidadeJogador.width * (1.0f - 2.0f * porcentagemRecuoInf),
        entidadeJogador.height * (1.0f - fracaoTopo)
    };
}

bool verificaColisaoInimigo(Rectangle hitboxesJogador[], Rectangle entidadeInimigo) {
    bool colidiu = false;

    for (int h = 0; h < NUMHITBOX; h++) {
        if (CheckCollisionRecs(hitboxesJogador[h], entidadeInimigo)) {
            colidiu = true;
        }
    }
    
    return colidiu;
}

void disparaMissil(JOGADOR *jogador, MISSIL *missil) {
    static const Vector2 TAMANHO_MISSIL = {22.0f, 86.0f};
    static const float VELOCIDADE_MISSIL = 800.0f;
    static const Rectangle SPRITE_MISSIL = {22, 86, 7, 31};

    if (jogador->missilDisparado) {
        return;
    }

    *missil = criaMissil(*jogador, TAMANHO_MISSIL, VELOCIDADE_MISSIL, SPRITE_MISSIL);
    jogador->missilDisparado = true;
}

MISSIL criaMissil(JOGADOR jogador, Vector2 tamanhoMissil, float velocidade, Rectangle sprite) {
    Vector2 posicaoMissil = {
        jogador.entidade.x + jogador.entidade.width / 2.0f - tamanhoMissil.x / 2.0f,
        jogador.entidade.y
    };

    Rectangle entidadeMissil = criaEntidade(posicaoMissil, tamanhoMissil);

    MISSIL missil = {
        entidadeMissil,
        velocidade,
        sprite
    };

    return missil;
}

void atualizaPosicaoMissil(JOGADOR *jogador, MISSIL *missil, float tempoDecorrido) {
    if (!jogador->missilDisparado) {
        return;
    }

    missil->entidade.y -= missil->velocidade * tempoDecorrido;

    if (missil->entidade.y + missil->entidade.height < ((jogador->entidade.y) - 650)) {
    jogador->missilDisparado = false;
    }
}

void desenhaMissil(MISSIL missil, Texture2D textura) {
    const float spriteWidth = missil.sprite.width; //> 0 ? inimigos[i].sprite.width : -inimigos[i].sprite.width
    const float spriteHeight = missil.sprite.height;// > 0 ? inimigos[i].sprite.height : -inimigos[i].sprite.height
    Rectangle source = missil.sprite;
    Rectangle destination = {
        missil.entidade.x,
        missil.entidade.y,
        spriteWidth,
        spriteHeight
    };

    DrawTexturePro(textura, source, destination, (Vector2){0.0f, 0.0f}, 0.0f, RAYWHITE);
}