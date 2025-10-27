#include <stdbool.h>
#include "raylib.h"
#include "Entities/entity.h"
#include "Entities/player.h"
#include "Entities/enemy.h"
#include "Menu/mainMenu.h"


int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    int esc = 1;
    int keyPressed;
    enum ScreenSet screen = Title;

    //-------------------------------------------------------------------------
    const Vector2 playerSize = {20.0f, 20.0f};
    const Vector2 playerPosStart = {screenWidth / 2.0f - playerSize.x / 2.0f, screenHeight - playerSize.y * 2.0f};
    const float playerSpeed = 200.0f;
    Player player = createPlayer(playerPosStart, playerSize, playerSpeed);
    //-------------------------------------------------------------------------
    const Vector2 missileSize = {5.0f, 5.0f};
    const float missileSpeed = 400.0f;
    Missile missile;

    const Vector2 enemySize = {20.0f, 20.0f};
    Enemy enemies[2];
    enemies[0] = createEnemy((Vector2){400.0f, 100.0f}, enemySize, 100.0f, 350, 500);
    enemies[1] = createEnemy((Vector2){200.0f, 200.0f}, enemySize, 150.0f, 150, 350);

    InitWindow(screenWidth, screenHeight, "Teste");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (screen != Game) {
            keyPressed = GetKeyPressed();
        }
   
        if (screen == Title) {
            drawTitleScreen();
            
            if (keyPressed == KEY_ENTER) {
                screen = MainMenu;
            }
        } else if (screen == MainMenu) {
            if (keyPressed == KEY_DOWN && esc < 4) {
                esc++;
            }
            if (keyPressed == KEY_UP && esc > 1) {
                esc--;
            }

            if (keyPressed == KEY_ENTER && esc == 1) {
                screen = Game;
            }

            if (keyPressed == KEY_ENTER && esc == 4) {
                CloseWindow();
                return 0;
            }
            
            BeginDrawing();
            ClearBackground(BLUE);
            DrawText("Novo jogo", 100, 150, 50, YELLOW);
            DrawText("Carregar jogo", 100, 200, 50, YELLOW);
            DrawText("Ranking", 100, 250, 50, YELLOW);
            DrawText("Sair", 100, 300, 50, YELLOW);

            switch (esc)
            {
                case 1:
                    DrawRectangle(50, 170, 10, 10, YELLOW);
                    break;
                case 2:
                    DrawRectangle(50, 220, 10, 10, YELLOW);
                    break;
                case 3:
                    DrawRectangle(50, 270, 10, 10, YELLOW);
                    break;
                case 4:
                    DrawRectangle(50, 320, 10, 10, YELLOW);
                    break;
                default:
                    break;
            }


            EndDrawing();
        } else if (screen == Game) {
            const float ft = GetFrameTime();

            if (IsKeyDown(KEY_SPACE)) {
                fireMissile(&player, &missile, missileSize, missileSpeed);
            }

            updateMissilePos(&player, &missile, ft);

            if (IsKeyDown(KEY_RIGHT)) player.entity.x += player.speed * ft;
            if (IsKeyDown(KEY_LEFT)) player.entity.x -= player.speed * ft;
            if (IsKeyDown(KEY_UP)) player.entity.y -= player.speed * ft;
            if (IsKeyDown(KEY_DOWN)) player.entity.y += player.speed * ft;

            if (player.entity.x < 0) player.entity.x = 0;
            if (player.entity.y < 0) player.entity.y = 0;
            if (player.entity.x + player.entity.width > screenWidth) player.entity.x = screenWidth - player.entity.width;
            if (player.entity.y + player.entity.height > screenHeight) player.entity.y = screenHeight - player.entity.height;

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
    }

    CloseWindow();
    return 0;
}
