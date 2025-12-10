#include "entidade.h"
#include "gasolina.h"

GASOLINA criaPostoGasolina(Vector2 posicao, Vector2 tamanhoHitbox) {
    Rectangle entidade = criaEntidade(posicao, tamanhoHitbox);

    GASOLINA posto = {
        entidade,
        0, // Comeca vivo
        {612, 62, 54, 94}, //sprite
        150
    };

    return posto;
}

void desenhaPosto(GASOLINA posto, Texture2D textura) {
    if (!posto.morto) {
        const float spriteWidth = posto.sprite.width; //> 0 ? inimigos[i].sprite.width : -inimigos[i].sprite.width
        const float spriteHeight = posto.sprite.height;// > 0 ? inimigos[i].sprite.height : -inimigos[i].sprite.height
        Rectangle source = posto.sprite;
        Rectangle destination = {
            posto.entidade.x,
            posto.entidade.y - 16, // O valor 16 desloca a textura para alinhar com a hitbox reposicionada
            spriteWidth,
            spriteHeight
        };
        DrawTexturePro(textura, source, destination, (Vector2){0.0f, 0.0f}, 0.0f, RAYWHITE);
    }
}

int consomeGasolina(int gasolina, int *contagem){
    if(*contagem <= 0){
        gasolina --;
       *contagem = 30;
    }
    *contagem = *contagem - 1;

    return gasolina;
}