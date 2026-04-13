#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "resource_dir.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450
#define TILE_SIZE     34
#define MAP_WIDTH     250
#define MAP_HEIGHT    103


int map[MAP_HEIGHT][MAP_WIDTH] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

#define SPRING_WIDTH  32
#define SPRING_HEIGHT 32

struct Animation {
    int Frame;
    int Counter;
    int Speed;
} Spring;

void AnimationSettings() {
    Spring.Counter++;
    if (Spring.Counter >= (85 / Spring.Speed)) {
        Spring.Counter = 0;
        Spring.Frame++;
        if (Spring.Frame > 1) Spring.Frame = 0;
    }
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "_C4STL3V4N14_");
    SearchAndSetResourceDir("resources");

    Texture2D rabbitIdleR = LoadTexture("wabbit_alpha.png");
    Texture2D rabbitIdleL = LoadTexture("OtherSide.png");
    Texture2D animR = LoadTexture("Anim_R.png");
    Texture2D animL = LoadTexture("Anim_L.png");
    Texture2D fondo = LoadTexture("maapa.png");

    if (fondo.id == 0) {
        TraceLog(LOG_ERROR, "No se pudo cargar la imagen 'castlevania.png'");
    }
    SetTextureFilter(fondo, TEXTURE_FILTER_POINT);

    float playerX = 200.0f;
    float playerY = 0.0f;
    float velocityY = 0.0f;
    const float GRAVITY = 0.8f;
    const float JUMP_FORCE = -12.0f;
    bool isGrounded = false;
    int direction = 0;
    bool isMoving = false;
    float moveSpeed = 3.0f;

    Spring.Speed = 5;
    Spring.Frame = 0;
    Spring.Counter = 0;

    Camera2D camera = { 0 };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.zoom = 2.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        AnimationSettings();

        isMoving = false;
        if (IsKeyDown(KEY_D)) {
            playerX += moveSpeed;
            direction = 0;
            isMoving = true;
        }
        if (IsKeyDown(KEY_A)) {
            playerX -= moveSpeed;
            direction = 1;
            isMoving = true;
        }

        velocityY += GRAVITY;
        playerY += velocityY;

        int tileX = (int)(playerX + SPRING_WIDTH / 2) / TILE_SIZE;
        int tileY = (int)(playerY + SPRING_HEIGHT) / TILE_SIZE;
        if (tileY >= MAP_HEIGHT) tileY = MAP_HEIGHT - 1;
        if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
            if (map[tileY][tileX] == 1) {
                playerY = tileY * TILE_SIZE - SPRING_HEIGHT;
                velocityY = 0;
                isGrounded = true;
            }
            else {
                isGrounded = false;
            }
        }
        else {
            isGrounded = false;
        }

        if (isGrounded && IsKeyPressed(KEY_SPACE)) {
            velocityY = JUMP_FORCE;
            isGrounded = false;
        }

        if (playerX < 0) playerX = 0;
        if (playerX > SCREEN_WIDTH - SPRING_WIDTH) playerX = SCREEN_WIDTH - SPRING_WIDTH;

        camera.target = (Vector2){ playerX + SPRING_WIDTH / 2, playerY + SPRING_HEIGHT / 2 };

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        DrawTextureEx(fondo, (Vector2) { 0, 0 }, 0, 2.0f, WHITE);

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] == 1) {
                    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
                }
            }
        }

        Rectangle sourceRect = { Spring.Frame * SPRING_WIDTH, 0, SPRING_WIDTH, SPRING_HEIGHT };
        Rectangle destRect = { playerX, playerY, SPRING_WIDTH, SPRING_HEIGHT };
        Vector2 origin = { 0, 0 };

        if (isMoving) {
            if (direction == 0) {
                DrawTexturePro(animR, sourceRect, destRect, origin, 0, WHITE);
            }
            else {
                DrawTexturePro(animL, sourceRect, destRect, origin, 0, WHITE);
            }
        }
        else {
            if (direction == 0) {
                DrawTextureEx(rabbitIdleR, (Vector2) { playerX, playerY }, 0, 1.0f, WHITE);
            }
            else {
                DrawTextureEx(rabbitIdleL, (Vector2) { playerX, playerY }, 0, 1.0f, WHITE);
            }
        }

        EndMode2D();

        if (fondo.id == 0) {
            DrawText("ERROR: No se cargo la imagen 'castlevania.png'", 10, 10, 20, RED);
        }

        EndDrawing();
    }

    UnloadTexture(rabbitIdleR);
    UnloadTexture(rabbitIdleL);
    UnloadTexture(animR);
    UnloadTexture(animL);
    UnloadTexture(fondo);
    CloseWindow();

    return 0;
}