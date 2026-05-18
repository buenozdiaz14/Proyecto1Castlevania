#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "resource_dir.h"

// Dimensiones de la ventana
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450

// Tamaños del sprite del jugador
#define PLAYER_SPRITE_WIDTH  72
#define PLAYER_SPRITE_HEIGHT 32

// Hitbox real del jugador
#define PLAYER_HITBOX_WIDTH  24
#define PLAYER_HITBOX_HEIGHT 32

#define ATTACK_HITBOX_WIDTH  20
#define ATTACK_HITBOX_HEIGHT 18

// Tamaños del enemigo
#define ENEMY_WIDTH   16
#define ENEMY_HEIGHT  31

// Tamaño de los tiles
#define TILE_SIZE     34
#define MAP_WIDTH     250
#define MAP_HEIGHT    12   

// --- DEFINICIÓN DE TILES ---
// 0 = Aire / Vacío
// 1 = Bloque Sólido (Pared/Suelo)
// 2 = SPAWN DEL JUGADOR
// 3 = FINAL DEL MAPA / TELETRANSPORTE

// Mapa 1 (Level1)
int Level1[MAP_HEIGHT][MAP_WIDTH] = {
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
    {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int (*currentLevel)[MAP_WIDTH] = Level1;
int Map2[MAP_HEIGHT][MAP_WIDTH] = { 0 }; 
int currentMap = 1;

typedef enum GameState { MENU, PLAYING, GAMEOVER, WIN, EXIT } GameState;

struct Animation { int Frame; int Counter; int Speed; } Spring, Enemy;
struct AttackAnimation { int Frame; int Counter; int Speed; } Attacker;

void AnimationSettings() {
    Spring.Counter++;
    if (Spring.Counter >= (100 / Spring.Speed)) { Spring.Counter = 0; Spring.Frame++; if (Spring.Frame > 2) Spring.Frame = 0; }
    Enemy.Counter++;
    if (Enemy.Counter >= (100 / Enemy.Speed)) { Enemy.Counter = 0; Enemy.Frame++; if (Enemy.Frame > 2) Enemy.Frame = 0; }
    if (IsKeyDown(KEY_E)) {
        Attacker.Counter++;
        if (Attacker.Counter >= (100 / Attacker.Speed)) { Attacker.Counter = 0; Attacker.Frame++; if (Attacker.Frame > 5) Attacker.Frame = 0; }
    } else { Attacker.Frame = 0; }
}

Vector2 FindSpawnPosition() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (currentLevel[y][x] == 2) {
                return (Vector2){ (float)(x * TILE_SIZE), (float)(y * TILE_SIZE) };
            }
        }
    }
    return (Vector2){ 100.0f, 200.0f }; // Fallback
}

float GetGroundHeight(float x) {
    int tileX = (int)(x + PLAYER_HITBOX_WIDTH / 2) / TILE_SIZE;
    if (tileX >= MAP_WIDTH) tileX = MAP_WIDTH - 1;
    if (tileX < 0) tileX = 0;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (currentLevel[y][tileX] == 1) return y * TILE_SIZE - PLAYER_HITBOX_HEIGHT;
    }
    return MAP_HEIGHT * TILE_SIZE - PLAYER_HITBOX_HEIGHT;
}

float GetEnemyGroundHeight(float x) {
    int tileX = (int)(x + ENEMY_WIDTH / 2) / TILE_SIZE;
    if (tileX >= MAP_WIDTH) tileX = MAP_WIDTH - 1;
    if (tileX < 0) tileX = 0;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (currentLevel[y][tileX] == 1) return y * TILE_SIZE - ENEMY_HEIGHT;
    }
    return MAP_HEIGHT * TILE_SIZE - ENEMY_HEIGHT;
}

void ResetGame(float* playerX, float* playerY, float* velocityY, bool* isGrounded,
    bool* canMove, bool* isJumping, int* jumpDirection,
    float* verticalSpeed, float* horizontalSpeed,
    float* enemyX, float* enemyY, bool* playerActive,
    int* direction, bool* isDucking, bool* isAttacking,
    Camera2D* camera, int screenWidth, int screenHeight) {
    
    Vector2 spawnPos = FindSpawnPosition();
    *playerX = spawnPos.x;
    *playerY = spawnPos.y;
    
    *velocityY = 0.0f;
    *isGrounded = true;
    *canMove = true;
    *isJumping = false;
    *jumpDirection = 0;
    *verticalSpeed = 0.0f;
    *horizontalSpeed = 0.0f;

    *enemyX = *playerX + 400.0f;
    if (*enemyX + ENEMY_WIDTH > MAP_WIDTH * TILE_SIZE) *enemyX = MAP_WIDTH * TILE_SIZE - ENEMY_WIDTH;
    *enemyY = GetEnemyGroundHeight(*enemyX);
    *playerActive = true;
    *direction = 0;
    *isDucking = false;
    *isAttacking = false;
    Spring.Frame = 0; Spring.Counter = 0;
    Enemy.Frame = 0; Enemy.Counter = 0;
    Attacker.Frame = 0; Attacker.Counter = 0;

    camera->target = (Vector2){ *playerX + PLAYER_HITBOX_WIDTH / 2, 290.0f };
    camera->offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera->rotation = 0.0f;
    camera->zoom = 2.0f;
}

// --- CORRECCIÓN CRÍTICA: INICIALIZAR EL MAPA 2 CON SUELO SÓLIDO ---
void InitMap2Data() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            // Fila 0 (Techo), Fila 11 (Suelo continuo), Columnas laterales (Paredes)
            if (y == 0 || y == 11 || x == 0 || x == MAP_WIDTH - 1) {
                Map2[y][x] = 1;
            } else {
                Map2[y][x] = 0;
            }
        }
    }

    // Colocar el Spawn (2) en el Mapa 2 en un lugar seguro sobre el suelo sólido (Fila 8, Columna 4)
    Map2[8][4] = 2; 

    // Altar Central / Plataformas mecánicas en Map2
    Map2[7][12] = 1; Map2[7][13] = 1;
    Map2[8][11] = 1; Map2[8][12] = 1; Map2[8][13] = 1; Map2[8][14] = 1;
    Map2[9][10] = 1; Map2[9][11] = 1; Map2[9][12] = 1; Map2[9][13] = 1; Map2[9][14] = 1; Map2[9][15] = 1;

    for(int i = 3; i <= 6; i++)   Map2[3][i] = 1;
    for(int i = 19; i <= 22; i++) Map2[3][i] = 1;
    for(int i = 3; i <= 7; i++)   Map2[6][i] = 1;
    for(int i = 21; i <= 25; i++) Map2[6][i] = 1;

    // Relleno extra a lo largo de las 250 columnas para que el mapa no esté vacío
    for (int i = 40; i < 60; i++)   Map2[8][i] = 1;
    for (int i = 80; i < 100; i++)  Map2[6][i] = 1;
    for (int i = 130; i < 160; i++) Map2[4][i] = 1;
    for (int i = 180; i < 220; i++) Map2[8][i] = 1;

    // Colocar la salida (3) al final del Mapa 2 (Justo antes de la pared derecha)
    Map2[7][MAP_WIDTH - 2] = 3;
    Map2[8][MAP_WIDTH - 2] = 3;
    Map2[9][MAP_WIDTH - 2] = 3;
}

bool CheckTriggerCollision(float px, float py) {
    int startX = (int)(px) / TILE_SIZE;
    int endX = (int)(px + PLAYER_HITBOX_WIDTH) / TILE_SIZE;
    int startY = (int)(py) / TILE_SIZE;
    int endY = (int)(py + PLAYER_HITBOX_HEIGHT) / TILE_SIZE;

    if (startX < 0) startX = 0; if (endX >= MAP_WIDTH) endX = MAP_WIDTH - 1;
    if (startY < 0) startY = 0; if (endY >= MAP_HEIGHT) endY = MAP_HEIGHT - 1;

    for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
            if (currentLevel[y][x] == 3) return true; 
        }
    }
    return false;
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "_C4STL3V4N14_");
    SearchAndSetResourceDir("resources");
    InitAudioDevice();

    InitMap2Data();

    Texture2D idleR = LoadTexture("Idle.png"); Texture2D idleL = LoadTexture("Idle_Sided.png");
    Texture2D walkR = LoadTexture("Walking_R.png"); Texture2D walkL = LoadTexture("Walking_L.png");
    Texture2D jumpR = LoadTexture("Jumper.png"); Texture2D jumpL = LoadTexture("Jump_L.png");
    Texture2D duckR = LoadTexture("Crouch_R.png"); Texture2D duckL = LoadTexture("Crouch_L.png");
    Texture2D attackR = LoadTexture("Attack_R.png"); Texture2D attackL = LoadTexture("Attack_L - Rework.png");
    Texture2D attackR_C = LoadTexture("C_A_R.png"); Texture2D attackL_C = LoadTexture("C_A_L.png");
    Texture2D enemyTex = LoadTexture("Zombie_L.png");
    Texture2D fondo = LoadTexture("maapa.png"); Texture2D fondo2 = LoadTexture("Map2.png");
    Texture2D Weapon2 = LoadTexture("Item_Star.png"); Texture2D Item1 = LoadTexture("Item_Image1.png"); Texture2D Item2 = LoadTexture("Item_Image2.png");

    SetTextureFilter(fondo, TEXTURE_FILTER_POINT); SetTextureFilter(fondo2, TEXTURE_FILTER_POINT);

    GameState gameState = MENU;
    int menuSelection = 0; int gameOverSelection = 0; int winSelection = 0;       

    Music musicaFondo = LoadMusicStream("001.wav"); Music Stage01 = LoadMusicStream("002.mp3");
    SetMasterVolume(1.0f); SetMusicVolume(musicaFondo, 1.0f);
    PlayMusicStream(musicaFondo); PlayMusicStream(Stage01);

    float playerX, playerY; float vX = 3.0f; float G = 0.2f;
    bool canMove = true; bool isJumping = false; int jumpDirection = 0;
    float verticalSpeed = 0.0f; float initialJumpSpeed = -7.0f; float horizontalSpeed = 0.0f;
    int direction = 0; bool playerActive = true; bool isDucking = false; bool isAttacking = false;
    float velocityY = 0.0f; bool isGrounded = false;

    float enemyX, enemyY; float enemySpeed = 2.0f;
    bool Whip = true; Camera2D camera = { 0 };
   
    Spring.Speed = 6; Enemy.Speed = 7; Attacker.Speed = 10;

    ResetGame(&playerX, &playerY, &velocityY, &isGrounded, &canMove, &isJumping, &jumpDirection,
        &verticalSpeed, &horizontalSpeed, &enemyX, &enemyY, &playerActive, &direction, &isDucking, &isAttacking,
        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
   
    bool CloseIt = false; bool Music01 = false;
    
    while (CloseIt == 0 && !WindowShouldClose()) 
    {
        UpdateMusicStream(musicaFondo);
        if (gameState == PLAYING) { AnimationSettings(); Music01 = true; SetMusicVolume(musicaFondo, 0); }
        
        switch (gameState) {
        case MENU: {
            if (IsKeyPressed(KEY_UP)) { menuSelection--; if (menuSelection < 0) menuSelection = 1; }
            if (IsKeyPressed(KEY_DOWN)) { menuSelection++; if (menuSelection > 1) menuSelection = 0; }
            if (IsKeyPressed(KEY_ENTER)) {
                if (menuSelection == 0) {
                    currentMap = 1; currentLevel = Level1; gameState = PLAYING;
                    ResetGame(&playerX, &playerY, &velocityY, &isGrounded, &canMove, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed, &enemyX, &enemyY, &playerActive, &direction, &isDucking, &isAttacking,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                } else if (menuSelection == 1) { gameState = EXIT; }
            }
            break;
        }
        case EXIT: CloseIt = true; break;

        case PLAYING: {
            if (Music01) UpdateMusicStream(Stage01);
            bool duckKey = IsKeyDown(KEY_LEFT_SHIFT); bool attackKey = IsKeyDown(KEY_E);
            isDucking = false; isAttacking = false;

            if (!isJumping) {
                if (attackKey) { isAttacking = true; canMove = false; }
                else if (duckKey) { isDucking = true; canMove = false; }
                else { canMove = true; }
            }

            if (playerActive) {
                if (canMove && !isJumping && !isAttacking && !isDucking) {
                    float newX = playerX;
                    if (IsKeyDown(KEY_D)) { newX += vX; direction = 0; }
                    else if (IsKeyDown(KEY_A)) { newX -= vX; direction = 1; }

                    int topTile = (int)(playerY) / TILE_SIZE;
                    int bottomTile = (int)(playerY + PLAYER_HITBOX_HEIGHT - 1) / TILE_SIZE;
                    if (newX > playerX) {
                        int rightTile = (int)(newX + PLAYER_HITBOX_WIDTH) / TILE_SIZE;
                        if (rightTile >= MAP_WIDTH) rightTile = MAP_WIDTH - 1;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (currentLevel[ty][rightTile] == 1) { newX = rightTile * TILE_SIZE - PLAYER_HITBOX_WIDTH; break; }
                        }
                    } else if (newX < playerX) {
                        int leftTile = (int)(newX) / TILE_SIZE;
                        if (leftTile < 0) leftTile = 0;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (currentLevel[ty][leftTile] == 1) { newX = (leftTile + 1) * TILE_SIZE; break; }
                        }
                    }
                    playerX = newX;

                    playerY += G;
                    int tileX = (int)(playerX + PLAYER_HITBOX_WIDTH / 2) / TILE_SIZE;
                    int tileY = (int)(playerY + PLAYER_HITBOX_HEIGHT) / TILE_SIZE;
                    if (tileY >= MAP_HEIGHT) tileY = MAP_HEIGHT - 1;
                    if (currentLevel[tileY][tileX] == 1) { playerY = tileY * TILE_SIZE - PLAYER_HITBOX_HEIGHT; isGrounded = true; }
                    else { isGrounded = false; }
                }

                if (canMove && !isJumping && !isAttacking && !isDucking) {
                    if (IsKeyPressed(KEY_SPACE)) {
                        isJumping = true; canMove = false; verticalSpeed = initialJumpSpeed;
                        if (IsKeyDown(KEY_D)) { jumpDirection = 1; direction = 0; horizontalSpeed = vX; }
                        else if (IsKeyDown(KEY_A)) { jumpDirection = -1; direction = 1; horizontalSpeed = -vX; }
                        else { jumpDirection = 0; horizontalSpeed = 0.0f; }
                    }
                }

                if (isJumping) {
                    verticalSpeed += G; playerY += verticalSpeed;
                    float newX = playerX + horizontalSpeed;
                    int topTile = (int)(playerY) / TILE_SIZE;
                    int bottomTile = (int)(playerY + PLAYER_HITBOX_HEIGHT - 1) / TILE_SIZE;
                    if (horizontalSpeed > 0) {
                        int rightTile = (int)(newX + PLAYER_HITBOX_WIDTH) / TILE_SIZE;
                        if (rightTile >= MAP_WIDTH) rightTile = MAP_WIDTH - 1;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (currentLevel[ty][rightTile] == 1) { newX = rightTile * TILE_SIZE - PLAYER_HITBOX_WIDTH; horizontalSpeed = 0; break; }
                        }
                    } else if (horizontalSpeed < 0) {
                        int leftTile = (int)(newX) / TILE_SIZE;
                        if (leftTile < 0) leftTile = 0;
                        for (int ty = topTile; ty <= bottomTile; ty++) {
                            if (currentLevel[ty][leftTile] == 1) { newX = (leftTile + 1) * TILE_SIZE; horizontalSpeed = 0; break; }
                        }
                    }
                    playerX = newX;

                    int tileX = (int)(playerX + PLAYER_HITBOX_WIDTH / 2) / TILE_SIZE;
                    int tileY = (int)(playerY + PLAYER_HITBOX_HEIGHT) / TILE_SIZE;
                    if (tileY >= MAP_HEIGHT) tileY = MAP_HEIGHT - 1;
                    if (currentLevel[tileY][tileX] == 1) {
                        playerY = tileY * TILE_SIZE - PLAYER_HITBOX_HEIGHT;
                        isJumping = false; canMove = true; verticalSpeed = 0; jumpDirection = 0; horizontalSpeed = 0; isGrounded = true;
                    }
                }
                if (playerX < 0) playerX = 0;

                // --- TRIGGER DE TELETRANSPORTE AL TOCAR EL TILE 3 ---
                if (CheckTriggerCollision(playerX, playerY)) {
                    if (currentMap == 1) {
                        currentMap = 2;
                        currentLevel = Map2; // Cambia el puntero de nivel activo
                        
                        // Busca el tile '2' del Map2 y coloca al jugador allí de forma limpia
                        ResetGame(&playerX, &playerY, &velocityY, &isGrounded, &canMove, &isJumping, &jumpDirection,
                            &verticalSpeed, &horizontalSpeed, &enemyX, &enemyY, &playerActive, &direction, &isDucking, &isAttacking,
                            &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                    } else {
                        gameState = WIN;
                    }
                }
            }

            // Enemigo
            enemyX -= enemySpeed;
            if (playerX - enemyX >= 800.0f) {
                enemyX = playerX + 800.0f;
                if (enemyX + ENEMY_WIDTH > MAP_WIDTH * TILE_SIZE) enemyX = MAP_WIDTH * TILE_SIZE - ENEMY_WIDTH;
            }
            enemyY = GetEnemyGroundHeight(enemyX);

            // Combate
            if (playerActive) {
                Rectangle playerHitbox = { playerX, playerY, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT };
                Rectangle enemyRect = { enemyX, enemyY, ENEMY_WIDTH, ENEMY_HEIGHT };
                Rectangle attackHitboxR = { playerX + 16, playerY, ATTACK_HITBOX_WIDTH, ATTACK_HITBOX_HEIGHT };
                Rectangle attackHitboxL = { playerX - 10, playerY, ATTACK_HITBOX_WIDTH, ATTACK_HITBOX_HEIGHT };
               
                if (attackKey && Whip) {
                    if (direction == 0 && CheckCollisionRecs(attackHitboxR, enemyRect)) enemyX = playerX + 800;
                    else if (direction == 1 && CheckCollisionRecs(attackHitboxL, enemyRect)) enemyX = playerX + 800;
                }
                if (CheckCollisionRecs(playerHitbox, enemyRect)) { playerActive = false; gameState = GAMEOVER; gameOverSelection = 0; }
            }
            camera.target = (Vector2){ playerX + PLAYER_HITBOX_WIDTH / 2, 290.0f };
            break;
        }

        case GAMEOVER: {
            if (IsKeyPressed(KEY_UP)) { gameOverSelection--; if (gameOverSelection < 0) gameOverSelection = 1; }
            if (IsKeyPressed(KEY_DOWN)) { gameOverSelection++; if (gameOverSelection > 1) gameOverSelection = 0; }
            if (IsKeyPressed(KEY_ENTER)) {
                if (gameOverSelection == 0) {
                    gameState = PLAYING;
                    ResetGame(&playerX, &playerY, &velocityY, &isGrounded, &canMove, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed, &enemyX, &enemyY, &playerActive, &direction, &isDucking, &isAttacking,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                } else if (gameOverSelection == 1) { gameState = EXIT; }
            }
            break;
        }
        case WIN: {
            if (IsKeyPressed(KEY_UP)) { winSelection--; if (winSelection < 0) winSelection = 1; }
            if (IsKeyPressed(KEY_DOWN)) { winSelection++; if (winSelection > 1) winSelection = 0; }
            if (IsKeyPressed(KEY_ENTER)) {
                if (winSelection == 0) { gameState = MENU; menuSelection = 0; }
                else if (winSelection == 1) { gameState = EXIT; }
            }
            break;
        }
        }

        // ---------- Dibujado ----------
        BeginDrawing();
        ClearBackground(BLACK);

        switch (gameState) {
        case MENU: {
            DrawText("CASTLEVANIA", (SCREEN_WIDTH - MeasureText("CASTLEVANIA", 30)) / 2, SCREEN_HEIGHT / 2 - 80, 30, RED);
            Color playColor = (menuSelection == 0) ? YELLOW : WHITE; Color exitColor = (menuSelection == 1) ? YELLOW : WHITE;
            DrawText("Play", (SCREEN_WIDTH - MeasureText("Play", 30)) / 2, SCREEN_HEIGHT / 2 - 20, 30, playColor);
            DrawText("Exit", (SCREEN_WIDTH - MeasureText("Exit", 30)) / 2, SCREEN_HEIGHT / 2 + 20, 30, exitColor);
            break;
        }
        case PLAYING: {
            BeginMode2D(camera);
            
            // Dibuja el fondo correcto según el mapa en el que estés
            if (currentMap == 1) DrawTextureEx(fondo, (Vector2) { 0, 0 }, 0, 2.0f, WHITE);
            else DrawTextureEx(fondo2, (Vector2) { 1, 1 }, 0, 0.5f, WHITE);

            // Renderizar los bloques físicos
            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    if (currentLevel[y][x] == 1) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
                    } else if (currentLevel[y][x] == 3) {
                        // Pintamos el activador de la puerta en color granate para que se vea
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, MAROON);
                    }
                }
            }

            // Enemigo
            Rectangle enemySource = { Enemy.Frame * 17, 0, ENEMY_WIDTH, ENEMY_HEIGHT };
            Rectangle enemyDest = { enemyX, enemyY, ENEMY_WIDTH, ENEMY_HEIGHT };
            DrawTexturePro(enemyTex, enemySource, enemyDest, (Vector2) { 0, 0 }, 0, WHITE);

            // Jugador
            if (playerActive) {
                Rectangle source; float spriteOffsetX = (PLAYER_SPRITE_WIDTH - PLAYER_HITBOX_WIDTH) / 2.0f;
                Rectangle dest = { playerX - spriteOffsetX, playerY, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                Texture2D textureToDraw; bool usePro = true;

                if (isAttacking && Whip) {
                    source = (Rectangle){ Attacker.Frame * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                    textureToDraw = (direction == 0) ? ((IsKeyDown(KEY_LEFT_SHIFT)) ? attackR_C : attackR) : ((IsKeyDown(KEY_LEFT_SHIFT)) ? attackL_C : attackL);
                } else if (isDucking) {
                    source = (Rectangle){ Spring.Frame * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                    textureToDraw = (direction == 0) ? duckR : duckL;
                } else if (isJumping) {
                    source = (Rectangle){ Spring.Frame * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                    textureToDraw = (direction == 0) ? jumpR : jumpL;
                } else if (canMove && (IsKeyDown(KEY_D) || IsKeyDown(KEY_A))) {
                    source = (Rectangle){ Spring.Frame * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                    textureToDraw = (direction == 0) ? walkR : walkL;
                } else {
                    usePro = false;
                    if (direction == 0) DrawTextureEx(idleR, (Vector2) { dest.x, dest.y }, 0, 1, WHITE);
                    else DrawTextureEx(idleL, (Vector2) { dest.x, dest.y }, 0, 1, WHITE);
                }
                if (usePro) DrawTexturePro(textureToDraw, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
            }
            EndMode2D();
            break;
        }
        case GAMEOVER: {
            DrawText("GAME OVER", (SCREEN_WIDTH - MeasureText("GAME OVER", 40)) / 2, SCREEN_HEIGHT / 2 - 60, 40, RED);
            Color rtryColor = (gameOverSelection == 0) ? YELLOW : WHITE; Color extColor = (gameOverSelection == 1) ? YELLOW : WHITE;
            DrawText("Try Again", (SCREEN_WIDTH - MeasureText("Try Again", 20)) / 2, SCREEN_HEIGHT / 2 + 15, 20, rtryColor);
            DrawText("Exit", (SCREEN_WIDTH - MeasureText("Exit", 20)) / 2, SCREEN_HEIGHT / 2 + 55, 20, extColor);
            break;
        }
        case WIN: {
            DrawText("YOU WIN!", (SCREEN_WIDTH - MeasureText("YOU WIN!", 40)) / 2, SCREEN_HEIGHT / 2 - 60, 40, GREEN);
            Color menuColor = (winSelection == 0) ? YELLOW : WHITE; Color extColor = (winSelection == 1) ? YELLOW : WHITE;
            DrawText("Return to Menu", (SCREEN_WIDTH - MeasureText("Return to Menu", 20)) / 2, SCREEN_HEIGHT / 2 + 15, 20, menuColor);
            DrawText("Exit", (SCREEN_WIDTH - MeasureText("Exit", 20)) / 2, SCREEN_HEIGHT / 2 + 55, 20, extColor);
            break;
        }
        }
        EndDrawing();
    }

    UnloadTexture(idleR); UnloadTexture(idleL); UnloadTexture(walkR); UnloadTexture(walkL);
    UnloadTexture(jumpR); UnloadTexture(jumpL); UnloadTexture(duckR); UnloadTexture(duckL);
    UnloadTexture(attackR); UnloadTexture(attackL); UnloadTexture(attackR_C); UnloadTexture(attackL_C);
    UnloadTexture(enemyTex); UnloadTexture(fondo); UnloadTexture(fondo2);
    UnloadTexture(Weapon2); UnloadTexture(Item1); UnloadTexture(Item2);
    UnloadMusicStream(musicaFondo); UnloadMusicStream(Stage01);
    CloseAudioDevice(); CloseWindow();
    return 0;
}