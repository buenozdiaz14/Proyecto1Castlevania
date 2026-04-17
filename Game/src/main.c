#include "raylib.h"

typedef enum GameScreen { MENU = 0, JUGAR, OPCIONES } GameScreen;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Mi Juego - Menu Principal");


    InitAudioDevice();


    Music musicaFondo = LoadMusicStream("001.wav");
    PlayMusicStream(musicaFondo);

    GameScreen currentScreen = MENU;
    Rectangle btnJugar = { screenWidth / 2.0f - 100, 200, 200, 50 };
    Rectangle btnOpcion = { screenWidth / 2.0f - 100, 300, 200, 50 };
    Rectangle btnSalir = { screenWidth / 2.0f - 100, 400, 200, 50 };

    float volumenMusica = 0.5f;
    bool arrastrandoSlider = false;
    Rectangle sliderBarra = { screenWidth / 2.0f - 150, 300, 300, 30 };


    SetMusicVolume(musicaFondo, volumenMusica);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        UpdateMusicStream(musicaFondo);

        Vector2 mousePoint = GetMousePosition();

        if (currentScreen == MENU) {
            if (CheckCollisionPointRec(mousePoint, btnJugar) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) currentScreen = JUGAR;
            if (CheckCollisionPointRec(mousePoint, btnOpcion) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) currentScreen = OPCIONES;
            if (CheckCollisionPointRec(mousePoint, btnSalir) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) break;
        }
        else if (currentScreen == OPCIONES) {
            if (IsKeyPressed(KEY_ESCAPE)) currentScreen = MENU;

            Rectangle sliderBoton = { sliderBarra.x + (volumenMusica * sliderBarra.width) - 15, sliderBarra.y - 10, 30, 50 };

            if ((CheckCollisionPointRec(mousePoint, sliderBarra) || CheckCollisionPointRec(mousePoint, sliderBoton)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                arrastrandoSlider = true;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                arrastrandoSlider = false;
            }

            if (arrastrandoSlider) {
                volumenMusica = (mousePoint.x - sliderBarra.x) / sliderBarra.width;

                if (volumenMusica < 0.0f) volumenMusica = 0.0f;
                if (volumenMusica > 1.0f) volumenMusica = 1.0f;


                SetMusicVolume(musicaFondo, volumenMusica);
            }
        }
        else {
            if (IsKeyPressed(KEY_ESCAPE)) currentScreen = MENU;
        }


        BeginDrawing();

        if (currentScreen == MENU) {
            ClearBackground(BLACK);
            const char* textoTitulo = "MENU PRINCIPAL";
            DrawText(textoTitulo, (screenWidth - MeasureText(textoTitulo, 60)) / 2, 80, 60, GOLD);

            Color colJugar = CheckCollisionPointRec(mousePoint, btnJugar) ? DARKGRAY : LIGHTGRAY;
            DrawRectangleRec(btnJugar, colJugar);
            DrawText("JUGAR", btnJugar.x + 60, btnJugar.y + 15, 20, BLACK);

            Color colOpcion = CheckCollisionPointRec(mousePoint, btnOpcion) ? DARKGRAY : LIGHTGRAY;
            DrawRectangleRec(btnOpcion, colOpcion);
            DrawText("OPCIONES", btnOpcion.x + 50, btnOpcion.y + 15, 20, BLACK);

            Color colSalir = CheckCollisionPointRec(mousePoint, btnSalir) ? DARKGRAY : LIGHTGRAY;
            DrawRectangleRec(btnSalir, colSalir);
            DrawText("SALIR", btnSalir.x + 70, btnSalir.y + 15, 20, BLACK);

        }
        else if (currentScreen == JUGAR) {
            ClearBackground(RAYWHITE);
            DrawText("ESTAS JUGANDO!", 200, 250, 30, MAROON);
        }
        else if (currentScreen == OPCIONES) {
            ClearBackground(RAYWHITE);
            DrawText("PANTALLA DE OPCIONES", screenWidth / 2 - 180, 100, 30, DARKBLUE);
            DrawText("VOLUMEN DE MUSICA", sliderBarra.x, sliderBarra.y - 30, 20, BLACK);

            DrawRectangleRec(sliderBarra, DARKGRAY);
            Rectangle barraLlena = { sliderBarra.x, sliderBarra.y, sliderBarra.width * volumenMusica, sliderBarra.height };
            DrawRectangleRec(barraLlena, LIME);
            DrawRectangleLinesEx(sliderBarra, 2, BLACK);

            Rectangle sliderBoton = { sliderBarra.x + (volumenMusica * sliderBarra.width) - 15, sliderBarra.y - 10, 30, 50 };
            DrawRectangleRec(sliderBoton, DARKGREEN);
            DrawRectangleLinesEx(sliderBoton, 2, BLACK);

            int porcentaje = (int)(volumenMusica * 100);
            DrawText(TextFormat("%i%%", porcentaje), sliderBarra.x + sliderBarra.width + 20, sliderBarra.y + 5, 20, BLACK);
        }

        EndDrawing();
    }


    UnloadMusicStream(musicaFondo);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}

