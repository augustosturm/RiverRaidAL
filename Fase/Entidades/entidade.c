#include "raylib.h"
#include "entidade.h"

Rectangle criaEntidade(Vector2 posicao, Vector2 tamanhoHitbox) {
    Rectangle entidade = {
        posicao.x,
        posicao.y,
        tamanhoHitbox.x,
        tamanhoHitbox.y
    };

    return entidade;
}
