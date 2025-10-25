#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

typedef struct {
    Rectangle entity;
    float speed;
    int direction;
    int minX;
    int maxX;
    int dead;
} Enemy;

/**
 * @brief Creates an enemy with speed, direction and range of movement.
 *
 * @param pos Initial position.
 * @param hitBoxArea Hitbox size.
 * @return Entity representing a Rectangle.
 */
Enemy createEnemy(Vector2 pos, Vector2 hitBoxArea, float speed, int minX, int maxX);

/**
 * @brief Moves the enemy along the X axis.
 *
 * @param Enemy e Pointer to the enemy.
 * @return void
 */
void moveEnemy(Enemy *e);

/**
 * @brief Changes the enemy's direction when it reaches the movement limit.
 *
 * @param Enemy e Pointer to the enemy.
 * @return void
 */
void changeEnemyDirection(Enemy *e);

#endif
