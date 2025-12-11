#include "entidade.h"
#include "inimigo.h"

INIMIGO criaHelicoptero(Vector2 posicao, int minimoX, int maximoX) {
    static const Vector2 hitboxHelicoptero = {64.0f, 15.0f};
    static const float velocidadeHelicoptero = 150.0f;
    static const int pontosHelicoptero = 100;
    Rectangle spriteHelicoptero = {11, 186, 63, 39};

    return criaInimigo(posicao, hitboxHelicoptero, velocidadeHelicoptero, minimoX, maximoX, spriteHelicoptero, pontosHelicoptero);
}

INIMIGO criaNavio(Vector2 posicao, int minimoX, int maximoX) {
    static const Vector2 hitboxNavio= {127.0f, 15.0f};
    static const float velocidadeNavio = 100.0f;
    static const int pontosNavio = 75;
    static const Rectangle spriteNavio = {14, 234, 127, 31};
    
    return criaInimigo(posicao, hitboxNavio, velocidadeNavio, minimoX, maximoX, spriteNavio, pontosNavio);
}

INIMIGO criaInimigoAleatorio(Vector2 posicao, int minimoX, int maximoX) {
    const bool criaHelicopteroAleatorio = GetRandomValue(0, 1);
    
    if (criaHelicopteroAleatorio) {
        return criaHelicoptero(posicao, minimoX, maximoX);
    }

    return criaNavio(posicao, minimoX, maximoX);
}

INIMIGO criaInimigo(Vector2 posicao, Vector2 tamanhoHitbox, float velocidade, int minimoX, int maximoX, Rectangle sprite, int pontos) {
    Rectangle entidade = criaEntidade(posicao, tamanhoHitbox);

    INIMIGO inimigo = {
        entidade,
        velocidade,
        geraDirecaoInicial(),
        minimoX,
        maximoX,
        0, // Comeca vivo
        0, // Comeca parado
        sprite,
        pontos
    };

    return inimigo;
}

int geraDirecaoInicial(void) {
    return GetRandomValue(0, 1)*2 - 1;
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

void desenhaInimigo(INIMIGO inimigo, Texture2D textura) {
    if (!inimigo.morto) {
        const float spriteWidth = inimigo.sprite.width * 0.8f; //> 0 ? inimigos[i].sprite.width : -inimigos[i].sprite.width
        const float spriteHeight = inimigo.sprite.height * 0.8f;// > 0 ? inimigos[i].sprite.height : -inimigos[i].sprite.height
        Rectangle source = inimigo.sprite;
        Rectangle destination = {
            inimigo.entidade.x,
            inimigo.entidade.y - 16, // O valor 16 desloca a textura para alinhar com a hitbox reposicionada
            spriteWidth,
            spriteHeight
        };

        if (inimigo.direcao < 0) {
            source.width *= -1;
        }

        DrawTexturePro(textura, source, destination, (Vector2){0.0f, 0.0f}, 0.0f, RAYWHITE);
    }
}

void atualizaAnimacaoHelice(INIMIGO *inimigo) {
    if (inimigo->entidade.width != 64.0f) return;

    const float intervalo = 0.04f;
    int frame = ((int)(GetTime() / intervalo)) & 1;

    inimigo->sprite.x = (frame == 0) ? 10 : 83;
}
