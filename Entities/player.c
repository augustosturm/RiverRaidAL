#include "raylib.h"
#include "player.h"

void checkCollision(Rectangle player, Rectangle enemy) {
    if (CheckCollisionRecs(player, enemy)) {
        CloseWindow();
    }
}