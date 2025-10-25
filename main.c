#include <stdbool.h>
#include "raylib.h"
#include "Entities/entity.h"
#include "Entities/player.h"
#include "Entities/enemy.h"


int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Teste");
    SetTargetFPS(60);

    //-------------------------------------------------------------------------
    const Vector2 playerSize = {20.0f, 20.0f};
    const Vector2 playerPosStart = {screenWidth / 2.0f - playerSize.x / 2.0f, screenHeight - playerSize.y * 2.0f};
    const float playerSpeed = 200.0f;
    Player player = createPlayer(playerPosStart, playerSize, playerSpeed);
    //-------------------------------------------------------------------------
    const Vector2 missileSize = {5.0f, 5.0f};
    const float missileSpeed = 400.0f;
    Missile missile = {0};

    const Vector2 enemySize = {20.0f, 20.0f};
    Enemy enemies[2];
    enemies[0] = createEnemy((Vector2){400.0f, 100.0f}, enemySize, 100.0f, 350, 500);
    enemies[1] = createEnemy((Vector2){200.0f, 200.0f}, enemySize, 150.0f, 150, 350);

    while (!WindowShouldClose()) {
        const float ft = GetFrameTime();

        if (IsKeyDown(KEY_SPACE)) {
            fireMissile(&player, &missile, missileSize, missileSpeed);
        }

        updateMissilePos(&player, &missile, ft);

        //-----------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) player.entity.x += player.speed * ft;
        if (IsKeyDown(KEY_LEFT)) player.entity.x -= player.speed * ft;
        if (IsKeyDown(KEY_UP)) player.entity.y -= player.speed * ft;
        if (IsKeyDown(KEY_DOWN)) player.entity.y += player.speed * ft;

        if (player.entity.x < 0) player.entity.x = 0;
        if (player.entity.y < 0) player.entity.y = 0;
        if (player.entity.x + player.entity.width > screenWidth) player.entity.x = screenWidth - player.entity.width;
        if (player.entity.y + player.entity.height > screenHeight) player.entity.y = screenHeight - player.entity.height;
        //-----------------------------------------------------------

        for (int i = 0; i < 2; i++) {
            //MODIFICAR
            Enemy *enemy = &enemies[i];
            if (enemy->dead) {
                continue;
            }
            //---------
            moveEnemy(enemy);

            if (CheckCollisionRecs(missile.entity, enemy->entity)) {
                enemy->dead = 1;
                player.missileFired = false;
            }

            if (checkCollisionEnemy(player.entity, enemy->entity)) {
                CloseWindow();
                return 0;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(player.entity, RED);

        if (player.missileFired) {
            DrawRectangleRec(missile.entity, GREEN);
        }

        for (int i = 0; i < 2; i++) {
            if (!enemies[i].dead) {
                DrawRectangleRec(enemies[i].entity, BLUE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
