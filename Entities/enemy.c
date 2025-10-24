#include "raylib.h"
#include "entity.h"
#include "enemy.h"

Enemy createEnemy(Vector2 pos, Vector2 hitBoxArea, float speed, int minX, int maxX) {
    Rectangle entity = createEntity(pos, hitBoxArea);

    Enemy e = {
        entity,
        speed,
        1, //Futuramente irá mudar isso
        minX,
        maxX,
        0 //Começa vivo
    };

    return e;
}

void moveEnemy(Enemy *e) {
    e->entity.x += e->speed * e->direction * GetFrameTime();

    changeEnemyDirection(e);
}

void changeEnemyDirection(Enemy *e) {
    if (e->entity.x > e->maxX || e->entity.x < e->minX) {
        e->direction *= -1;
    }
}
