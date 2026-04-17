/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/
*/

#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#define Spring_Width 16
#define Spring_Height 31
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

// Estados del juego
typedef enum GameState {
    MENU,
    PLAYING,
    GAMEOVER
} GameState;

// Structure for animation frames
struct Animation
{
	int Frame /*= 0*/;
	int Counter /*= 0*/;
	int Speed /*= 5*/;
} Spring, Enemy;

// Function to handle animation frame cycling
void AnimationSettings()
{
    Spring.Counter++;
    if (Spring.Counter >= (100 / Spring.Speed))
    {
        Spring.Counter = 0;
        Spring.Frame++;

		if (Spring.Frame > 2) Spring.Frame = 0;
	}

	Enemy.Counter++;
	if (Enemy.Counter >= (100 / Enemy.Speed))
	{
		Enemy.Counter = 0;
		Enemy.Frame++;

		if (Enemy.Frame > 2) Enemy.Frame = 0;
	}
}

// Funci�n para reiniciar todas las variables del juego
void ResetGame(float* x, float* y, float* ballX, float* ballY,
    bool* playerActive, bool* isJumping, int* jumpDirection,
    float* verticalSpeed, float* horizontalSpeed, bool* canMove,
    int* Direction, int screenWidth, int Floor)
{
    *x = 200;
    *y = 175;
    *ballX = screenWidth;       // Reaparece desde la derecha
    *ballY = Floor;
    *playerActive = true;
    *isJumping = false;
    *jumpDirection = 0;
    *verticalSpeed = 0;
    *horizontalSpeed = 0;
    *canMove = true;
    *Direction = 0;
    Spring.Frame = 0;
    Spring.Counter = 0;
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
	Enemy.Speed = 7;

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

	// Variables de la bola (obst�culo)
	float ballX = 400;           // Aparece desde la derecha (ancho de pantalla)
	float ballY = Floor;         // Misma altura que el suelo (top de la colisi�n)
	float ballSpeed = 1.0f;      // Velocidad hacia la izquierda
	bool playerActive = true;    // Si el personaje est� activo (no colisionado)

	//---------------------------------------------------

    //------------------Window--------------------
    int screenWidth = 400; //X
    int screenHeight = 350; //Y

    InitWindow(screenWidth, screenHeight, "_C4STL3V4N14_");
    //---------------------------------------------

    //------------------Textures--------------------
    SearchAndSetResourceDir("resources"); // Utility function from resource_dir.h

    Texture Rabbit = LoadTexture("Idle.png");
    Texture Rabbit_O = LoadTexture("Idle_Sided.png");

    Texture AnimR = LoadTexture("Walking_R.png");
    Texture AnimL = LoadTexture("Walking_L.png");

	Texture JumpR = LoadTexture("Jump_R.png");
	Texture JumpL = LoadTexture("Jump_L.png");

	Texture CreatureL = LoadTexture("Zombie_L.png");

	//-----------------------------------------------

    //------------------Gameplay Loop--------------------
    while (!WindowShouldClose())		// Detecta ESC o cierre de ventana
    {
        //------------------Actualizaci�n seg�n estado--------------------
        switch (gameState)
        {
        case MENU:
        {
            // Navegaci�n con teclado
            if (IsKeyPressed(KEY_UP)) {
                menuSelection--;
                if (menuSelection < 0) menuSelection = 1;
            }
            if (IsKeyPressed(KEY_DOWN)) {
                menuSelection++;
                if (menuSelection > 1) menuSelection = 0;
            }

            // Selecci�n con Enter
            if (IsKeyPressed(KEY_ENTER)) {
                if (menuSelection == 0) {
                    gameState = PLAYING;
                    ResetGame(&x, &y, &ballX, &ballY, &playerActive, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed, &canMove, &Direction, screenWidth, Floor);
                }
                else if (menuSelection == 1) {
                    break;  // Saldr� del bucle principal (WindowShouldClose se pondr� true)
                }
            }

            // Interacci�n con rat�n
            Vector2 mousePos = GetMousePosition();

            // Definir �reas para los textos (Play y Exit)
            Rectangle playBtn = { screenWidth / 2.0f - 50, screenHeight / 2.0f - 20, 100, 30 };
            Rectangle exitBtn = { screenWidth / 2.0f - 50, screenHeight / 2.0f + 20, 100, 30 };

            if (CheckCollisionPointRec(mousePos, playBtn)) {
                menuSelection = 0;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    gameState = PLAYING;
                    ResetGame(&x, &y, &ballX, &ballY, &playerActive, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed, &canMove, &Direction, screenWidth, Floor);
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                menuSelection = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    break;  // Salir
                }
            }
        }
        break;

        case PLAYING:
        {
            //------------------Actualizaci�n de la bola--------------------
            ballX -= ballSpeed;
            if (ballX + Spring_Width < 0) {
                ballX = screenWidth;
            }

            //------------------Movimiento del personaje (solo si est� activo)--------------------
            if (playerActive) {
                // Manejar el salto
                if (canMove && !isJumping)
                {
                    if (IsKeyPressed(KEY_SPACE))
                    {
                        isJumping = true;
                        canMove = false;
                        verticalSpeed = initialJumpSpeed;
                        startX = x;

                        if (IsKeyDown(KEY_D))
                        {
                            jumpDirection = 1;
                            Direction = 0;
                            horizontalSpeed = vX + 1.5;
                        }
                        else if (IsKeyDown(KEY_A))
                        {
                            jumpDirection = -1;
                            Direction = 1;
                            horizontalSpeed = vX + 1.5;
                        }
                        else
                        {
                            jumpDirection = 0;
                            horizontalSpeed = 0;
                        }
                    }
                }

                // F�sica del salto
                if (isJumping)
                {
                    verticalSpeed += G + 0.02f;
                    y += verticalSpeed;

                    if (jumpDirection == 1)
                        x += horizontalSpeed;
                    else if (jumpDirection == -1)
                        x -= horizontalSpeed;

                    if (y >= Floor)
                    {
                        y = Floor;
                        isJumping = false;
                        canMove = true;
                        verticalSpeed = 0;
                        jumpDirection = 0;
                        horizontalSpeed = 0;
                    }

                    if (y < 0) {
                        y = 0;
                        verticalSpeed = 0;
                    }
                }

                // Movimiento en el suelo
                if (canMove && !isJumping)
                {
                    y += G;

                    if (IsKeyDown(KEY_D))
                    {
                        x += vX;
                        Direction = 0;
                    }
                    else if (IsKeyDown(KEY_A))
                    {
                        x -= vX;
                        Direction = 1;
                    }

                    if (y >= Floor)
                        y = Floor;
                }

                // L�mites de pantalla
                if (x > screenWidth - 15) x = screenWidth - 15;
                if (x < -5) x = -5;
                if (y > screenHeight - 100) y = screenHeight - 100;
            }

            //------------------Colisi�n entre personaje y bola--------------------
            if (playerActive) {
                Rectangle playerRect = { x, y, Spring_Width, Spring_Height };
                Rectangle ballRect = { ballX, ballY, Spring_Width, Spring_Height };

                if (CheckCollisionRecs(playerRect, ballRect)) {
                    playerActive = false;
                    gameState = GAMEOVER;
                    gameOverSelection = 0;  // Por defecto "Try Again"
                }
            }
        }
        break;

        case GAMEOVER:
        {
            // Navegaci�n con teclado
            if (IsKeyPressed(KEY_UP)) {
                gameOverSelection--;
                if (gameOverSelection < 0) gameOverSelection = 1;
            }
            if (IsKeyPressed(KEY_DOWN)) {
                gameOverSelection++;
                if (gameOverSelection > 1) gameOverSelection = 0;
            }

            // Selecci�n con Enter
            if (IsKeyPressed(KEY_ENTER)) {
                if (gameOverSelection == 0) {
                    // Try Again
                    gameState = PLAYING;
                    ResetGame(&x, &y, &ballX, &ballY, &playerActive, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed, &canMove, &Direction, screenWidth, Floor);
                }
                else if (gameOverSelection == 1) {
                    break;  // Exit -> cierra aplicaci�n
                }
            }

            // Interacci�n con rat�n
            Vector2 mousePos = GetMousePosition();

            Rectangle tryAgainBtn = { screenWidth / 2.0f - 60, screenHeight / 2.0f + 10, 120, 30 };
            Rectangle exitBtn = { screenWidth / 2.0f - 60, screenHeight / 2.0f + 50, 120, 30 };

            if (CheckCollisionPointRec(mousePos, tryAgainBtn)) {
                gameOverSelection = 0;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    gameState = PLAYING;
                    ResetGame(&x, &y, &ballX, &ballY, &playerActive, &isJumping, &jumpDirection,
                        &verticalSpeed, &horizontalSpeed, &canMove, &Direction, screenWidth, Floor);
                }
            }
            else if (CheckCollisionPointRec(mousePos, exitBtn)) {
                gameOverSelection = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    break;
                }
            }
        }
        break;
        }

        //------------------Dibujado--------------------
        BeginDrawing();
        ClearBackground(BLACK);

        switch (gameState)
        {
        case MENU:
        {
            // T�tulo centrado
            const char* title = "CASTLEVANIA";
            int titleFontSize = 30;
            int titleWidth = MeasureText(title, titleFontSize);
            DrawText(title, (screenWidth - titleWidth) / 2, screenHeight / 2 - 80, titleFontSize, RED);

            // Opciones centradas
            const char* playText = "Play";
            const char* exitText = "Exit";
            int optionFontSize = 30;
            int playWidth = MeasureText(playText, optionFontSize);
            int exitWidth = MeasureText(exitText, optionFontSize);

            Color playColor = (menuSelection == 0) ? YELLOW : WHITE;
            Color exitColor = (menuSelection == 1) ? YELLOW : WHITE;

            DrawText(playText, (screenWidth - playWidth) / 2, screenHeight / 2 - 20, optionFontSize, playColor);
            DrawText(exitText, (screenWidth - exitWidth) / 2, screenHeight / 2 + 20, optionFontSize, exitColor);

            // Instrucciones centradas
            const char* instr = "Use ARROWS and ENTER or click";
            int instrFontSize = 15;
            int instrWidth = MeasureText(instr, instrFontSize);
            DrawText(instr, (screenWidth - instrWidth) / 2, screenHeight - 40, instrFontSize, GRAY);
        }
        break;

        case PLAYING:
        {
            // Mensaje (opcional, puedes quitarlo)
            DrawText("You should KILL YOURSELF NOW!", 30, 100, 20, PURPLE);

		// Dibujar la bola (c�rculo rojo con el mismo centro que su rect�ngulo de colisi�n)
		Vector2 ballCenter = { ballX + Spring_Width / 2.0f, ballY + Spring_Height / 2.0f };
		float ballRadius = Spring_Width / 2.0f;
		AnimationSettings();
		Rectangle source = (Rectangle){ Enemy.Frame * 16.5, 0, Spring_Width, Spring_Height };
		Rectangle dest = (Rectangle){ ballX, ballY, Spring_Width, Spring_Height };
		DrawTexturePro(CreatureL, source, dest, (Vector2) { 0, 0 }, 0, WHITE);

		// Opcional: dibujar el rect�ngulo de colisi�n (descomentar para debug)
		// DrawRectangleLines(ballX, ballY, Spring_Width, Spring_Height, GREEN);

		// Dibujar el personaje solo si est� activo
		if (playerActive) {
			// Dibujar animaci�n cuando est� en movimiento en el suelo
			if (canMove && !isJumping && (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)))
			{
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
		}
		else {
			// Si el personaje est� desactivado, mostrar mensaje de Game Over
			DrawText("GAME OVER", screenWidth / 2 - 60, screenHeight / 2, 30, RED);
		}

            // Dibujar el suelo
            DrawRectangle(0, 233, screenWidth, 10, WHITE);
        }
        break;

        case GAMEOVER:
        {
            // "GAME OVER" centrado
            const char* gameOverText = "GAME OVER";
            int goFontSize = 40;
            int goWidth = MeasureText(gameOverText, goFontSize);
            DrawText(gameOverText, (screenWidth - goWidth) / 2, screenHeight / 2 - 60, goFontSize, RED);

            // Opciones centradas
            const char* tryAgainText = "Try Again";
            const char* exitText = "Exit";
            int optFontSize = 25;
            int tryAgainWidth = MeasureText(tryAgainText, optFontSize);
            int exitWidth = MeasureText(exitText, optFontSize);

            Color tryAgainColor = (gameOverSelection == 0) ? YELLOW : WHITE;
            Color exitColor = (gameOverSelection == 1) ? YELLOW : WHITE;

            DrawText(tryAgainText, (screenWidth - tryAgainWidth) / 2, screenHeight / 2 + 10, optFontSize, tryAgainColor);
            DrawText(exitText, (screenWidth - exitWidth) / 2, screenHeight / 2 + 50, optFontSize, exitColor);

            // Instrucciones centradas
            const char* instr = "Use ARROWS and ENTER or click";
            int instrFontSize = 15;
            int instrWidth = MeasureText(instr, instrFontSize);
            DrawText(instr, (screenWidth - instrWidth) / 2, screenHeight - 40, instrFontSize, GRAY);
        }
        break;
        }

        EndDrawing();
    }
    //---------------------------------------------------

    //-----------------Cleanup-----------------
    UnloadTexture(Rabbit);
    UnloadTexture(Rabbit_O);
    UnloadTexture(AnimL);
    UnloadTexture(AnimR);
    UnloadTexture(JumpR);
    UnloadTexture(JumpL);
    CloseWindow();
    return 0;
}