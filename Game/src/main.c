#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "resource_dir.h"

// Dimensiones de la ventana
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450

// Tamaño real de los sprites (16x31)
#define SPRING_WIDTH  16
#define SPRING_HEIGHT 31

// Tamaño de los tiles
#define TILE_SIZE     34
#define MAP_WIDTH     250
#define MAP_HEIGHT    103

// Mapa
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

// Actualiza frames de animación (3 frames)
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

// Función auxiliar para obtener la altura del suelo en una posición X dada
float GetGroundHeight(float x) {
    int tileX = (int)(x + SPRING_WIDTH / 2) / TILE_SIZE;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (map[y][tileX] == 1) {
            return y * TILE_SIZE - SPRING_HEIGHT;
        }
    }
    return MAP_HEIGHT * TILE_SIZE - SPRING_HEIGHT; // Fondo del mapa
}

// Reinicia todas las variables del juego
void ResetGame(float* playerX, float* playerY, float* velocityY, bool* isGrounded,
    bool* canMove, bool* isJumping, int* jumpDirection,
    float* verticalSpeed, float* horizontalSpeed,
    float* enemyX, float* enemyY, bool* playerActive,
    int* direction, Camera2D* camera, int screenWidth, int screenHeight) {
    *playerX = 200.0f;
    // Colocar al jugador sobre el suelo en esa posición
    *playerY = GetGroundHeight(*playerX);
    *velocityY = 0.0f;
    *isGrounded = true;
    *canMove = true;
    *isJumping = false;
    *jumpDirection = 0;
    *verticalSpeed = 0.0f;
    *horizontalSpeed = 0.0f;
    *enemyX = (float)(screenWidth + 200);
    *enemyY = 0.0f;  // Se ajustará en el primer frame
    *playerActive = true;
    *direction = 0;
    Spring.Frame = 0;
    Spring.Counter = 0;
    Enemy.Frame = 0;
    Enemy.Counter = 0;

    // Cámara sigue al jugador (X variable, Y fija en 220)
    camera->target = (Vector2){ *playerX, 220 };
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
    float vX = 3.0f;                // Velocidad horizontal (constante)
    float G = 0.2f;                 // Gravedad
    bool canMove = true;
    bool isJumping = false;
    int jumpDirection = 0;          // 0 = arriba, -1 = izquierda, 1 = derecha
    float verticalSpeed = 0.0f;
    float initialJumpSpeed = -7.0f;
    float horizontalSpeed = 0.0f;
    int direction = 0;              // 0 = derecha, 1 = izquierda
    bool playerActive = true;

    float velocityY = 0.0f;         // Para compatibilidad con ResetGame
    bool isGrounded = false;

    // ------------------ Variables del enemigo -----------------
    float enemyX, enemyY;
    float enemySpeed = 2.0f;

    // ------------------ Cámara -----------------
    Camera2D camera = { 0 };

    // Velocidades de animación
    Spring.Speed = 6;
    Enemy.Speed = 7;

    // Inicializar estado del juego
    ResetGame(&playerX, &playerY, &velocityY, &isGrounded,
        &canMove, &isJumping, &jumpDirection,
        &verticalSpeed, &horizontalSpeed,
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
                        &canMove, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed,
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
                        &canMove, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed,
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
                // ----- Movimiento horizontal (suelo) -----
                if (canMove && !isJumping) {
                    float newX = playerX;
                    if (IsKeyDown(KEY_D)) {
                        newX += vX;
                        direction = 0;
                    }
                    else if (IsKeyDown(KEY_A)) {
                        newX -= vX;
                        direction = 1;
                    }

                    // Colisión horizontal
                    int topTile = (int)(playerY) / TILE_SIZE;
                    int bottomTile = (int)(playerY + SPRING_HEIGHT - 1) / TILE_SIZE;
                    if (newX > playerX) { // Derecha
                        int rightTile = (int)(newX + SPRING_WIDTH) / TILE_SIZE;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (map[ty][rightTile] == 1) {
                                newX = rightTile * TILE_SIZE - SPRING_WIDTH;
                                break;
                            }
                        }
                    }
                    else if (newX < playerX) { // Izquierda
                        int leftTile = (int)(newX) / TILE_SIZE;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (map[ty][leftTile] == 1) {
                                newX = (leftTile + 1) * TILE_SIZE;
                                break;
                            }
                        }
                    }
                    playerX = newX;

                    // Aplicar gravedad
                    playerY += G;
                    // Colisión vertical (suelo)
                    int tileX = (int)(playerX + SPRING_WIDTH / 2) / TILE_SIZE;
                    int tileY = (int)(playerY + SPRING_HEIGHT) / TILE_SIZE;
                    if (map[tileY][tileX] == 1) {
                        playerY = tileY * TILE_SIZE - SPRING_HEIGHT;
                        isGrounded = true;
                    }
                    else {
                        isGrounded = false;
                    }
                }

                // ----- Salto -----
                if (canMove && !isJumping) {
                    if (IsKeyPressed(KEY_SPACE)) {
                        isJumping = true;
                        canMove = false;
                        verticalSpeed = initialJumpSpeed;

                        // Dirección del salto según input
                        if (IsKeyDown(KEY_D)) {
                            jumpDirection = 1;
                            direction = 0;
                            horizontalSpeed = vX;
                        }
                        else if (IsKeyDown(KEY_A)) {
                            jumpDirection = -1;
                            direction = 1;
                            horizontalSpeed = -vX;
                        }
                        else {
                            jumpDirection = 0;
                            horizontalSpeed = 0.0f;
                        }
                    }
                }

                // ----- Física del salto -----
                if (isJumping) {
                    verticalSpeed += G;
                    playerY += verticalSpeed;

                    // Movimiento horizontal constante durante el salto
                    float newX = playerX + horizontalSpeed;
                    // Colisión horizontal en el aire
                    int topTile = (int)(playerY) / TILE_SIZE;
                    int bottomTile = (int)(playerY + SPRING_HEIGHT - 1) / TILE_SIZE;
                    if (horizontalSpeed > 0) {
                        int rightTile = (int)(newX + SPRING_WIDTH) / TILE_SIZE;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (map[ty][rightTile] == 1) {
                                newX = rightTile * TILE_SIZE - SPRING_WIDTH;
                                horizontalSpeed = 0; // chocamos con pared
                                break;
                            }
                        }
                    }
                    else if (horizontalSpeed < 0) {
                        int leftTile = (int)(newX) / TILE_SIZE;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (map[ty][leftTile] == 1) {
                                newX = (leftTile + 1) * TILE_SIZE;
                                horizontalSpeed = 0;
                                break;
                            }
                        }
                    }
                    playerX = newX;

                    // Colisión con el suelo durante el salto
                    int tileX = (int)(playerX + SPRING_WIDTH / 2) / TILE_SIZE;
                    int tileY = (int)(playerY + SPRING_HEIGHT) / TILE_SIZE;
                    if (map[tileY][tileX] == 1) {
                        playerY = tileY * TILE_SIZE - SPRING_HEIGHT;
                        isJumping = false;
                        canMove = true;
                        verticalSpeed = 0;
                        jumpDirection = 0;
                        horizontalSpeed = 0;
                        isGrounded = true;
                    }

                    // Colisión con el techo
                    int headTileY = (int)(playerY) / TILE_SIZE;
                    if (map[headTileY][tileX] == 1) {
                        playerY = (headTileY + 1) * TILE_SIZE;
                        verticalSpeed = 0;
                    }

                    if (playerY < 0) {
                        playerY = 0;
                        verticalSpeed = 0;
                    }
                }

                // Límite izquierdo
                if (playerX < 0) playerX = 0;
            }

            // ---------- Movimiento del enemigo ----------
            enemyX -= enemySpeed;
            if (enemyX + SPRING_WIDTH < 0) {
                enemyX = SCREEN_WIDTH + 200;
            }

            // Ajustar altura del enemigo al suelo
            int enemyTileX = (int)(enemyX + SPRING_WIDTH / 2) / TILE_SIZE;
            for (int y = 0; y < MAP_HEIGHT; y++) {
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

            // Actualizar cámara (sigue en X, Y fija en 220)
            camera.target = (Vector2){ playerX, 220 };

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
                        &canMove, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed,
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
                        &canMove, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed,
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

            // Fondo
            DrawTextureEx(fondo, (Vector2) { 0, 0 }, 0, 2.0f, WHITE);

            // Tiles del mapa
            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    if (map[y][x] == 1) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
                    }
                }
            }

            // Enemigo
            Rectangle enemySource = { Enemy.Frame * SPRING_WIDTH, 0, SPRING_WIDTH, SPRING_HEIGHT };
            Rectangle enemyDest = { enemyX, enemyY, SPRING_WIDTH, SPRING_HEIGHT };
            DrawTexturePro(enemyTex, enemySource, enemyDest, (Vector2) { 0, 0 }, 0, WHITE);

            // Jugador
            if (playerActive) {
                Rectangle source = { Spring.Frame * SPRING_WIDTH, 0, SPRING_WIDTH, SPRING_HEIGHT };
                Rectangle dest = { playerX, playerY, SPRING_WIDTH, SPRING_HEIGHT };

                if (isJumping) {
                    if (direction == 0)
                        DrawTexturePro(jumpR, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
                    else
                        DrawTexturePro(jumpL, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
                }
                else if (canMove && (IsKeyDown(KEY_D) || IsKeyDown(KEY_A))) {
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
#define Spring_Width 72 //16
#define Spring_Height 32
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

// Structure for animation frames
struct Animation
{
	int Frame /*= 0*/;
	int Counter /*= 0*/;
	int Speed /*= 5*/;
} Spring, Attacker;



// Function to handle animation frame cycling
void AnimationSettings()
{
	Spring.Counter++;
	if (Spring.Counter >= (100/ Spring.Speed))
	{
		Spring.Counter = 0;
		Spring.Frame++;

		if (Spring.Frame > 2) Spring.Frame = 0;
	}
	
	Attacker.Counter++;
	if (Attacker.Counter >= (100 / Attacker.Speed))
	{
		Attacker.Counter = 0;
		Attacker.Frame++;
		if (Attacker.Frame > 5) Attacker.Frame = 0;
	}
}


int main()
{
	//------------------Miscellaneous--------------------
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	float x = 0;
	float vX = 1;  // Velocidad de movimiento horizontal constante
	float y = 10;
	Spring.Speed = 5;
	Attacker.Speed = 5;

	bool Direction = 0;  // 0 = mirando derecha, 1 = mirando izquierda
	x = 200;
	y = 175;

	float G = 0.1f;  // Gravedad reducida para ca�da m�s lenta y salto m�s alto
	int Floor = 200;
	bool canMove = true;  // Puede moverse? (true = puede moverse, false = en el aire/saltando)

	// Variables de salto
	bool isJumping = false;      // Indica si el jugador est� en el aire
	int jumpDirection = 0;       // 0 = arriba, -1 = izquierda, 1 = derecha
	float verticalSpeed = 0;     // Velocidad vertical actual
	float initialJumpSpeed = -6.0f;  // Velocidad inicial para salto alto

	// Variables para el movimiento horizontal durante el salto
	int startX = 0;              // Posici�n X cuando comenz� el salto
	float horizontalSpeed = 0;   // Velocidad horizontal durante el salto (igual que vX)

	bool Attack = false;

	//---------------------------------------------------

	//------------------Window--------------------
	int screenWidth = 400; //X
	int screenHeight = 350; //Y

	InitWindow(screenWidth, screenHeight, "_C4STL3V4N14_");
	//---------------------------------------------

	//------------------Textures--------------------
	SearchAndSetResourceDir("resources"); // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it

	Texture Rabbit = LoadTexture("Idle.png");
	Texture Rabbit_O = LoadTexture("Idle_Sided.png");

	Texture AnimR = LoadTexture("Walking_R.png");
	Texture AnimL = LoadTexture("Walking_L.png");

	Texture JumpR = LoadTexture("Jumper.png");
	Texture JumpL = LoadTexture("Jump_L.png");

	Texture DuckR = LoadTexture("Crouch_R.png");
	Texture DuckL = LoadTexture("Crouch_L.png");

	Texture AttackR1 = LoadTexture("Attack_R.png");
	Texture AttackL1 = LoadTexture("Attack_L - Rework.png");

	Texture AttackR1_Crouch = LoadTexture("C_A_R.png");
	Texture AttackL1_Crouch = LoadTexture("C_A_L.png");

	//-----------------------------------------------

	//------------------Gameplay Loop--------------------
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		//------------------Camera--------------------

		//--------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("You should KILL YOURSELF NOW!", 30, 100, 20, PURPLE);

		//------------------Player Movement--------------------

		// Manejar el salto
		if (canMove && !isJumping)
		{
			// Verificar si se presiona W para saltar
			if (IsKeyPressed(KEY_SPACE))
			{
				isJumping = true;
				canMove = false;
				verticalSpeed = initialJumpSpeed;
				startX = x;

				// Determinar direcci�n y velocidad horizontal del salto
				if (IsKeyDown(KEY_D))
				{
					jumpDirection = 1;  // Saltar derecha
					Direction = 0;
					horizontalSpeed = vX + 1.5;  // Misma velocidad que caminando
				}
				else if (IsKeyDown(KEY_A))
				{
					jumpDirection = -1;  // Saltar izquierda
					Direction = 1;
					horizontalSpeed = vX + 1.5;  // Misma velocidad que caminando
				}
				else
				{
					jumpDirection = 0;  // Saltar recto
					horizontalSpeed = 0;
				}
			}
		}

		// F�sica del salto
		if (isJumping)
		{
			// Actualizar velocidad vertical con gravedad
			verticalSpeed += G + 0.02;
			y += (float)verticalSpeed;

			// Movimiento horizontal DURANTE EL SALTO - MANTIENE LA MISMA VELOCIDAD QUE EN EL SUELO
			if (jumpDirection == 1)
			{
				// Moverse hacia la derecha a la misma velocidad que caminando
				x += (float)horizontalSpeed;
			}
			else if (jumpDirection == -1)
			{
				// Moverse hacia la izquierda a la misma velocidad que caminando
				x -= (float)horizontalSpeed;
			}

			// Verificar si ha llegado al suelo
			if (y >= Floor)
			{
				y = Floor;
				isJumping = false;
				canMove = true;
				verticalSpeed = 0;
				jumpDirection = 0;
				horizontalSpeed = 0;
			}

			// Evitar que pase el techo
			if (y < 0)
			{
				y = 0;
				verticalSpeed = 0;
			}
		}

		// Movimiento en el suelo
		if (canMove && !isJumping)
		{
			// Aplicar gravedad para caer de plataformas
			y = y + (float)G;

			// Movimiento horizontal (velocidad vX)
			if (IsKeyDown(KEY_D))
			{
				x = x + vX;
				Direction = 0;
			}
			else if (IsKeyDown(KEY_A))
			{
				x = x - vX;
				Direction = 1;
			}

			// Colisi�n con el suelo
			if (y >= Floor)
			{
				y = Floor;
			}
		}

		// L�mites de la pantalla
		if (x > screenWidth - 15) x = screenWidth - 15;
		if (x < -5) x = -5;
		if (y > screenHeight - 100) y = screenHeight - 100;

		//------------------Dibujado de Sprites--------------------

		// Dibujar animaci�n cuando est� en movimiento en el suelo
		if (canMove && !isJumping && (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)))
		{
			AnimationSettings();
			if (IsKeyDown(KEY_D))
			{
				Rectangle source = (Rectangle){ Spring.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
				Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
				DrawTexturePro(AnimR, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
			}
			else if (IsKeyDown(KEY_A))
			{
				Rectangle source = (Rectangle){ Spring.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
				Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
				DrawTexturePro(AnimL, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
			}
		}
		// Dibujar sprite est�tico cuando est� quieto en el suelo
		else if (canMove && !isJumping)
		{
			if (Direction == 0)
			{
				DrawTexture(Rabbit, x, y, WHITE);
			}
			else
			{
				DrawTexture(Rabbit_O, x, y, WHITE);
			}

		}
		// Dibujar sprite durante el salto
		else if (isJumping)
		{
			AnimationSettings();
			if (Direction == 0)
			{
				Rectangle source = (Rectangle){ Spring.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
				Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
				DrawTexturePro(JumpR, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
			}
			else
			{
				Rectangle source = (Rectangle){ Spring.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
				Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
				DrawTexturePro(JumpL, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
			}
		}

		// Dibujar sprite de agachar y cancelar movimiento
		if (!isJumping)
		{
			if (Direction == 0 && IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_E))
			{
				canMove = false;
				Rectangle source = (Rectangle){ Spring.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
				Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
				DrawTexturePro(DuckR, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
			}
			else if (IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_E))
			{
				canMove = false;
				Rectangle source = (Rectangle){ Spring.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
				Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
				DrawTexturePro(DuckL, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
			}
			if (IsKeyUp(KEY_LEFT_SHIFT))
			{
				canMove = true;
			}
		}

		//Dibujar Ataque Light
		if (!isJumping)
		{
			if (Direction == 0 && IsKeyDown(KEY_E))
			{
				if (IsKeyDown(KEY_LEFT_SHIFT))
				{
					AnimationSettings();
					canMove = false;
					Rectangle source = (Rectangle){ Attacker.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
					Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
					DrawTexturePro(AttackR1_Crouch, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
				}
				else
				{
					AnimationSettings();
					canMove = false;
					Rectangle source = (Rectangle){ Attacker.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
					Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
					DrawTexturePro(AttackR1, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
				}
			}
			else if (IsKeyDown(KEY_E))
			{
				if (IsKeyDown(KEY_LEFT_SHIFT))
				{
					AnimationSettings();
					canMove = false;
					Rectangle source = (Rectangle){ Attacker.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
					Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
					DrawTexturePro(AttackL1_Crouch, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
				}
				else
				{
					AnimationSettings();
					canMove = false;
					Rectangle source = (Rectangle){ Attacker.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
					Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
					DrawTexturePro(AttackL1, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
				}
			}
		}

		// Dibujar el suelo
		DrawRectangle(0, 233, screenWidth, 10, WHITE);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}
	//---------------------------------------------------


	//-----------------Cleanup-----------------

	// unload our texture so it can be cleaned up
	UnloadTexture(Rabbit);
	UnloadTexture(Rabbit_O);

	UnloadTexture(AnimL);
	UnloadTexture(AnimR);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}