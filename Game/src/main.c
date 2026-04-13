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

#define Spring_Width  32
#define Spring_Height 32

struct Animation {
    int Frame;
    int Counter;
    int Speed;
} Spring;

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
	SearchAndSetResourceDir("resources"); // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it

	Texture Rabbit = LoadTexture("Idle.png");
	Texture Rabbit_O = LoadTexture("Idle_Sided.png");

	Texture AnimR = LoadTexture("Walking_R.png");
	Texture AnimL = LoadTexture("Walking_L.png");

	Texture JumpR = LoadTexture("Jump_R.png");
	Texture JumpL = LoadTexture("Jump_L.png");

	//-----------------------------------------------

	//------------------Gameplay Loop--------------------
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		//------------------Actualizaci�n de la bola--------------------
		// Mover la bola hacia la izquierda
		ballX -= ballSpeed;
		// Si sale completamente por la izquierda, reaparece por la derecha
		if (ballX + Spring_Width < 0) {
			ballX = screenWidth;
		}

		//------------------Movimiento del personaje (solo si est� activo)--------------------
		if (playerActive) {
			// Manejar el salto
			if (canMove && !isJumping)
			{
				// Verificar si se presiona SPACE para saltar
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

				// Movimiento horizontal DURANTE EL SALTO
				if (jumpDirection == 1)
				{
					x += (float)horizontalSpeed;
				}
				else if (jumpDirection == -1)
				{
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
		}

		//------------------Colisi�n entre personaje y bola--------------------
		if (playerActive) {
			// Rect�ngulo del personaje (mismo tama�o que el sprite)
			Rectangle playerRect = { x, y, Spring_Width, Spring_Height };
			// Rect�ngulo de la bola (mismo tama�o que el personaje)
			Rectangle ballRect = { ballX, ballY, Spring_Width, Spring_Height };

			// Verificar colisi�n
			if (CheckCollisionRecs(playerRect, ballRect)) {
				playerActive = false;  // Desactivar personaje: desaparece por completo
			}
		}

		//------------------Dibujado--------------------

		// Dibujar la bola (c�rculo rojo con el mismo centro que su rect�ngulo de colisi�n)
		Vector2 ballCenter = { ballX + Spring_Width / 2.0f, ballY + Spring_Height / 2.0f };
		float ballRadius = Spring_Width / 2.0f;
		DrawCircleV(ballCenter, ballRadius, RED);

		// Opcional: dibujar el rect�ngulo de colisi�n (descomentar para debug)
		// DrawRectangleLines(ballX, ballY, Spring_Width, Spring_Height, GREEN);

		// Dibujar el personaje solo si est� activo
		if (playerActive) {
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
		}
		else {
			// Si el personaje est� desactivado, mostrar mensaje de Game Over
			DrawText("GAME OVER", screenWidth / 2 - 60, screenHeight / 2, 30, RED);
		}

		// Dibujar el suelo
		DrawRectangle(0, 233, screenWidth, 10, WHITE);

		EndDrawing();
	}
	//---------------------------------------------------

	//-----------------Cleanup-----------------
	UnloadTexture(Rabbit);
	UnloadTexture(Rabbit_O);
	UnloadTexture(AnimL);
	UnloadTexture(AnimR);
	CloseWindow();
	return 0;
}