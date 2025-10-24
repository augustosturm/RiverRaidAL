#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "raylib.h"

typedef struct {
    Rectangle entity;
    float speed;
    int missileFired;
} Player;

Player createPlayer(Vector2 pos, Vector2 hitBoxArea, float speed);

bool checkCollisionEnemy(Rectangle playerEntity, Rectangle enemyEntity);

#endif
