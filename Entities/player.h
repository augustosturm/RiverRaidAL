#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "raylib.h"

typedef struct {
    Rectangle entity;
    float speed;
    bool missileFired;
} Player;

typedef struct {
    Rectangle entity;
    float speed;
} Missile;

/**
 * @brief Create a player with initial position, hitbox size and speed.
 *
 * @param pos Initial player position.
 * @param hitBoxArea Hitbox size (width x height).
 * @param speed Base player speed.
 * @return Player struct initialized with missileFired = false.
 */
Player createPlayer(Vector2 pos, Vector2 hitBoxArea, float speed);

/**
 * @brief Check rectangle collision between player and enemy.
 *
 * @param playerEntity Player rectangle.
 * @param enemyEntity Enemy rectangle.
 * @return true if the rectangles overlap; false otherwise.
 */
bool checkCollisionEnemy(Rectangle playerEntity, Rectangle enemyEntity);


/**
 * @brief Create a missile aligned to the player.
 *
 * @param player Player used as position reference.
 * @param missileSize Missile size.
 * @param speed Missile vertical speed.
 * @return Initialized Missile struct.
 */
Missile createMissile(Player player, Vector2 missileSize, float speed);

/**
 * @brief Fire a missile if none is currently active.
 *
 * @param player Pointer to the player.
 * @param missile Pointer to the missile to initialize.
 * @param missileSize Missile size.
 * @param missileSpeed Missile vertical speed.
 * @return void
 */
void fireMissile(Player *player, Missile *missile, Vector2 missileSize, float missileSpeed);

/**
 * @brief Update the missile's Y position.
 *
 * @param player Pointer to the player.
 * @param missile Pointer to the active missile.
 * @param ft Delta time in seconds since the last frame.
 * @return void
 */
void updateMissilePos(Player *player, Missile *missile, float ft);

#endif
