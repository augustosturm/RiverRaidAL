#include "raylib.h"
#include "entity.h"
#include "player.h"

Player createPlayer(Vector2 pos, Vector2 hitBoxArea, float speed) {
    Rectangle entity = createEntity(pos, hitBoxArea);

    Player player = {
        entity,
        speed,
        0
    };

    return player;
}

bool checkCollisionEnemy(Rectangle playerEntity, Rectangle enemyEntity) {
    return CheckCollisionRecs(playerEntity, enemyEntity);
}
