#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "resource_dir.h"

// Dimensiones de la ventana
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450

// Tamaños del sprite del jugador (ancho completo, incluye transparencia)
#define PLAYER_SPRITE_WIDTH  72
#define PLAYER_SPRITE_HEIGHT 32

// Hitbox real del jugador (más pequeña, solo la parte sólida)
#define PLAYER_HITBOX_WIDTH  24
#define PLAYER_HITBOX_HEIGHT 32

#define ATTACK_HITBOX_WIDTH  40
#define ATTACK_HITBOX_HEIGHT 18

// Tamaños del enemigo
#define ENEMY_WIDTH   16
#define ENEMY_HEIGHT  31

// Item 
#define ITEM_WIDTH   72
#define ITEM_HEIGHT  32

// Tamaño de los tiles
#define TILE_SIZE     34
#define MAP_WIDTH     250
#define MAP_HEIGHT    12   // Ajustado a las filas reales definidas en map[][]


// Mapa (12 filas de alto, 250 columnas de ancho)
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
    GAMEOVER,
    WIN,
    EXIT
} GameState;

// Estructura para animaciones (personaje y enemigo)
struct Animation {
    int Frame;
    int Counter;
    int Speed;
} Spring, Enemy;

// Estructura para animaciones de ataque (6 frames)
struct AttackAnimation {
    int Frame;
    int Counter;
    int Speed;
} Attacker;

// Actualiza frames de animación
void AnimationSettings() {
    // Animación del personaje (caminar, saltar) - 3 frames
    Spring.Counter++;
    if (Spring.Counter >= (100 / Spring.Speed)) {
        Spring.Counter = 0;
        Spring.Frame++;
        if (Spring.Frame > 2) Spring.Frame = 0;
    }

    // Animación del enemigo - 3 frames
    Enemy.Counter++;
    if (Enemy.Counter >= (100 / Enemy.Speed)) {
        Enemy.Counter = 0;
        Enemy.Frame++;
        if (Enemy.Frame > 2) Enemy.Frame = 0;
    }
    
    if (IsKeyDown(KEY_E))
    {
        // Animación de ataque - 6 frames (0 a 5)
        Attacker.Counter++;
        if (Attacker.Counter >= (100 / Attacker.Speed)) {
            Attacker.Counter = 0;
            Attacker.Frame++;
            if (Attacker.Frame > 5) Attacker.Frame = 0;
        }
    }
    else
        Attacker.Frame = 0;
}

// Obtener altura del suelo para una posición X (usando la hitbox real del jugador)
float GetGroundHeight(float x) {
    int tileX = (int)(x + PLAYER_HITBOX_WIDTH / 2) / TILE_SIZE;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (map[y][tileX] == 1) {
            return y * TILE_SIZE - PLAYER_HITBOX_HEIGHT;
        }
    }
    return MAP_HEIGHT * TILE_SIZE - PLAYER_HITBOX_HEIGHT;
}

// Obtener altura del suelo para el enemigo
float GetEnemyGroundHeight(float x) {
    int tileX = (int)(x + ENEMY_WIDTH / 2) / TILE_SIZE;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (map[y][tileX] == 1) {
            return y * TILE_SIZE - ENEMY_HEIGHT;
        }
    }
    return MAP_HEIGHT * TILE_SIZE - ENEMY_HEIGHT;
}

// Reinicia todas las variables del juego
void ResetGame(float* playerX, float* playerY, float* velocityY, bool* isGrounded,
    bool* canMove, bool* isJumping, int* jumpDirection,
    float* verticalSpeed, float* horizontalSpeed,
    float* enemyX, float* enemyY, bool* playerActive,
    int* direction, bool* isDucking, bool* isAttacking,
    Camera2D* camera, int screenWidth, int screenHeight) {
    *playerX = 200.0f;
    *playerY = GetGroundHeight(*playerX);
    *velocityY = 0.0f;
    *isGrounded = true;
    *canMove = true;
    *isJumping = false;
    *jumpDirection = 0;
    *verticalSpeed = 0.0f;
    *horizontalSpeed = 0.0f;

    // Enemigo aparece 800 píxeles por delante del jugador
    *enemyX = *playerX + 800.0f;
    // Asegurar que no se salga del mapa
    if (*enemyX + ENEMY_WIDTH > MAP_WIDTH * TILE_SIZE) {
        *enemyX = MAP_WIDTH * TILE_SIZE - ENEMY_WIDTH;
    }
    *enemyY = GetEnemyGroundHeight(*enemyX);
    *playerActive = true;
    *direction = 0;
    *isDucking = false;
    *isAttacking = false;
    Spring.Frame = 0;
    Spring.Counter = 0;
    Enemy.Frame = 0;
    Enemy.Counter = 0;
    Attacker.Frame = 0;
    Attacker.Counter = 0;

    // Cámara centrada en el jugador (Y fija en 290)
    camera->target = (Vector2){ *playerX + PLAYER_HITBOX_WIDTH / 2, 290.0f };
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
    Texture2D jumpR = LoadTexture("Jumper.png");
    Texture2D jumpL = LoadTexture("Jump_L.png");
    Texture2D duckR = LoadTexture("Crouch_R.png");
    Texture2D duckL = LoadTexture("Crouch_L.png");
    Texture2D attackR = LoadTexture("Attack_R.png");
    Texture2D attackL = LoadTexture("Attack_L - Rework.png");
    Texture2D attackR_C = LoadTexture("C_A_R.png");
    Texture2D attackL_C = LoadTexture("C_A_L.png");
    Texture2D enemyTex = LoadTexture("Zombie_L.png");
    Texture2D fondo = LoadTexture("maapa.png");
    Texture2D Weapon2 = LoadTexture("Item_Placeholder.png");
    Texture2D Item1 = LoadTexture("Item_Image1.png");
    Texture2D Item2 = LoadTexture("Item_Image2.png");

    SetTextureFilter(fondo, TEXTURE_FILTER_POINT);

    // ------------------ Variables de estado -----------------
    GameState gameState = MENU;
    int menuSelection = 0;
    int gameOverSelection = 0;
    int winSelection = 0;       // 0 = Return to Menu, 1 = Exit

    // ------------------ Variables del jugador -----------------
    float playerX, playerY;
    float vX = 3.0f;
    float G = 0.2f;
    bool canMove = true;
    bool isJumping = false;
    int jumpDirection = 0;
    float verticalSpeed = 0.0f;
    float initialJumpSpeed = -7.0f;
    float horizontalSpeed = 0.0f;
    int direction = 0;              // 0 = derecha, 1 = izquierda
    bool playerActive = true;
    bool isDucking = false;
    bool isAttacking = false;

    float velocityY = 0.0f;
    bool isGrounded = false;

    // ------------------ Variables del enemigo -----------------
    float enemyX, enemyY;
    float enemySpeed = 2.0f;

    // ------------------ [ITEMS] -----------------
    bool Whip = true;
    bool Star = false;
    bool CollectStar = false;
    // ------------------ Cámara -----------------
    Camera2D camera = { 0 };

    // Velocidades de animación
    Spring.Speed = 6;
    Enemy.Speed = 7;
    Attacker.Speed = 10;

    // Inicializar estado del juego
    ResetGame(&playerX, &playerY, &velocityY, &isGrounded,
        &canMove, &isJumping, &jumpDirection,
        &verticalSpeed, &horizontalSpeed,
        &enemyX, &enemyY, &playerActive, &direction,
        &isDucking, &isAttacking,
        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);

    SetTargetFPS(60);

    bool CloseIt = false;

    // Bucle principal
    while (CloseIt == 0 && !WindowShouldClose()) {
        // Actualizar animaciones (se hace siempre durante el juego)
        if (gameState == PLAYING) {
            AnimationSettings();
        }

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
                        &isDucking, &isAttacking,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                else if (menuSelection == 1) {
                    gameState = EXIT;
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
                        &isDucking, &isAttacking,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                menuSelection = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    gameState = EXIT;
                }
            }
            break;
        }
      
        case EXIT:
        {
            CloseIt = true;
        }

        case PLAYING: {
            // Determinar estados de agacharse y atacar (solo en suelo, no saltando)
            bool duckKey = IsKeyDown(KEY_LEFT_SHIFT);
            bool attackKey = IsKeyDown(KEY_E);
            isDucking = false;
            isAttacking = false;

            if (!isJumping) {
                if (attackKey) {
                    AnimationSettings();
                    isAttacking = true;
                    canMove = false;
                }
                else if (duckKey) {
                    isDucking = true;
                    canMove = false;
                }
                else {
                    canMove = true;
                }
            }

            if (playerActive) {
                // Movimiento horizontal (suelo)
                if (canMove && !isJumping && !isAttacking && !isDucking) {
                    float newX = playerX;
                    if (IsKeyDown(KEY_D)) {
                        newX += vX;
                        direction = 0;
                    }
                    else if (IsKeyDown(KEY_A)) {
                        newX -= vX;
                        direction = 1;
                    }

                    // Colisión horizontal con la hitbox reducida
                    int topTile = (int)(playerY) / TILE_SIZE;
                    int bottomTile = (int)(playerY + PLAYER_HITBOX_HEIGHT - 1) / TILE_SIZE;
                    if (newX > playerX) {
                        int rightTile = (int)(newX + PLAYER_HITBOX_WIDTH) / TILE_SIZE;
                        if (rightTile >= MAP_WIDTH) rightTile = MAP_WIDTH - 1;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (map[ty][rightTile] == 1) {
                                newX = rightTile * TILE_SIZE - PLAYER_HITBOX_WIDTH;
                                break;
                            }
                        }
                    }
                    else if (newX < playerX) {
                        int leftTile = (int)(newX) / TILE_SIZE;
                        if (leftTile < 0) leftTile = 0;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (map[ty][leftTile] == 1) {
                                newX = (leftTile + 1) * TILE_SIZE;
                                break;
                            }
                        }
                    }
                    playerX = newX;

                    // Gravedad
                    playerY += G;
                    int tileX = (int)(playerX + PLAYER_HITBOX_WIDTH / 2) / TILE_SIZE;
                    int tileY = (int)(playerY + PLAYER_HITBOX_HEIGHT) / TILE_SIZE;
                    if (tileY >= MAP_HEIGHT) tileY = MAP_HEIGHT - 1;
                    if (map[tileY][tileX] == 1) {
                        playerY = tileY * TILE_SIZE - PLAYER_HITBOX_HEIGHT;
                        isGrounded = true;
                    }
                    else {
                        isGrounded = false;
                    }
                }

                // Salto
                if (canMove && !isJumping && !isAttacking && !isDucking) {
                    if (IsKeyPressed(KEY_SPACE)) {
                        isJumping = true;
                        canMove = false;
                        verticalSpeed = initialJumpSpeed;

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

                // Física del salto
                if (isJumping) {
                    verticalSpeed += G;
                    playerY += verticalSpeed;

                    float newX = playerX + horizontalSpeed;
                    int topTile = (int)(playerY) / TILE_SIZE;
                    int bottomTile = (int)(playerY + PLAYER_HITBOX_HEIGHT - 1) / TILE_SIZE;
                    if (horizontalSpeed > 0) {
                        int rightTile = (int)(newX + PLAYER_HITBOX_WIDTH) / TILE_SIZE;
                        if (rightTile >= MAP_WIDTH) rightTile = MAP_WIDTH - 1;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (map[ty][rightTile] == 1) {
                                newX = rightTile * TILE_SIZE - PLAYER_HITBOX_WIDTH;
                                horizontalSpeed = 0;
                                break;
                            }
                        }
                    }
                    else if (horizontalSpeed < 0) {
                        int leftTile = (int)(newX) / TILE_SIZE;
                        if (leftTile < 0) leftTile = 0;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (map[ty][leftTile] == 1) {
                                newX = (leftTile + 1) * TILE_SIZE;
                                horizontalSpeed = 0;
                                break;
                            }
                        }
                    }
                    playerX = newX;

                    int tileX = (int)(playerX + PLAYER_HITBOX_WIDTH / 2) / TILE_SIZE;
                    int tileY = (int)(playerY + PLAYER_HITBOX_HEIGHT) / TILE_SIZE;
                    if (tileY >= MAP_HEIGHT) tileY = MAP_HEIGHT - 1;
                    if (map[tileY][tileX] == 1) {
                        playerY = tileY * TILE_SIZE - PLAYER_HITBOX_HEIGHT;
                        isJumping = false;
                        canMove = true;
                        verticalSpeed = 0;
                        jumpDirection = 0;
                        horizontalSpeed = 0;
                        isGrounded = true;
                    }

                    int headTileY = (int)(playerY) / TILE_SIZE;
                    if (headTileY >= MAP_HEIGHT) headTileY = MAP_HEIGHT - 1;
                    if (map[headTileY][tileX] == 1) {
                        playerY = (headTileY + 1) * TILE_SIZE;
                        verticalSpeed = 0;
                    }

                    if (playerY < 0) {
                        playerY = 0;
                        verticalSpeed = 0;
                    }
                }

                if (playerX < 0) playerX = 0;

                // ----- DETECCIÓN DE VICTORIA (CON TOLERANCIA) -----
                // Se activa cuando la hitbox del jugador toca (o casi toca) la pared derecha.
                // La pared derecha está en la columna MAP_WIDTH-1.
                float victoryThreshold = (MAP_WIDTH - 1) * TILE_SIZE - 1.0f; // 1 píxel de margen
                if (playerX + PLAYER_HITBOX_WIDTH >= victoryThreshold) {
                    gameState = WIN;
                    winSelection = 0;
                }
            }

            // ----- COMPORTAMIENTO DEL ENEMIGO -----
            // Movimiento hacia la izquierda
            enemyX -= enemySpeed;

            // Si el enemigo está 800 px a la izquierda del jugador, lo recolocamos 800 px a la derecha
            if (playerX - enemyX >= 800.0f) {
                enemyX = playerX + 800.0f;
                // Asegurar que no se salga del mapa por la derecha
                if (enemyX + ENEMY_WIDTH > MAP_WIDTH * TILE_SIZE) {
                    enemyX = MAP_WIDTH * TILE_SIZE - ENEMY_WIDTH;
                }
            }

            // Ajustar altura del enemigo al suelo
            enemyY = GetEnemyGroundHeight(enemyX);

            // Colisión jugador - enemigo (usando hitbox reducida del jugador)
            if (playerActive) 
            {
                Rectangle playerHitbox = { playerX, playerY, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT };
                Rectangle enemyRect = { enemyX, enemyY, ENEMY_WIDTH, ENEMY_HEIGHT };
                Rectangle attackHitbox = { playerX, playerY, ATTACK_HITBOX_WIDTH, ATTACK_HITBOX_HEIGHT };
                if (attackKey)
                {
                    if (CheckCollisionRecs(attackHitbox, enemyRect))
                    {
                        enemyX = playerX + 800;
                    }
                }
                if (CheckCollisionRecs(playerHitbox, enemyRect)) 
                {
                    playerActive = false;
                    gameState = GAMEOVER;
                    gameOverSelection = 0;
                }
            }

            // Actualizar cámara (centrada en el jugador)
            camera.target = (Vector2){ playerX + PLAYER_HITBOX_WIDTH / 2, 290.0f };
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
                        &isDucking, &isAttacking,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                else if (gameOverSelection == 1) {
                    gameState = EXIT;
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
                        &isDucking, &isAttacking,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                gameOverSelection = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    gameState = EXIT;
                }
            }
            break;
        }

        case WIN: {
            if (IsKeyPressed(KEY_UP)) {
                winSelection--;
                if (winSelection < 0) winSelection = 1;
            }
            if (IsKeyPressed(KEY_DOWN)) {
                winSelection++;
                if (winSelection > 1) winSelection = 0;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                if (winSelection == 0) {
                    gameState = MENU;
                    menuSelection = 0;
                }
                else if (winSelection == 1) {
                    break;
                }
            }
            Vector2 mousePos = GetMousePosition();
            Rectangle menuBtn = { SCREEN_WIDTH / 2.0f - 80, SCREEN_HEIGHT / 2.0f + 10, 160, 30 };
            Rectangle exitBtn = { SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f + 50, 100, 30 };
            if (CheckCollisionPointRec(mousePos, menuBtn)) {
                winSelection = 0;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    gameState = MENU;
                    menuSelection = 0;
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                winSelection = 1;
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

            DrawTextureEx(fondo, (Vector2) { 0, 0 }, 0, 2.0f, WHITE);

            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    if (map[y][x] == 1) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
                    }
                }
            }

            // Dibujar enemigo
            Rectangle enemySource = { Enemy.Frame * 17, 0, ENEMY_WIDTH, ENEMY_HEIGHT };
            Rectangle enemyDest = { enemyX, enemyY, ENEMY_WIDTH, ENEMY_HEIGHT };
            DrawTexturePro(enemyTex, enemySource, enemyDest, (Vector2) { 0, 0 }, 0, WHITE);

            if (playerActive) {
                Rectangle source;
                float spriteOffsetX = (PLAYER_SPRITE_WIDTH - PLAYER_HITBOX_WIDTH) / 2.0f;
                Rectangle dest = {
                    playerX - spriteOffsetX,
                    playerY,
                    PLAYER_SPRITE_WIDTH,
                    PLAYER_SPRITE_HEIGHT
                };
                Texture2D textureToDraw;
                bool usePro = true;

                bool attackDucking = isAttacking && IsKeyDown(KEY_LEFT_SHIFT);

                if (isAttacking) {
                    source = (Rectangle){ Attacker.Frame * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                    if (attackDucking) {
                        textureToDraw = (direction == 0) ? attackR_C : attackL_C;
                    }
                    else {
                        textureToDraw = (direction == 0) ? attackR : attackL;
                    }
                }
                else if (isDucking) {
                    source = (Rectangle){ Spring.Frame * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                    textureToDraw = (direction == 0) ? duckR : duckL;
                }
                else if (isJumping) {
                    source = (Rectangle){ Spring.Frame * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                    textureToDraw = (direction == 0) ? jumpR : jumpL;
                }
                else if (canMove && (IsKeyDown(KEY_D) || IsKeyDown(KEY_A))) {
                    source = (Rectangle){ Spring.Frame * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                    textureToDraw = (direction == 0) ? walkR : walkL;
                }
                else {
                    usePro = false;
                    if (direction == 0)
                        DrawTextureEx(idleR, (Vector2) { dest.x, dest.y }, 0, 1, WHITE);
                    else
                        DrawTextureEx(idleL, (Vector2) { dest.x, dest.y }, 0, 1, WHITE);
                }

                if (usePro) {
                    DrawTexturePro(textureToDraw, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
                }
            }

            //Item Frame
            if (IsKeyPressed(KEY_ONE))
            {
                Whip = true;
                Star = false;
            }
            if (CollectStar && IsKeyPressed(KEY_TWO))
            {
                Whip = false;
                Star = true;
            }
            while (Whip)
            {
                DrawTextureEx(Item1, (Vector2) { 250 + playerX, 400 }, 0, 1, WHITE);
            }
            while (Star)
            {
                DrawTextureEx(Item2, (Vector2) { 250 + playerX, 400 }, 0, 1, WHITE);
            }
            

            //Dibujar Arma 02

            while (CollectStar == false)
            {
                Rectangle playerHitbo = { playerX, playerY, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT };
                Rectangle StarHitbox = { 400, 342, ITEM_WIDTH, ITEM_HEIGHT };
                DrawTextureEx(Weapon2, (Vector2) { 400, 342 }, 0, 1, WHITE);
                if (CheckCollisionRecs(playerHitbo, StarHitbox))
                {
                    CollectStar = true;
                }
            }

            
           
            

            // Indicadores visuales de depuración (puedes comentarlos si no los necesitas)
            DrawLine(MAP_WIDTH * TILE_SIZE, 0, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, WHITE);
            DrawRectangle((MAP_WIDTH - 1) * TILE_SIZE, 0, TILE_SIZE, MAP_HEIGHT * TILE_SIZE, (Color) { 255, 0, 0, 100 });

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

        case WIN: {
            const char* winText = "LEVEL WIN";
            int winFontSize = 40;
            int winWidth = MeasureText(winText, winFontSize);
            DrawText(winText, (SCREEN_WIDTH - winWidth) / 2, SCREEN_HEIGHT / 2 - 60, winFontSize, GREEN);
            const char* menuText = "Return to Menu";
            const char* exitText = "Exit";
            int optFontSize = 25;
            int menuWidth = MeasureText(menuText, optFontSize);
            int exitWidth = MeasureText(exitText, optFontSize);
            Color menuColor = (winSelection == 0) ? YELLOW : WHITE;
            Color exitColor = (winSelection == 1) ? YELLOW : WHITE;
            DrawText(menuText, (SCREEN_WIDTH - menuWidth) / 2, SCREEN_HEIGHT / 2 + 10, optFontSize, menuColor);
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
    UnloadTexture(duckR);
    UnloadTexture(duckL);
    UnloadTexture(attackR);
    UnloadTexture(attackL);
    UnloadTexture(attackR_C);
    UnloadTexture(attackL_C);
    UnloadTexture(enemyTex);
    UnloadTexture(fondo);
    CloseWindow();
    return 0;
}