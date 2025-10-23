#include "raylib.h"
#include "entity.h"

Rectangle createEntity(Vector2 pos, Vector2 hitBoxArea) {
       Rectangle entity = {
        pos.x,
        pos.y,
        hitBoxArea.x,
        hitBoxArea.y
    };

    return entity;
}
