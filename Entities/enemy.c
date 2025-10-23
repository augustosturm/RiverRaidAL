#include "raylib.h"
#include "enemy.h"

void moveEnemy(Enemy *e) {
    e->entity.x += e->speed * e->direction * GetFrameTime();

    if (e->entity.x > e->maxX || e->entity.x < e->minX) {
        e->direction *= -1;
    }
}