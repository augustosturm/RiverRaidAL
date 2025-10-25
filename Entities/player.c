#include <stdbool.h>
#include "raylib.h"
#include "entity.h"
#include "player.h"

Player createPlayer(Vector2 pos, Vector2 hitBoxArea, float speed) {
    Rectangle entity = createEntity(pos, hitBoxArea);

    Player player = {
        entity,
        speed,
        false
    };

    return player;
}

bool checkCollisionEnemy(Rectangle playerEntity, Rectangle enemyEntity) {
    return CheckCollisionRecs(playerEntity, enemyEntity);
}

Missile createMissile(Player player, Vector2 missileSize, float speed) {
    Vector2 missilePos = {
        player.entity.x + player.entity.width / 2.0f - missileSize.x / 2.0f,
        player.entity.y
    };

    Rectangle missileEntity = createEntity(missilePos, missileSize);

    Missile missile = {
        missileEntity,
        speed
    };

    return missile;
}

void fireMissile(Player *player, Missile *missile, Vector2 missileSize, float missileSpeed) {
    if (player->missileFired) {
        return;
    }

    *missile = createMissile(*player, missileSize, missileSpeed);
    player->missileFired = true;
}

void updateMissilePos(Player *player, Missile *missile, float ft) {
    if (!player->missileFired) {
        return;
    }

    missile->entity.y -= missile->speed * ft;
    if (missile->entity.y + missile->entity.height < 0) {
        player->missileFired = false;
    }
}
