#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "Entities/enemy.h"
#include "Entities/entity.h"
#include "Entities/player.h"

int main(void) {
    InitWindow(800, 450, "Movimento básico");
    SetTargetFPS(60);

    Vector2 posPlayerIni = {400, 225};
    Vector2 sizePlayer = {20, 20};
    float speedPlayer = 200.0f;
    Player player = createPlayer(posPlayerIni, sizePlayer, speedPlayer, 0);

    Rectangle missile;
    int missileFlying = 0;

    Enemy enemies[2] = {
        { createEntity((Vector2){400, 100}, size), 100.0f, 1, 350, 500 },
        { createEntity((Vector2){200, 200}, size), 150.0f, -1, 150, 350 }
    };


    while (!WindowShouldClose()) {
        float dt = GetFrameTime();


        if (IsKeyDown(KEY_SPACE) && missileFlying == 0) {
            missile = createEntity((Vector2) {player.entity.x, player.entity.y}, (Vector2) {50,50});
            missileFlying = 1;
        }
        
        // Desenho
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleRec(player.entity, RED);
        if (missileFlying == 1) {
            missile.y -= speedPlayer * dt;
            DrawRectangleRec(missile, GREEN);
        }


        for (int i = 0; i < 2; i++) {
            if (enemies[i].dead == 0) {
                moveEnemy(&enemies[i]);
                DrawRectangleRec(enemies[i].entity, BLUE);
            }
            checkCollisionEnemy(player.entity, enemies[i].entity);
            
            // if (CheckCollisionRecs(missile, )) {
            //     return 0;
            // }
        }

        // Movimento do jogador
        if (IsKeyDown(KEY_RIGHT)) player.entity.x += speedPlayer * dt;
        if (IsKeyDown(KEY_LEFT))  player.entity.x -= speedPlayer * dt;
        if (IsKeyDown(KEY_UP))    player.entity.y -= speedPlayer * dt;
        if (IsKeyDown(KEY_DOWN))  player.entity.y += speedPlayer * dt;

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
