/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

Corregido y ampliado para incluir mapa, fondo, animaciones y físicas.
*/

#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "resource_dir.h"   // utility header for SearchAndSetResourceDir

// ---------- Constantes del mapa y pantalla ----------
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450
#define TILE_SIZE     32
#define MAP_WIDTH     25
#define MAP_HEIGHT    10

// ---------- Mapa (0 = vacío, 1 = suelo sólido) ----------
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// ---------- Estructura de animación (para el conejo) ----------
#define SPRING_WIDTH  32   // asumimos ancho del sprite de animación
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

// ---------- Función principal ----------
int main() {
    // Configuración de ventana
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "_C4STL3V4N14_");
    SearchAndSetResourceDir("resources");   // buscar carpeta resources

    // Cargar texturas
    Texture2D rabbitIdleR = LoadTexture("wabbit_alpha.png");
    Texture2D rabbitIdleL = LoadTexture("OtherSide.png");
    Texture2D animR = LoadTexture("Anim_R.png");
    Texture2D animL = LoadTexture("Anim_L.png");
    Texture2D fondo = LoadTexture("castevania.png");

    if (fondo.id == 0) {
        TraceLog(LOG_ERROR, "No se pudo cargar la imagen 'castlevania.png'");
    }
    SetTextureFilter(fondo, TEXTURE_FILTER_POINT);

    // Variables del jugador
    float playerX = 200.0f;
    float playerY = 0.0f;
    float velocityY = 0.0f;
    const float GRAVITY = 0.8f;
    const float JUMP_FORCE = -12.0f;
    bool isGrounded = false;
    int direction = 0;          // 0 = derecha, 1 = izquierda
    bool isMoving = false;
    float moveSpeed = 3.0f;

    // Configurar animación
    Spring.Speed = 5;
    Spring.Frame = 0;
    Spring.Counter = 0;

    // Cámara que sigue al jugador
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.zoom = 2.0f;

    SetTargetFPS(60);

    // Bucle principal
    while (!WindowShouldClose()) {
        // ----- Actualizar animación -----
        AnimationSettings();

        // ----- Movimiento horizontal -----
        isMoving = false;
        if (IsKeyDown(KEY_D)) {
            playerX += moveSpeed;
            direction = 0;   // derecha
            isMoving = true;
        }
        if (IsKeyDown(KEY_A)) {
            playerX -= moveSpeed;
            direction = 1;   // izquierda
            isMoving = true;
        }

        // ----- Gravedad y salto -----
        velocityY += GRAVITY;
        playerY += velocityY;

        // Colisión con el suelo (piso del mapa: fila MAP_HEIGHT-1)
        int tileX = (int)(playerX + SPRING_WIDTH / 2) / TILE_SIZE;
        int tileY = (int)(playerY + SPRING_HEIGHT) / TILE_SIZE;
        if (tileY >= MAP_HEIGHT) tileY = MAP_HEIGHT - 1;
        if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
            if (map[tileY][tileX] == 1) {
                // Ajustar posición arriba del tile
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

        // Salto
        if (isGrounded && IsKeyPressed(KEY_SPACE)) {
            velocityY = JUMP_FORCE;
            isGrounded = false;
        }

        // Límites de pantalla (opcional, para no salirse del todo)
        if (playerX < 0) playerX = 0;
        if (playerX > SCREEN_WIDTH - SPRING_WIDTH) playerX = SCREEN_WIDTH - SPRING_WIDTH;

        // Actualizar cámara (sigue al jugador)
        camera.target = (Vector2){ playerX + SPRING_WIDTH / 2, playerY + SPRING_HEIGHT / 2 };

        // ----- Dibujar -----
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        // 1. Dibujar fondo (textura)
        DrawTextureEx(fondo, (Vector2) { 0, 0 }, 0, 2.0f, WHITE);

        // 2. Dibujar mapa (tiles sólidos)
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x] == 1) {
                    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
                }
            }
        }

        // 3. Dibujar jugador según estado (movimiento o quieto, dirección)
        Rectangle sourceRect = { Spring.Frame * SPRING_WIDTH, 0, SPRING_WIDTH, SPRING_HEIGHT };
        Rectangle destRect = { playerX, playerY, SPRING_WIDTH, SPRING_HEIGHT };
        Vector2 origin = { 0, 0 };   // esquina superior izquierda

        if (isMoving) {
            if (direction == 0) {
                DrawTexturePro(animR, sourceRect, destRect, origin, 0, WHITE);
            }
            else {
                DrawTexturePro(animL, sourceRect, destRect, origin, 0, WHITE);
            }
        }
        else {
            // Quieto: usar textura idle según dirección
            if (direction == 0) {
                DrawTextureEx(rabbitIdleR, (Vector2) { playerX, playerY }, 0, 1.0f, WHITE);
            }
            else {
                DrawTextureEx(rabbitIdleL, (Vector2) { playerX, playerY }, 0, 1.0f, WHITE);
            }
        }

        EndMode2D();

        // Mensaje de error si no se cargó el fondo
        if (fondo.id == 0) {
            DrawText("ERROR: No se cargo la imagen 'castlevania.png'", 10, 10, 20, RED);
        }

        EndDrawing();
    }

    // Liberar recursos
    UnloadTexture(rabbitIdleR);
    UnloadTexture(rabbitIdleL);
    UnloadTexture(animR);
    UnloadTexture(animL);
    UnloadTexture(fondo);
    CloseWindow();

    return 0;
}