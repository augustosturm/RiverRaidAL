#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

/**
 * @brief Create a rectangle from position and hitbox size.
 *
 * @param pos Initial position.
 * @param hitBoxArea Hitbox size.
 * @return Rectangle with the given position and size.
 */
Rectangle createEntity(Vector2 pos, Vector2 hitBoxArea);

#endif