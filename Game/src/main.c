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
#define Spring_Height 32
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
struct Animation
{
	int Frame /*= 0*/;
	int Counter /*= 0*/;
	int Speed /*= 5*/;
} Spring;
void AnimationSettings()
{
	Spring.Counter++;
	if (Spring.Counter >= (85 / Spring.Speed))
	{
		Spring.Counter = 0;
		Spring.Frame++;

		if (Spring.Frame > 1) Spring.Frame = 0;
	}
}


int main()
{
	//------------------Miscellaneous--------------------
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	int x = 0;
	int vX = 1;
	int y = 10;
	int vY = 1;
	Spring.Speed = 5;

	bool Direction = 0;
	x = 200;
	y = 175;

	int G = 2;

	int Floor = 200;
	bool Momentum = 1;

	//---------------------------------------------------

	//------------------Window--------------------
	int screenWidth = 400; //X
	int screenHeight = 350; //Y

	InitWindow(screenWidth, screenHeight, "_C4STL3V4N14_");
	//---------------------------------------------

	//------------------Textures--------------------
	SearchAndSetResourceDir("resources"); // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it

	Texture Rabbit = LoadTexture("wabbit_alpha.png");
	Texture Rabbit_O = LoadTexture("OtherSide.png");

	Texture AnimR = LoadTexture("Anim_R.png");
	Texture AnimL = LoadTexture("Anim_L.png");

	//-----------------------------------------------

	//------------------Gameplay Loop--------------------
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		//------------------Camera--------------------

		//--------------------------------------------
		/*BeginDrawing();

		ClearBackground(BLACK);


		DrawText("You should KILL YOURSELF NOW!", 30, 100, 20, PURPLE);
		if (IsKeyUp(KEY_D) && IsKeyUp(KEY_A))
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
		if (IsKeyDown(KEY_D) && IsKeyDown(KEY_A))
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
		DrawRectangle(0, 233, screenWidth, 10, WHITE);*/

		AnimationSettings();

		//------------------Player Movement--------------------
		y = y + G; //Gravity

		if (y > screenHeight - 100) y = screenHeight - 100;
		if (y < 0) y = 0;
		if (x > screenWidth - 15) x = screenWidth - 15;
		if (x < -5) x = -5;

		if (y > Floor)
		{
			y = Floor;
			Momentum = true;
		}


		if (Momentum == true)
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				int Stanley = y;
				int Jump = 100;
				y = y - Jump;
				Momentum = false;
			}
			if (IsKeyUp(KEY_A))
			{
				if (IsKeyDown(KEY_D))
				{
					x = x + vX;
					Direction = 0;

					Rectangle source = (Rectangle){ Spring.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
					Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
					DrawTexturePro(AnimR, source, dest, (Vector2) { dest.width / x, dest.height / y }, 0, WHITE);

				}
			}
			if (IsKeyUp(KEY_D))
			{
				if (IsKeyDown(KEY_A))
				{
					x = x - vX;
					Direction = 1;
					Rectangle source = (Rectangle){ Spring.Frame * Spring_Width, 0, Spring_Width, Spring_Height };
					Rectangle dest = (Rectangle){ x, y, Spring_Width, Spring_Height };
					DrawTexturePro(AnimL, source, dest, (Vector2) { dest.width / x, dest.height / y }, 0, WHITE);
				}
			}
		}
		//-------------------------------------------------



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
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define TILE_SIZE 32
#define MAP_WIDTH 25
#define MAP_HEIGHT 10

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

int fondo(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Castlevania Demo");

	// 📸 Cargar imagen
	Texture2D fondo = LoadTexture("resources/castlevania.png");

	// comprobar si cargó
	if (fondo.id == 0) {
		TraceLog(LOG_ERROR, "No se pudo cargar la imagen");
	}

	SetTextureFilter(fondo, TEXTURE_FILTER_POINT);

	Camera2D camera = { 0 };
	camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 2.0f;

	Vector2 player = { 100, 100 };

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// movimiento
		if (IsKeyDown(KEY_RIGHT)) player.x += 2;
		if (IsKeyDown(KEY_LEFT))  player.x -= 2;
		if (IsKeyDown(KEY_DOWN))  player.y += 2;
		if (IsKeyDown(KEY_UP))    player.y -= 2;

		camera.target = player;

		BeginDrawing();
		ClearBackground(BLACK);

		BeginMode2D(camera);

		// 🖼️ fondo (nivel)
		DrawTextureEx(fondo, (Vector2) { 0.0f, 0.0f }, 0.0f, 2.0f, WHITE);

		// mapa debug
		for (int y = 0; y < MAP_HEIGHT; y++) {
			for (int x = 0; x < MAP_WIDTH; x++) {
				if (map[y][x] == 1) {
					DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
				}
			}
		}

		// jugador
		DrawRectangle((int)player.x, (int)player.y, 20, 20, RED);

		EndMode2D();

		// mensaje si falla la imagen
		if (fondo.id == 0) {
			DrawText("ERROR: No se cargo la imagen", 10, 10, 20, RED);
		}

		EndDrawing();
	}

	UnloadTexture(fondo);
	CloseWindow();

	return 0;
}
