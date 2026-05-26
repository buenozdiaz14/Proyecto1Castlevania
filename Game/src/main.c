#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

#define ATTACK_HITBOX_WIDTH  20
#define ATTACK_HITBOX_HEIGHT 18

// Tamaños del enemigo
#define ENEMY_WIDTH   16
#define ENEMY_HEIGHT  31

// Item 
#define ITEM_WIDTH   16
#define ITEM_HEIGHT  16

// Tamaños corregidos de 1 solo frame del Boss (126/3 = 42)
#define BOSS_WIDTH 42
#define BOSS_HEIGHT 37

// Tamaño de los tiles
#define TILE_SIZE     34
#define MAP_WIDTH     250
#define MAP_HEIGHT    12

// Disparo del boss
#define BOSS_SHOOT_INTERVAL 2.0f
#define BOSS_PROJECTILE_SPEED 3.0f
#define BOSS_PROJECTILE_RANGE 600.0f

typedef struct BossProjectile {
    bool active;
    float x, y;
    float vx, vy;
    float distance;
} BossProjectile;

#define MAX_BOSS_PROJECTILES 5

// --- DEFINICIÓN DE TILES ---
// 0 = Aire / Vacío
// 1 = Bloque Sólido (Pared/Suelo)
// 2 = SPAWN DEL JUGADOR
// 3 = FINAL DEL MAPA / TELETRANSPORTE

// Mapa 1 (Level1) - Antiguo "map", ahora con spawn y salida
int Level1[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},  // tile 3 en columna 248
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1}, // spawn (2) en columna 1, tile 3 en 248
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1}, // más tiles 3
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int (*currentLevel)[MAP_WIDTH] = Level1;
int Map2[MAP_HEIGHT][MAP_WIDTH] = { 0 };
int currentMap = 1;

// Estados del juego (añadido CHEAT_MENU)
typedef enum GameState {
    MENU,
    PLAYING,
    GAMEOVER,
    WIN,
    EXIT,
    TUTORIAL,
    CHEAT_MENU
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

// ---------- Proyectil para la estrella ----------
typedef struct Projectile {
    bool active;
    float x, y;
    float direction;   // 1 = derecha, -1 = izquierda
    float distance;
} Projectile;

Projectile starBall = { false, 0, 0, 1, 0 };
#define PROJECTILE_SPEED 5.0f
#define PROJECTILE_RANGE 400.0f
float starCooldown = 0.0f;
#define STAR_COOLDOWN_TIME 1.0f

// ---------- ESTRUCTURAS DEL BOSS ----------
typedef enum BossState {
    BOSS_HANGING,
    BOSS_FLYING,
    BOSS_RESTING
} BossState;

typedef struct PhantomBat {
    float x, y;
    BossState state;
    bool active;
    int hp;
    float flyTimer;
    float stateTimer;
    float invulnerableTimer;
} PhantomBat;

PhantomBat boss;
BossProjectile bossProjectiles[MAX_BOSS_PROJECTILES] = { 0 };
float bossShootTimer = 0.0f;

// Temporizador
typedef struct {
    float Lifetime;
} Timer;

void StartTimer(Timer* timer, float lifetime) {
    if (timer != NULL) timer->Lifetime = lifetime;
}
void UpdateTimer(Timer* timer) {
    if (timer != NULL && timer->Lifetime > 0) timer->Lifetime -= GetFrameTime();
}
bool TimerDone(Timer* timer) {
    if (timer != NULL) return timer->Lifetime <= 0;
    return false;
}

// Variables globales de items
bool Whip = true;
bool Star = false;
bool CollectStar = false;
float Warning = 2.0f;
Timer Collection = { 0 };
Timer Tutorial = { 0 };

// --- Variables del menú de trucos ---
bool godMode = false;
int blinkCounter = 0;

// --- FUNCIONES NUEVAS DEL SISTEMA DE NIVELES ---
Vector2 FindSpawnPosition() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (currentLevel[y][x] == 2) {
                return (Vector2) { (float)(x * TILE_SIZE), (float)(y * TILE_SIZE) };
            }
        }
    }
    return (Vector2) { 100.0f, 200.0f }; // Fallback
}

void InitMap2Data() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (y == 0 || y == 11 || x == 0 || x == MAP_WIDTH - 1) {
                Map2[y][x] = 1;
            }
            else {
                Map2[y][x] = 0;
            }
        }
    }
    Map2[8][4] = 2; // spawn del boss (marcador, aunque usaremos una posición fija)

    // Plataformas/estructura de la sala
    Map2[7][12] = 1; Map2[7][13] = 1;
    Map2[8][11] = 1; Map2[8][12] = 1; Map2[8][13] = 1; Map2[8][14] = 1;
    Map2[9][10] = 1; Map2[9][11] = 1; Map2[9][12] = 1; Map2[9][13] = 1; Map2[9][14] = 1; Map2[9][15] = 1;
    for (int i = 3; i <= 6; i++)   Map2[3][i] = 1;
    for (int i = 19; i <= 22; i++) Map2[3][i] = 1;
    for (int i = 3; i <= 7; i++)   Map2[6][i] = 1;
    for (int i = 21; i <= 25; i++) Map2[6][i] = 1;
    for (int i = 40; i < 60; i++)   Map2[8][i] = 1;
    for (int i = 80; i < 100; i++)  Map2[6][i] = 1;
    for (int i = 130; i < 160; i++) Map2[4][i] = 1;
    for (int i = 180; i < 220; i++) Map2[8][i] = 1;

    // Salida al final del mapa 2
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

// Comprueba si un rectángulo colisiona con algún tile sólido (1)
bool CheckTileCollision(Rectangle rect) {
    int left = (int)(rect.x) / TILE_SIZE;
    int right = (int)(rect.x + rect.width) / TILE_SIZE;
    int top = (int)(rect.y) / TILE_SIZE;
    int bottom = (int)(rect.y + rect.height) / TILE_SIZE;

    if (left < 0) left = 0;
    if (right >= MAP_WIDTH) right = MAP_WIDTH - 1;
    if (top < 0) top = 0;
    if (bottom >= MAP_HEIGHT) bottom = MAP_HEIGHT - 1;

    for (int y = top; y <= bottom; y++) {
        for (int x = left; x <= right; x++) {
            if (currentLevel[y][x] == 1) return true;
        }
    }
    return false;
}

// Actualiza frames de animación
void AnimationSettings() {
    Spring.Counter++;
    if (Spring.Counter >= (100 / Spring.Speed)) { Spring.Counter = 0; Spring.Frame++; if (Spring.Frame > 2) Spring.Frame = 0; }

    Enemy.Counter++;
    if (Enemy.Counter >= (100 / Enemy.Speed)) { Enemy.Counter = 0; Enemy.Frame++; if (Enemy.Frame > 2) Enemy.Frame = 0; }

    if (Whip && IsKeyDown(KEY_E))
    {
        Attacker.Counter++;
        if (Attacker.Counter >= (100 / Attacker.Speed)) { Attacker.Counter = 0; Attacker.Frame++; if (Attacker.Frame > 5) Attacker.Frame = 0; }
    }
    else
        Attacker.Frame = 0;
}

// Obtener altura del suelo para el jugador (usa currentLevel)
float GetGroundHeight(float x) {
    int tileX = (int)(x + PLAYER_HITBOX_WIDTH / 2) / TILE_SIZE;
    if (tileX >= MAP_WIDTH) tileX = MAP_WIDTH - 1;
    if (tileX < 0) tileX = 0;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (currentLevel[y][tileX] == 1) return y * TILE_SIZE - PLAYER_HITBOX_HEIGHT;
    }
    return MAP_HEIGHT * TILE_SIZE - PLAYER_HITBOX_HEIGHT;
}

// Obtener altura del suelo para el enemigo
float GetEnemyGroundHeight(float x) {
    int tileX = (int)(x + ENEMY_WIDTH / 2) / TILE_SIZE;
    if (tileX >= MAP_WIDTH) tileX = MAP_WIDTH - 1;
    if (tileX < 0) tileX = 0;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (currentLevel[y][tileX] == 1) return y * TILE_SIZE - ENEMY_HEIGHT;
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

    // --- SPAWN CORREGIDO SEGÚN EL NIVEL ---
    if (currentMap == 1) {
        *playerX = 200.0f;
        *playerY = GetGroundHeight(*playerX);
    }
    else {
        *playerX = 13.0f * TILE_SIZE;
        *playerY = 8.0f * TILE_SIZE - PLAYER_HITBOX_HEIGHT - 10;
    }

    *velocityY = 0.0f;
    *isGrounded = true;
    *canMove = true;
    *isJumping = false;
    *jumpDirection = 0;
    *verticalSpeed = 0.0f;
    *horizontalSpeed = 0.0f;

    *enemyX = *playerX + 800.0f;
    if (*enemyX + ENEMY_WIDTH > MAP_WIDTH * TILE_SIZE) *enemyX = MAP_WIDTH * TILE_SIZE - ENEMY_WIDTH;
    *enemyY = GetEnemyGroundHeight(*enemyX);
    *playerActive = true;
    *direction = 0;
    *isDucking = false;
    *isAttacking = false;
    Spring.Frame = 0; Spring.Counter = 0;
    Enemy.Frame = 0; Enemy.Counter = 0;
    Attacker.Frame = 0; Attacker.Counter = 0;

    starBall.active = false;
    starCooldown = 0.0f;

    // Inicializar boss SOLO en el Mapa 2
    if (currentMap == 2) {
        boss.x = 200.0f;
        boss.y = 100.0f;
        boss.state = BOSS_HANGING;
        boss.active = true;
        boss.hp = 4;
        boss.flyTimer = 0.0f;
        boss.stateTimer = 0.0f;
        boss.invulnerableTimer = 0.0f;
        bossShootTimer = 0.0f;
        for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) {
            bossProjectiles[i].active = false;
        }
    }
    else {
        boss.active = false;
    }

    camera->target = (Vector2){ *playerX + PLAYER_HITBOX_WIDTH / 2, 290.0f };
    camera->offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera->rotation = 0.0f;
    camera->zoom = 2.0f;
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "_C4STL3V4N14_");
    SearchAndSetResourceDir("resources");
    InitAudioDevice();

    InitMap2Data(); // Inicializar el mapa del boss

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
    Texture2D fondo2 = LoadTexture("Map2.png");              // Fondo del boss
    Texture2D Weapon2 = LoadTexture("Item_Star.png");
    Texture2D Item1 = LoadTexture("Item_Image1.png");
    Texture2D Item2 = LoadTexture("Item_Image2.png");
    Texture2D starProjectileTex = LoadTexture("Item_Star_2.png");
    Texture2D DRACULA = LoadTexture("VAMP.png");
    Texture2D bossTex = LoadTexture("boss_castlevania.png");

    SetTextureFilter(fondo, TEXTURE_FILTER_POINT);
    SetTextureFilter(fondo2, TEXTURE_FILTER_POINT);

    // ------------------ Variables de estado -----------------
    GameState gameState = MENU;
    int menuSelection = 0;
    int gameOverSelection = 0;
    int winSelection = 0;
    int cheatSelection = 0;

    Music musicaFondo = LoadMusicStream("001.wav");
    Music Stage01 = LoadMusicStream("002.mp3");
    SetMasterVolume(1.0f);
    SetMusicVolume(musicaFondo, 1.0f);
    SetMusicPan(musicaFondo, 1.0f);
    PlayMusicStream(musicaFondo);
    PlayMusicStream(Stage01);

    bool TutorialStart = false;
    float Tick = 0;

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
    int direction = 0;
    bool playerActive = true;
    bool isDucking = false;
    bool isAttacking = false;

    float velocityY = 0.0f;
    bool isGrounded = false;

    // ------------------ Variables del enemigo -----------------
    float enemyX, enemyY;
    float enemySpeed = 2.0f;

    // ------------------ Cámara -----------------
    Camera2D camera = { 0 };

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
    bool Music01 = false;

    while (CloseIt == 0 && !WindowShouldClose())
    {
        float delta = GetFrameTime();
        UpdateMusicStream(musicaFondo);

        if (gameState == PLAYING) {
            AnimationSettings();
            Music01 = true;
            SetMusicVolume(musicaFondo, 0);
            if (starCooldown > 0.0f) {
                starCooldown -= delta;
                if (starCooldown < 0.0f) starCooldown = 0.0f;
            }

            // Abrir menú de trucos con F1 o P
            if (IsKeyPressed(KEY_F1) || IsKeyPressed(KEY_P)) {
                gameState = CHEAT_MENU;
                cheatSelection = 0;
            }
        }

        switch (gameState) {
        case MENU: {
            if (IsKeyPressed(KEY_UP)) { menuSelection--; if (menuSelection < 0) menuSelection = 1; }
            if (IsKeyPressed(KEY_DOWN)) { menuSelection++; if (menuSelection > 1) menuSelection = 0; }
            if (IsKeyPressed(KEY_ENTER)) {
                if (menuSelection == 0) {
                    currentMap = 1;
                    currentLevel = Level1;
                    gameState = TUTORIAL;
                    TutorialStart = true;
                }
                else if (menuSelection == 1) { gameState = EXIT; }
            }
            Vector2 mousePos = GetMousePosition();
            Rectangle playBtn = { SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f - 20, 100, 30 };
            Rectangle exitBtn = { SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f + 20, 100, 30 };
            if (CheckCollisionPointRec(mousePos, playBtn)) {
                menuSelection = 0;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentMap = 1;
                    currentLevel = Level1;
                    gameState = TUTORIAL;
                    TutorialStart = true;
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                menuSelection = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { gameState = EXIT; }
            }
            break;
        }
        case EXIT: CloseIt = true; break;

        case TUTORIAL: {
            playerX = 0;
            if (TutorialStart) { StartTimer(&Tutorial, 6.0f); TutorialStart = false; }
            UpdateTimer(&Tutorial);
            if (!TimerDone(&Tutorial)) {
                Tick += 0.1f;
                DrawTextureEx(DRACULA, (Vector2) { (SCREEN_WIDTH - 120) / 2, SCREEN_HEIGHT / 2 - 60 }, 0, 2, WHITE);
                if (Tick >= 20.0f) DrawText("You only have one life.\nI hope you fail.", (SCREEN_WIDTH - 250) / 2, SCREEN_HEIGHT / 2 + 50, 20, RED);
                else DrawText("You can press E to attack.\nYou can crouch with Shift.", (SCREEN_WIDTH - 250) / 2, SCREEN_HEIGHT / 2 + 50, 20, RED);
            }
            if (TimerDone(&Tutorial)) {
                currentMap = 1;
                currentLevel = Level1;
                ResetGame(&playerX, &playerY, &velocityY, &isGrounded, &canMove, &isJumping, &jumpDirection,
                    &verticalSpeed, &horizontalSpeed, &enemyX, &enemyY, &playerActive, &direction, &isDucking, &isAttacking,
                    &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                gameState = PLAYING;
            }
            break;
        }

        case PLAYING: {
            if (Music01) UpdateMusicStream(Stage01);

            bool duckKey = IsKeyDown(KEY_LEFT_SHIFT);
            bool attackKey = IsKeyDown(KEY_E);
            isDucking = false;
            isAttacking = false;

            if (!isJumping) {
                if (attackKey && Whip) {
                    AnimationSettings();
                    isAttacking = true;
                    canMove = false;
                }
                else if (attackKey && Star) {
                    if (!starBall.active && starCooldown <= 0.0f) {
                        starBall.active = true;
                        starBall.distance = 0.0f;
                        starBall.x = playerX + PLAYER_HITBOX_WIDTH / 2.0f;
                        starBall.y = playerY + PLAYER_HITBOX_HEIGHT / 2.0f;
                        starBall.direction = (direction == 0) ? 1.0f : -1.0f;
                        starCooldown = STAR_COOLDOWN_TIME;
                    }
                    canMove = true;
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
                    }
                    else if (newX < playerX) {
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
                    }
                    else if (horizontalSpeed < 0) {
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

                // --- TELETRANSPORTE AL TOCAR TILE 3 ---
                if (CheckTriggerCollision(playerX, playerY)) {
                    if (currentMap == 1) {
                        currentMap = 2;
                        currentLevel = Map2;
                        ResetGame(&playerX, &playerY, &velocityY, &isGrounded, &canMove, &isJumping, &jumpDirection,
                            &verticalSpeed, &horizontalSpeed, &enemyX, &enemyY, &playerActive, &direction, &isDucking, &isAttacking,
                            &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                    }
                    else {
                        gameState = WIN;
                    }
                }
            }

            if (starBall.active) {
                starBall.x += starBall.direction * PROJECTILE_SPEED;
                starBall.distance += PROJECTILE_SPEED;
                if (starBall.distance >= PROJECTILE_RANGE) starBall.active = false;
            }

            // Enemigo normal (solo en Nivel 1)
            if (currentMap == 1) {
                enemyX -= enemySpeed;
                if (playerX - enemyX >= 800.0f) {
                    enemyX = playerX + 800.0f;
                    if (enemyX + ENEMY_WIDTH > MAP_WIDTH * TILE_SIZE) enemyX = MAP_WIDTH * TILE_SIZE - ENEMY_WIDTH;
                }
                enemyY = GetEnemyGroundHeight(enemyX);

                if (playerActive) {
                    Rectangle playerHitbox = { playerX, playerY, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT };
                    Rectangle enemyRect = { enemyX, enemyY, ENEMY_WIDTH, ENEMY_HEIGHT };
                    Rectangle attackHitboxR = { playerX + 16, playerY, ATTACK_HITBOX_WIDTH, ATTACK_HITBOX_HEIGHT };
                    Rectangle attackHitboxL = { playerX - 10, playerY, ATTACK_HITBOX_WIDTH, ATTACK_HITBOX_HEIGHT };

                    if (attackKey && Whip) {
                        if (direction == 0 && CheckCollisionRecs(attackHitboxR, enemyRect)) enemyX = playerX + 800;
                        else if (direction == 1 && CheckCollisionRecs(attackHitboxL, enemyRect)) enemyX = playerX + 800;
                    }
                    if (starBall.active) {
                        Rectangle projectileRect = { starBall.x - ITEM_WIDTH / 2.0f, starBall.y - ITEM_HEIGHT / 2.0f, ITEM_WIDTH, ITEM_HEIGHT };
                        if (CheckCollisionRecs(projectileRect, enemyRect)) {
                            enemyX = playerX + 800.0f;
                            if (enemyX + ENEMY_WIDTH > MAP_WIDTH * TILE_SIZE) enemyX = MAP_WIDTH * TILE_SIZE - ENEMY_WIDTH;
                            starBall.active = false;
                        }
                    }
                    if (CheckCollisionRecs(playerHitbox, enemyRect) && !godMode) {
                        playerActive = false;
                        gameState = GAMEOVER;
                        gameOverSelection = 0;
                    }
                }
            }

            // ----- COMPORTAMIENTO DEL BOSS (SOLO EN MAPA 2) -----
            if (currentMap == 2 && boss.active) {
                if (boss.invulnerableTimer > 0.0f) {
                    boss.invulnerableTimer -= delta;
                }

                // Disparo de proyectiles
                if (boss.state == BOSS_FLYING) {
                    bossShootTimer += delta;
                    if (bossShootTimer >= BOSS_SHOOT_INTERVAL) {
                        bossShootTimer = 0.0f;
                        // Buscar un slot libre para el proyectil
                        for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) {
                            if (!bossProjectiles[i].active) {
                                bossProjectiles[i].active = true;
                                bossProjectiles[i].x = boss.x + BOSS_WIDTH / 2;
                                bossProjectiles[i].y = boss.y + BOSS_HEIGHT / 2;
                                float angle = atan2f(playerY + PLAYER_HITBOX_HEIGHT / 2 - bossProjectiles[i].y,
                                    playerX + PLAYER_HITBOX_WIDTH / 2 - bossProjectiles[i].x);
                                bossProjectiles[i].vx = cosf(angle) * BOSS_PROJECTILE_SPEED;
                                bossProjectiles[i].vy = sinf(angle) * BOSS_PROJECTILE_SPEED;
                                bossProjectiles[i].distance = 0.0f;
                                break;
                            }
                        }
                    }
                }

                // Actualizar proyectiles del boss
                for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) {
                    if (bossProjectiles[i].active) {
                        bossProjectiles[i].x += bossProjectiles[i].vx;
                        bossProjectiles[i].y += bossProjectiles[i].vy;
                        bossProjectiles[i].distance += BOSS_PROJECTILE_SPEED;

                        // Desactivar si sale del rango o de la pantalla
                        if (bossProjectiles[i].distance >= BOSS_PROJECTILE_RANGE ||
                            bossProjectiles[i].x < 0 || bossProjectiles[i].x > MAP_WIDTH * TILE_SIZE ||
                            bossProjectiles[i].y < 0 || bossProjectiles[i].y > MAP_HEIGHT * TILE_SIZE) {
                            bossProjectiles[i].active = false;
                        }

                        // Colisión con el jugador
                        Rectangle projRect = { bossProjectiles[i].x - 4, bossProjectiles[i].y - 4, 8, 8 };
                        Rectangle playerHitbox = { playerX, playerY, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT };
                        if (CheckCollisionRecs(projRect, playerHitbox) && playerActive && !godMode) {
                            playerActive = false;
                            gameState = GAMEOVER;
                            gameOverSelection = 0;
                        }
                    }
                }

                // Movimiento del boss con colisiones
                if (boss.state == BOSS_HANGING) {
                    float distanceToPlayer = fabs(playerX - boss.x);
                    if (distanceToPlayer < 400.0f) {
                        boss.state = BOSS_FLYING;
                        boss.stateTimer = 0.0f;
                    }
                }
                else if (boss.state == BOSS_FLYING) {
                    boss.flyTimer += 0.05f;
                    boss.stateTimer += delta;

                    // Movimiento horizontal hacia el jugador
                    float moveX = 0;
                    if (boss.x > playerX) moveX = -1.5f;
                    else if (boss.x < playerX) moveX = 1.5f;

                    Rectangle newRectX = { boss.x + moveX, boss.y, BOSS_WIDTH, BOSS_HEIGHT };
                    if (!CheckTileCollision(newRectX)) {
                        boss.x += moveX;
                    }

                    // Movimiento vertical (persecución suave + senoidal)
                    float targetY = playerY - 50.0f;
                    float moveY = 0;
                    if (boss.y < targetY) moveY = 1.0f;
                    else if (boss.y > targetY) moveY = -1.0f;
                    moveY += sinf(boss.flyTimer) * 4.0f;

                    Rectangle newRectY = { boss.x, boss.y + moveY, BOSS_WIDTH, BOSS_HEIGHT };
                    if (!CheckTileCollision(newRectY)) {
                        boss.y += moveY;
                    }

                    if (boss.y < 0) boss.y = 0;
                    if (boss.y > MAP_HEIGHT * TILE_SIZE - BOSS_HEIGHT) boss.y = MAP_HEIGHT * TILE_SIZE - BOSS_HEIGHT;

                    if (boss.stateTimer >= 4.0f) {
                        boss.state = BOSS_RESTING;
                        boss.stateTimer = 0.0f;
                    }
                }
                else if (boss.state == BOSS_RESTING) {
                    boss.stateTimer += delta;
                    // Bajar al suelo de la sala
                    float groundY = 11 * TILE_SIZE - BOSS_HEIGHT; // 374 - 37 = 337
                    if (boss.y < groundY) {
                        boss.y += 2.0f;
                        if (boss.y > groundY) boss.y = groundY;
                    }

                    // También evitar atravesar tiles mientras baja
                    Rectangle restRect = { boss.x, boss.y, BOSS_WIDTH, BOSS_HEIGHT };
                    if (CheckTileCollision(restRect)) {
                        boss.y = groundY; // Forzar al suelo si toca un tile
                    }

                    if (boss.stateTimer >= 2.0f) {
                        boss.state = BOSS_FLYING;
                        boss.stateTimer = 0.0f;
                    }
                }

                // Daño del jugador al boss
                Rectangle bossHitbox = { boss.x, boss.y, BOSS_WIDTH, BOSS_HEIGHT };
                Rectangle attackHitbox = { playerX, playerY, ATTACK_HITBOX_WIDTH, ATTACK_HITBOX_HEIGHT };

                if (isAttacking && boss.invulnerableTimer <= 0.0f && CheckCollisionRecs(attackHitbox, bossHitbox)) {
                    boss.hp -= 1;
                    boss.invulnerableTimer = 0.5f;
                    boss.x += (direction == 0) ? 15.0f : -15.0f;

                    if (boss.hp <= 0) {
                        boss.active = false;
                        gameState = WIN;
                    }
                }

                // Daño del boss al jugador (contacto directo)
                Rectangle playerHitbox = { playerX, playerY, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT };
                if (CheckCollisionRecs(playerHitbox, bossHitbox) && playerActive && !godMode) {
                    playerActive = false;
                    gameState = GAMEOVER;
                    gameOverSelection = 0;
                }
            }

            // --- ACTUALIZACIÓN DE CÁMARA ---
            if (currentMap == 2) {
                camera.target = (Vector2){ playerX + PLAYER_HITBOX_WIDTH / 2, playerY + PLAYER_HITBOX_HEIGHT / 2 };
            }
            else {
                camera.target = (Vector2){ playerX + PLAYER_HITBOX_WIDTH / 2, 290.0f };
            }
            break;
        }

        case CHEAT_MENU: {
            if (IsKeyPressed(KEY_F1) || IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
                gameState = PLAYING;
                break;
            }

            Vector2 mousePos = GetMousePosition();
            float menuCenterX = SCREEN_WIDTH / 2.0f;
            Rectangle godRect = { menuCenterX - 150, 170, 300, 40 };
            Rectangle tpRect = { menuCenterX - 150, 220, 300, 40 };

            if (IsKeyPressed(KEY_UP)) {
                cheatSelection--;
                if (cheatSelection < 0) cheatSelection = 1;
            }
            if (IsKeyPressed(KEY_DOWN)) {
                cheatSelection++;
                if (cheatSelection > 1) cheatSelection = 0;
            }

            if (CheckCollisionPointRec(mousePos, godRect)) cheatSelection = 0;
            else if (CheckCollisionPointRec(mousePos, tpRect)) cheatSelection = 1;

            if (IsKeyPressed(KEY_ENTER) ||
                (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, godRect))) {
                if (cheatSelection == 0) {
                    godMode = !godMode;
                }
            }
            if (IsKeyPressed(KEY_ENTER) ||
                (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, tpRect))) {
                if (cheatSelection == 1) {
                    currentMap = 2;
                    currentLevel = Map2;
                    ResetGame(&playerX, &playerY, &velocityY, &isGrounded, &canMove, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed, &enemyX, &enemyY, &playerActive, &direction, &isDucking, &isAttacking,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                    gameState = PLAYING;
                }
            }

            Rectangle closeRect = { menuCenterX - 120, 395, 240, 25 };
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, closeRect)) {
                gameState = PLAYING;
            }
            break;
        }

        case GAMEOVER: {
            if (IsKeyPressed(KEY_UP)) { gameOverSelection--; if (gameOverSelection < 0) gameOverSelection = 1; }
            if (IsKeyPressed(KEY_DOWN)) { gameOverSelection++; if (gameOverSelection > 1) gameOverSelection = 0; }
            if (IsKeyPressed(KEY_ENTER)) {
                if (gameOverSelection == 0) {
                    ResetGame(&playerX, &playerY, &velocityY, &isGrounded, &canMove, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed, &enemyX, &enemyY, &playerActive, &direction, &isDucking, &isAttacking,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                    gameState = PLAYING;
                }
                else if (gameOverSelection == 1) { gameState = EXIT; }
            }
            Vector2 mousePos = GetMousePosition();
            Rectangle tryAgainBtn = { SCREEN_WIDTH / 2.0f - 60, SCREEN_HEIGHT / 2.0f + 10, 120, 30 };
            Rectangle exitBtn = { SCREEN_WIDTH / 2.0f - 60, SCREEN_HEIGHT / 2.0f + 50, 120, 30 };
            if (CheckCollisionPointRec(mousePos, tryAgainBtn)) {
                gameOverSelection = 0;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    ResetGame(&playerX, &playerY, &velocityY, &isGrounded, &canMove, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed, &enemyX, &enemyY, &playerActive, &direction, &isDucking, &isAttacking,
                        &camera, SCREEN_WIDTH, SCREEN_HEIGHT);
                    gameState = PLAYING;
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                gameOverSelection = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { gameState = EXIT; }
            }
            break;
        }
        case WIN: {
            if (IsKeyPressed(KEY_UP)) { winSelection--; if (winSelection < 0) winSelection = 1; }
            if (IsKeyPressed(KEY_DOWN)) { winSelection++; if (winSelection > 1) winSelection = 0; }
            if (IsKeyPressed(KEY_ENTER)) {
                if (winSelection == 0) { gameState = MENU; menuSelection = 0; }
                else if (winSelection == 1) { CloseIt = true; }
            }
            Vector2 mousePos = GetMousePosition();
            Rectangle menuBtn = { SCREEN_WIDTH / 2.0f - 80, SCREEN_HEIGHT / 2.0f + 10, 160, 30 };
            Rectangle exitBtn = { SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f + 50, 100, 30 };
            if (CheckCollisionPointRec(mousePos, menuBtn)) {
                winSelection = 0;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { gameState = MENU; menuSelection = 0; }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                winSelection = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { CloseIt = true; }
            }
            break;
        }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        switch (gameState) {
        case MENU: {
            const char* title = "CASTLEVANIA";
            int titleFontSize = 30;
            DrawText(title, (SCREEN_WIDTH - MeasureText(title, titleFontSize)) / 2, SCREEN_HEIGHT / 2 - 80, titleFontSize, RED);
            const char* playText = "Enter ?\n ";
            const char* exitText = "Run Away \n[Coward.]";
            int optionFontSize = 30;
            Color playColor = (menuSelection == 0) ? YELLOW : WHITE;
            Color exitColor = (menuSelection == 1) ? YELLOW : WHITE;
            DrawText(playText, (SCREEN_WIDTH - MeasureText(playText, optionFontSize)) / 2, SCREEN_HEIGHT / 2 - 20, optionFontSize, playColor);
            DrawText(exitText, (SCREEN_WIDTH - MeasureText(exitText, optionFontSize)) / 2, SCREEN_HEIGHT / 2 + 30, optionFontSize, exitColor);
            const char* instr = "Use ARROWS and ENTER or click";
            int instrFontSize = 15;
            DrawText(instr, (SCREEN_WIDTH - MeasureText(instr, instrFontSize)) / 2, SCREEN_HEIGHT - 40, instrFontSize, GRAY);
            break;
        }

        case PLAYING: {
            BeginMode2D(camera);

            if (currentMap == 1) DrawTextureEx(fondo, (Vector2) { 0, 0 }, 0, 2.0f, WHITE);
            else DrawTextureEx(fondo2, (Vector2) { 1, 1 }, 0, 0.5f, WHITE);

            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    if (currentLevel[y][x] == 1) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
                    }
                    else if (currentLevel[y][x] == 3) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, MAROON);
                    }
                }
            }

            // Dibujar enemigo normal solo en Nivel 1
            if (currentMap == 1) {
                Rectangle enemySource = { Enemy.Frame * 17, 0, ENEMY_WIDTH, ENEMY_HEIGHT };
                Rectangle enemyDest = { enemyX, enemyY, ENEMY_WIDTH, ENEMY_HEIGHT };
                DrawTexturePro(enemyTex, enemySource, enemyDest, (Vector2) { 0, 0 }, 0, WHITE);
            }

            // Dibujar boss en Mapa 2
            if (currentMap == 2 && boss.active) {
                int bossFrame = 0;
                if (boss.state == BOSS_HANGING) {
                    bossFrame = 0;
                }
                else {
                    bossFrame = 1 + (Enemy.Frame % 2);
                }

                Rectangle bossSource = { bossFrame * BOSS_WIDTH, 0, BOSS_WIDTH, BOSS_HEIGHT };
                Rectangle bossDest = { boss.x, boss.y, BOSS_WIDTH, BOSS_HEIGHT };

                if (boss.x < playerX) {
                    bossSource.width = -BOSS_WIDTH;
                }

                Color drawColor = WHITE;
                if (boss.invulnerableTimer > 0.0f) {
                    drawColor = ((int)(boss.invulnerableTimer * 20) % 2 == 0) ? RED : BLANK;
                }

                DrawTexturePro(bossTex, bossSource, bossDest, (Vector2) { 0, 0 }, 0, drawColor);
            }

            // Dibujar proyectiles del boss
            for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) {
                if (bossProjectiles[i].active) {
                    DrawCircle((int)bossProjectiles[i].x, (int)bossProjectiles[i].y, 6, RED);
                }
            }

            DrawRectangle(playerX - 200, 395, SCREEN_WIDTH, 210, BLACK);

            if (playerActive) {
                Rectangle source;
                float spriteOffsetX = (PLAYER_SPRITE_WIDTH - PLAYER_HITBOX_WIDTH) / 2.0f;
                Rectangle dest = { playerX - spriteOffsetX, playerY, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                Texture2D textureToDraw;
                bool usePro = true;
                bool attackDucking = isAttacking && IsKeyDown(KEY_LEFT_SHIFT);

                if (isAttacking && Whip) {
                    source = (Rectangle){ Attacker.Frame * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT };
                    if (attackDucking) textureToDraw = (direction == 0) ? attackR_C : attackL_C;
                    else textureToDraw = (direction == 0) ? attackR : attackL;
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
                    if (direction == 0) DrawTextureEx(idleR, (Vector2) { dest.x, dest.y }, 0, 1, WHITE);
                    else DrawTextureEx(idleL, (Vector2) { dest.x, dest.y }, 0, 1, WHITE);
                }
                if (usePro) DrawTexturePro(textureToDraw, source, dest, (Vector2) { 0, 0 }, 0, WHITE);
            }

            if (starBall.active) {
                DrawTextureEx(starProjectileTex,
                    (Vector2) {
                    starBall.x - ITEM_WIDTH / 2.0f, starBall.y - ITEM_HEIGHT / 2.0f
                },
                    0, 1.0f, WHITE);
            }

            if (IsKeyPressed(KEY_ONE)) { Whip = true; Star = false; }
            if (CollectStar && IsKeyPressed(KEY_TWO)) { Whip = false; Star = true; }
            if (Whip) DrawTextureEx(Item1, (Vector2) { 250 + playerX, 400 }, 0, 1, WHITE);
            if (Star) DrawTextureEx(Item2, (Vector2) { 250 + playerX, 400 }, 0, 1, WHITE);

            if (CollectStar == false)
            {
                Rectangle playerHitbox = { playerX, playerY, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT };
                Rectangle StarHitbox = { 400, 342, ITEM_WIDTH, ITEM_HEIGHT };
                DrawTextureEx(Weapon2, (Vector2) { 400, 358 }, 0, 1, WHITE);
                if (CheckCollisionRecs(playerHitbox, StarHitbox))
                {
                    StartTimer(&Collection, Warning);
                    CollectStar = true;
                    Tick = 0;
                }
            }

            UpdateTimer(&Collection);
            if (!TimerDone(&Collection))
            {
                Tick += 0.1f;
                if ((int)Tick % 2 == 0)
                {
                    DrawRectangle(400, 358, MeasureText("PRESS 2!!!", 10), 10, BLACK);
                    DrawText("PRESS 2!!!", 400, 358, 10, RED);
                }
                else
                {
                    DrawRectangle(400, 358, MeasureText("PRESS 2!!!", 10), 10, BLACK);
                    DrawText("PRESS 2!!!", 400, 358, 10, WHITE);
                }
            }

            DrawLine(MAP_WIDTH * TILE_SIZE, 0, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, WHITE);
            DrawRectangle((MAP_WIDTH - 1) * TILE_SIZE, 0, TILE_SIZE, MAP_HEIGHT * TILE_SIZE, (Color) { 255, 0, 0, 100 });

            EndMode2D();

            blinkCounter++;
            Rectangle indicatorRect = { SCREEN_WIDTH - 170.0f, 10.0f, 160.0f, 30.0f };
            DrawRectangleRec(indicatorRect, Fade(BLACK, 0.7f));
            if ((blinkCounter / 30) % 2 == 0) {
                DrawText("[CHEATS: F1]", SCREEN_WIDTH - 160, 15, 18, YELLOW);
            }
            if (godMode) {
                DrawText("[GOD MODE]", SCREEN_WIDTH - 160, 35, 15, RED);
            }

            if (CheckCollisionPointRec(GetMousePosition(), indicatorRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                gameState = CHEAT_MENU;
                cheatSelection = 0;
            }
            break;
        }

        case CHEAT_MENU: {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color) { 0, 0, 0, 200 });
            const char* title = "CHEATS";
            int titleSize = 40;
            DrawText(title, SCREEN_WIDTH / 2 - MeasureText(title, titleSize) / 2, 80, titleSize, RED);
            const char* godModeText = TextFormat("God Mode: %s", godMode ? "ON" : "OFF");
            int optSize = 30;
            Color godColor = (cheatSelection == 0) ? YELLOW : WHITE;
            DrawText(godModeText, SCREEN_WIDTH / 2 - MeasureText(godModeText, optSize) / 2, 180, optSize, godColor);
            const char* tpText = "Teleport to Boss Room";
            Color tpColor = (cheatSelection == 1) ? YELLOW : WHITE;
            DrawText(tpText, SCREEN_WIDTH / 2 - MeasureText(tpText, optSize) / 2, 230, optSize, tpColor);
            const char* instr = "Press F1, P, ESC or click here to close";
            int instrSize = 20;
            DrawText(instr, SCREEN_WIDTH / 2 - MeasureText(instr, instrSize) / 2, 400, instrSize, GRAY);
            break;
        }

        case GAMEOVER: {
            const char* gameOverText = "GAME OVER";
            int goFontSize = 40;
            DrawText(gameOverText, (SCREEN_WIDTH - MeasureText(gameOverText, goFontSize)) / 2, SCREEN_HEIGHT / 2 - 60, goFontSize, RED);
            const char* tryAgainText = "Try Again";
            const char* exitText = "PERISH";
            int optFontSize = 25;
            Color tryAgainColor = (gameOverSelection == 0) ? YELLOW : WHITE;
            Color exitColor = (gameOverSelection == 1) ? YELLOW : WHITE;
            DrawText(tryAgainText, (SCREEN_WIDTH - MeasureText(tryAgainText, optFontSize)) / 2, SCREEN_HEIGHT / 2 + 10, optFontSize, tryAgainColor);
            DrawText(exitText, (SCREEN_WIDTH - MeasureText(exitText, optFontSize)) / 2, SCREEN_HEIGHT / 2 + 50, optFontSize, exitColor);
            const char* instr = "Use ARROWS and ENTER or click";
            int instrFontSize = 15;
            DrawText(instr, (SCREEN_WIDTH - MeasureText(instr, instrFontSize)) / 2, SCREEN_HEIGHT - 40, instrFontSize, GRAY);
            break;
        }

        case WIN: {
            const char* winText = "LEVEL WIN";
            int winFontSize = 40;
            DrawText(winText, (SCREEN_WIDTH - MeasureText(winText, winFontSize)) / 2, SCREEN_HEIGHT / 2 - 60, winFontSize, GREEN);
            const char* menuText = "Return to Menu";
            const char* exitText = "Exit";
            int optFontSize = 25;
            Color menuColor = (winSelection == 0) ? YELLOW : WHITE;
            Color exitColor = (winSelection == 1) ? YELLOW : WHITE;
            DrawText(menuText, (SCREEN_WIDTH - MeasureText(menuText, optFontSize)) / 2, SCREEN_HEIGHT / 2 + 10, optFontSize, menuColor);
            DrawText(exitText, (SCREEN_WIDTH - MeasureText(exitText, optFontSize)) / 2, SCREEN_HEIGHT / 2 + 50, optFontSize, exitColor);
            const char* instr = "Use ARROWS and ENTER or click";
            int instrFontSize = 15;
            DrawText(instr, (SCREEN_WIDTH - MeasureText(instr, instrFontSize)) / 2, SCREEN_HEIGHT - 40, instrFontSize, GRAY);
            break;
        }
        }

        EndDrawing();
    }

    UnloadMusicStream(musicaFondo);
    UnloadMusicStream(Stage01);
    CloseAudioDevice();

    UnloadTexture(idleR); UnloadTexture(idleL); UnloadTexture(walkR); UnloadTexture(walkL);
    UnloadTexture(jumpR); UnloadTexture(jumpL); UnloadTexture(duckR); UnloadTexture(duckL);
    UnloadTexture(attackR); UnloadTexture(attackL); UnloadTexture(attackR_C); UnloadTexture(attackL_C);
    UnloadTexture(enemyTex); UnloadTexture(Item1); UnloadTexture(Item2);
    UnloadTexture(starProjectileTex);
    UnloadTexture(fondo); UnloadTexture(fondo2);
    UnloadTexture(bossTex);
    CloseWindow();
    return 0;
}