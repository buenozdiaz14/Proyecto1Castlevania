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

// Structure for animation frames
struct Animation
{
	int Frame /*= 0*/;
	int Counter /*= 0*/;
	int Speed /*= 5*/;
} Spring;

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

	float G = 0.1f;  // Gravedad reducida para caída más lenta y salto más alto
	int Floor = 200;
	bool canMove = true;  // Puede moverse? (true = puede moverse, false = en el aire/saltando)

	// Variables de salto
	bool isJumping = false;      // Indica si el jugador está en el aire
	int jumpDirection = 0;       // 0 = arriba, -1 = izquierda, 1 = derecha
	float verticalSpeed = 0;     // Velocidad vertical actual
	float initialJumpSpeed = -6.0f;  // Velocidad inicial para salto alto

	// Variables para el movimiento horizontal durante el salto
	int startX = 0;              // Posición X cuando comenzó el salto
	float horizontalSpeed = 0;   // Velocidad horizontal durante el salto (igual que vX)

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

				// Determinar dirección y velocidad horizontal del salto
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

		// Física del salto
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

			// Colisión con el suelo
			if (y >= Floor)
			{
				y = Floor;
			}
		}

		// Límites de la pantalla
		if (x > screenWidth - 15) x = screenWidth - 15;
		if (x < -5) x = -5;
		if (y > screenHeight - 100) y = screenHeight - 100;

		//------------------Dibujado de Sprites--------------------

		// Dibujar animación cuando está en movimiento en el suelo
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
		// Dibujar sprite estático cuando está quieto en el suelo
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