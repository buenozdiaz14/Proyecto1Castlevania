#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "resource_dir.h"

// Dimensiones de la ventana
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450

// Tamaño de los sprites (32x32 para coincidir con los tiles)
#define SPRING_WIDTH  32
#define SPRING_HEIGHT 32

// Tamaño de los tiles
#define TILE_SIZE     34
#define MAP_WIDTH     250
#define MAP_HEIGHT    103

// Mapa (idéntico al proporcionado)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Estados del juego
typedef enum GameState {
    MENU,
    PLAYING,
    GAMEOVER
} GameState;

// Estructura para animaciones
struct Animation {
    int Frame;
    int Counter;
    int Speed;
} Spring, Enemy;

// Actualiza los frames de animación
void AnimationSettings() {
    Spring.Counter++;
    if (Spring.Counter >= (100 / Spring.Speed)) {
        Spring.Counter = 0;
        Spring.Frame++;
        if (Spring.Frame > 2) Spring.Frame = 0;
    }

    Enemy.Counter++;
    if (Enemy.Counter >= (100 / Enemy.Speed)) {
        Enemy.Counter = 0;
        Enemy.Frame++;
        if (Enemy.Frame > 2) Enemy.Frame = 0;
    }
}

// Reinicia todas las variables del juego
void ResetGame(float* playerX, float* playerY, float* velocityY, bool* isGrounded,
    float* enemyX, float* enemyY, bool* playerActive,
    int* direction, Camera2D* camera, int screenWidth, int screenHeight) {
    *playerX = 200.0f;
    *playerY = 0.0f;
    *velocityY = 0.0f;
    *isGrounded = false;
    *enemyX = (float)(screenWidth + 200);   // Aparece desde la derecha
    *enemyY = 0.0f;                         // Se ajustará al suelo más tarde
    *playerActive = true;
    *direction = 0;
    Spring.Frame = 0;
    Spring.Counter = 0;
    Enemy.Frame = 0;
    Enemy.Counter = 0;

    // Configurar cámara para seguir al jugador (centrado)
    camera->target = (Vector2){ *playerX + SPRING_WIDTH / 2, *playerY + SPRING_HEIGHT / 2 };
    camera->offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera->rotation = 0.0f;
    camera->zoom = 2.0f;
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "_C4STL3V4N14_");
    SearchAndSetResourceDir("resources");

    // ------------------ Carga de texturas -----------------
    Texture2D idleR = LoadTexture("Idle.png");
    Texture2D idleL = LoadTexture("Idle_Sided.png");
    Texture2D walkR = LoadTexture("Walking_R.png");
    Texture2D walkL = LoadTexture("Walking_L.png");
    Texture2D jumpR = LoadTexture("Jump_R.png");
    Texture2D jumpL = LoadTexture("Jump_L.png");
    Texture2D enemyTex = LoadTexture("Zombie_L.png");
    Texture2D fondo = LoadTexture("maapa.png");
    SetTextureFilter(fondo, TEXTURE_FILTER_POINT);

    // ------------------ Variables de estado -----------------
    GameState gameState = MENU;
    int menuSelection = 0;
    int gameOverSelection = 0;

    // ------------------ Variables del jugador -----------------
    float playerX, playerY;
    float velocityY = 0.0f;
    bool isGrounded = false;
    const float GRAVITY = 0.8f;
    const float JUMP_FORCE = -12.0f;
    const float MOVE_SPEED = 3.0f;
    int direction = 0;          // 0 = derecha, 1 = izquierda
    bool isMoving = false;
    bool playerActive = true;

    // ------------------ Variables del enemigo -----------------
    float enemyX, enemyY;
    float enemySpeed = 1.5f;

    // ------------------ Cámara -----------------
    Camera2D camera = { 0 };

    // Velocidades de animación
    Spring.Speed = 5;
    Enemy.Speed = 7;

    // Inicializar estado del juego
    ResetGame(&playerX, &playerY, &velocityY, &isGrounded,
        &enemyX, &enemyY, &playerActive, &direction,
        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);

    SetTargetFPS(60);

    // Bucle principal
    while (!WindowShouldClose()) {
        // ---------- Actualización según estado ----------
        switch (gameState) {
        case MENU: {
            if (IsKeyPressed(KEY_UP)) {
                menuSelection--;
                if (menuSelection < 0) menuSelection = 1;
            }
            if (IsKeyPressed(KEY_DOWN)) {
                menuSelection++;
                if (menuSelection > 1) menuSelection = 0;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                if (menuSelection == 0) {
                    gameState = PLAYING;
                    ResetGame(&playerX, &playerY, &velocityY, &isGrounded,
                        &enemyX, &enemyY, &playerActive, &direction,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                else if (menuSelection == 1) {
                    break;
                }
            }
            Vector2 mousePos = GetMousePosition();
            Rectangle playBtn = { SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f - 20, 100, 30 };
            Rectangle exitBtn = { SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f + 20, 100, 30 };
            if (CheckCollisionPointRec(mousePos, playBtn)) {
                menuSelection = 0;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    gameState = PLAYING;
                    ResetGame(&playerX, &playerY, &velocityY, &isGrounded,
                        &enemyX, &enemyY, &playerActive, &direction,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                menuSelection = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    break;
                }
            }
            break;
        }

        case PLAYING: {
            if (playerActive) {
                // ---------- Movimiento horizontal ----------
                float newX = playerX;
                isMoving = false;
                if (IsKeyDown(KEY_D)) {
                    newX += MOVE_SPEED;
                    direction = 0;
                    isMoving = true;
                }
                if (IsKeyDown(KEY_A)) {
                    newX -= MOVE_SPEED;
                    direction = 1;
                    isMoving = true;
                }

                // Colisión horizontal con tiles
                int topTile = (int)(playerY) / TILE_SIZE;
                int bottomTile = (int)(playerY + SPRING_HEIGHT - 1) / TILE_SIZE;
                // Derecha
                int rightTile = (int)(newX + SPRING_WIDTH) / TILE_SIZE;
                for (int y = topTile; y <= bottomTile; y++) {
                    if (map[y][rightTile] == 1) {
                        newX = rightTile * TILE_SIZE - SPRING_WIDTH;
                    }
                }
                // Izquierda
                int leftTile = (int)(newX) / TILE_SIZE;
                for (int y = topTile; y <= bottomTile; y++) {
                    if (map[y][leftTile] == 1) {
                        newX = (leftTile + 1) * TILE_SIZE;
                    }
                }
                playerX = newX;

                // ---------- Gravedad y salto ----------
                velocityY += GRAVITY;
                playerY += velocityY;

                // Colisión vertical con tiles (suelo)
                int tileX = (int)(playerX + SPRING_WIDTH / 2) / TILE_SIZE;
                int tileY = (int)(playerY + SPRING_HEIGHT) / TILE_SIZE;
                if (map[tileY][tileX] == 1) {
                    playerY = tileY * TILE_SIZE - SPRING_HEIGHT;
                    velocityY = 0;
                    isGrounded = true;
                }
                else {
                    isGrounded = false;
                }

                // Salto
                if (isGrounded && IsKeyPressed(KEY_SPACE)) {
                    velocityY = JUMP_FORCE;
                }

                // No salirse del mapa por la izquierda
                if (playerX < 0) playerX = 0;
            }

            // ---------- Movimiento del enemigo ----------
            enemyX -= enemySpeed;
            if (enemyX + SPRING_WIDTH < 0) {
                enemyX = SCREEN_WIDTH + 200;
            }

            // Ajustar altura del enemigo para que esté apoyado en el suelo
            int enemyTileX = (int)(enemyX + SPRING_WIDTH / 2) / TILE_SIZE;
            int enemyTileY = (int)(enemyY + SPRING_HEIGHT) / TILE_SIZE;
            for (int y = enemyTileY; y < MAP_HEIGHT; y++) {
                if (map[y][enemyTileX] == 1) {
                    enemyY = y * TILE_SIZE - SPRING_HEIGHT;
                    break;
                }
            }

            // ---------- Colisión jugador - enemigo ----------
            if (playerActive) {
                Rectangle playerRect = { playerX, playerY, SPRING_WIDTH, SPRING_HEIGHT };
                Rectangle enemyRect = { enemyX, enemyY, SPRING_WIDTH, SPRING_HEIGHT };
                if (CheckCollisionRecs(playerRect, enemyRect)) {
                    playerActive = false;
                    gameState = GAMEOVER;
                    gameOverSelection = 0;
                }
            }

            // Actualizar cámara (seguir al jugador)
            camera.target = (Vector2){ playerX + SPRING_WIDTH / 2, playerY + SPRING_HEIGHT / 2 };

            // Actualizar animaciones
            AnimationSettings();
            break;
        }

        case GAMEOVER: {
            if (IsKeyPressed(KEY_UP)) {
                gameOverSelection--;
                if (gameOverSelection < 0) gameOverSelection = 1;
            }
            if (IsKeyPressed(KEY_DOWN)) {
                gameOverSelection++;
                if (gameOverSelection > 1) gameOverSelection = 0;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                if (gameOverSelection == 0) {
                    gameState = PLAYING;
                    ResetGame(&playerX, &playerY, &velocityY, &isGrounded,
                        &enemyX, &enemyY, &playerActive, &direction,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                else if (gameOverSelection == 1) {
                    break;
                }
            }
            Vector2 mousePos = GetMousePosition();
            Rectangle tryAgainBtn = { SCREEN_WIDTH / 2.0f - 60, SCREEN_HEIGHT / 2.0f + 10, 120, 30 };
            Rectangle exitBtn = { SCREEN_WIDTH / 2.0f - 60, SCREEN_HEIGHT / 2.0f + 50, 120, 30 };
            if (CheckCollisionPointRec(mousePos, tryAgainBtn)) {
                gameOverSelection = 0;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    gameState = PLAYING;
                    ResetGame(&playerX, &playerY, &velocityY, &isGrounded,
                        &enemyX, &enemyY, &playerActive, &direction,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                gameOverSelection = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    break;
                }
            }
            break;
        }
        }

        // ---------- Dibujado ----------
        BeginDrawing();
        ClearBackground(BLACK);

        switch (gameState) {
        case MENU: {
            const char* title = "CASTLEVANIA";
            int titleFontSize = 30;
            int titleWidth = MeasureText(title, titleFontSize);
            DrawText(title, (SCREEN_WIDTH - titleWidth) / 2, SCREEN_HEIGHT / 2 - 80, titleFontSize, RED);
            const char* playText = "Play";
            const char* exitText = "Exit";
            int optionFontSize = 30;
            int playWidth = MeasureText(playText, optionFontSize);
            int exitWidth = MeasureText(exitText, optionFontSize);
            Color playColor = (menuSelection == 0) ? YELLOW : WHITE;
            Color exitColor = (menuSelection == 1) ? YELLOW : WHITE;
            DrawText(playText, (SCREEN_WIDTH - playWidth) / 2, SCREEN_HEIGHT / 2 - 20, optionFontSize, playColor);
            DrawText(exitText, (SCREEN_WIDTH - exitWidth) / 2, SCREEN_HEIGHT / 2 + 20, optionFontSize, exitColor);
            const char* instr = "Use ARROWS and ENTER or click";
            int instrFontSize = 15;
            int instrWidth = MeasureText(instr, instrFontSize);
            DrawText(instr, (SCREEN_WIDTH - instrWidth) / 2, SCREEN_HEIGHT - 40, instrFontSize, GRAY);
            break;
        }

        case PLAYING: {
            BeginMode2D(camera);

            // 1. Fondo lejano (maapa.png)
            DrawTextureEx(fondo, (Vector2) { 0, 0 }, 0, 2.0f, WHITE);

            // 2. Tiles del mapa (plataformas) – detrás de todo
            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    if (map[y][x] == 1) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
                    }
                }
            }

            // 3. Enemigo (zombie animado)
            Rectangle enemySource = { Enemy.Frame * SPRING_WIDTH, 0, SPRING_WIDTH, SPRING_HEIGHT };
            Rectangle enemyDest = { enemyX, enemyY, SPRING_WIDTH, SPRING_HEIGHT };
            DrawTexturePro(enemyTex, enemySource, enemyDest, (Vector2) { 0, 0 }, 0, WHITE);

            // 4. Jugador (si está activo) – encima de todo
            if (playerActive) {
                Rectangle source = { Spring.Frame * SPRING_WIDTH, 0, SPRING_WIDTH, SPRING_HEIGHT };
                Rectangle dest = { playerX, playerY, SPRING_WIDTH, SPRING_HEIGHT };

                if (!isGrounded) {  // Saltando/cayendo
                    if (direction == 0)
                        DrawTexturePro(jumpR, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
                    else
                        DrawTexturePro(jumpL, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
                }
                else if (isMoving) {
                    if (direction == 0)
                        DrawTexturePro(walkR, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
                    else
                        DrawTexturePro(walkL, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
                }
                else {
                    if (direction == 0)
                        DrawTextureEx(idleR, (Vector2) { playerX, playerY }, 0, 1, WHITE);
                    else
                        DrawTextureEx(idleL, (Vector2) { playerX, playerY }, 0, 1, WHITE);
                }
            }

            EndMode2D();

            // Texto en pantalla (fuera de la cámara)
            DrawText("You should KILL YOURSELF NOW!", 30, 100, 20, PURPLE);
            break;
        }

        case GAMEOVER: {
            const char* gameOverText = "GAME OVER";
            int goFontSize = 40;
            int goWidth = MeasureText(gameOverText, goFontSize);
            DrawText(gameOverText, (SCREEN_WIDTH - goWidth) / 2, SCREEN_HEIGHT / 2 - 60, goFontSize, RED);
            const char* tryAgainText = "Try Again";
            const char* exitText = "Exit";
            int optFontSize = 25;
            int tryAgainWidth = MeasureText(tryAgainText, optFontSize);
            int exitWidth = MeasureText(exitText, optFontSize);
            Color tryAgainColor = (gameOverSelection == 0) ? YELLOW : WHITE;
            Color exitColor = (gameOverSelection == 1) ? YELLOW : WHITE;
            DrawText(tryAgainText, (SCREEN_WIDTH - tryAgainWidth) / 2, SCREEN_HEIGHT / 2 + 10, optFontSize, tryAgainColor);
            DrawText(exitText, (SCREEN_WIDTH - exitWidth) / 2, SCREEN_HEIGHT / 2 + 50, optFontSize, exitColor);
            const char* instr = "Use ARROWS and ENTER or click";
            int instrFontSize = 15;
            int instrWidth = MeasureText(instr, instrFontSize);
            DrawText(instr, (SCREEN_WIDTH - instrWidth) / 2, SCREEN_HEIGHT - 40, instrFontSize, GRAY);
            break;
        }
        }

        EndDrawing();
    }

    // Liberar recursos
    UnloadTexture(idleR);
    UnloadTexture(idleL);
    UnloadTexture(walkR);
    UnloadTexture(walkL);
    UnloadTexture(jumpR);
    UnloadTexture(jumpL);
    UnloadTexture(enemyTex);
    UnloadTexture(fondo);
    CloseWindow();
    return 0;
}