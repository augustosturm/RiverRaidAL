#include "raylib.h"
#include "enemy.h"

typedef struct {
    Rectangle entity;
    float speed;
    int direction;
    float minX, maxX;
} Enemy;

void moveEnemy(Enemy *e) {
    e->entity.x += e->speed * e->direction * GetFrameTime();

    if (e->entity.x > e->maxX || e->entity.x < e->minX) {
        e->direction *= -1;
    }
}