#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "main.h"
#include "game.h"
#include "home.h"
#include "levels.h"


//------------------------------------------------------------------------------------
const int screenWidth = 600;
const int screenHeight = 700;
CurrentScreen currentScreen = SCREEN_HOME;

bool needToLoadLevel = true;



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "Casse Brique");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    InitHome();
    InitGame();
    InitLevels();



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        switch (currentScreen)
        {
        case SCREEN_HOME:
            //DRAW
            BeginDrawing();
                ClearBackground(BLACK);

                DrawHome();

                //fonction pour voir les coordonnees
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePosCoordonnee = GetMousePosition();
                    char pos[100];
                    sprintf(pos,"%.0f ; %.0f",mousePosCoordonnee.x,mousePosCoordonnee.y);
                    DrawText(pos,250,250,25,MAGENTA);
                }


            EndDrawing();

            break;
        case SCREEN_LEVEL1:
            //UPDATE
            UpdateGame();
            if (needToLoadLevel) {LoadLevel(brickEasy); needToLoadLevel = false;}

            //DRAW
            BeginDrawing();
                ClearBackground(BLACK);

                DrawLevel();
                DrawGame();


                //fonction pour voir les coordonnees
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePosCoordonnee = GetMousePosition();
                    char pos[100];
                    sprintf(pos,"%.0f ; %.0f",mousePosCoordonnee.x,mousePosCoordonnee.y);
                    DrawText(pos,250,250,25,MAGENTA);
                }

            EndDrawing();

            break;
        case SCREEN_LEVEL2:
            //UPDATE
            UpdateGame();
            if (needToLoadLevel) {LoadLevel(brickMedium); needToLoadLevel = false;}

            //DRAW
            BeginDrawing();
                ClearBackground(BLACK);

                DrawLevel();
                DrawGame();


                //fonction pour voir les coordonnees
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePosCoordonnee = GetMousePosition();
                    char pos[100];
                    sprintf(pos,"%.0f ; %.0f",mousePosCoordonnee.x,mousePosCoordonnee.y);
                    DrawText(pos,250,250,25,MAGENTA);
                }

            EndDrawing();

            break;
        case SCREEN_LEVEL3:
            //UPDATE
            UpdateGame();
            if (needToLoadLevel) {LoadLevel(brickHard); needToLoadLevel = false;}

            //DRAW
            BeginDrawing();
                ClearBackground(BLACK);

                DrawLevel();
                DrawGame();


                //fonction pour voir les coordonnees
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePosCoordonnee = GetMousePosition();
                    char pos[100];
                    sprintf(pos,"%.0f ; %.0f",mousePosCoordonnee.x,mousePosCoordonnee.y);
                    DrawText(pos,250,250,25,MAGENTA);
                }

            EndDrawing();

            break;
        case SCREEN_LEVEL4:
            //UPDATE
            UpdateGame();
            if (needToLoadLevel) {LoadLevel(brickDemon); needToLoadLevel = false;}

            //DRAW
            BeginDrawing();
                ClearBackground(BLACK);

                DrawLevel();
                DrawGame();


                //fonction pour voir les coordonnees
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePosCoordonnee = GetMousePosition();
                    char pos[100];
                    sprintf(pos,"%.0f ; %.0f",mousePosCoordonnee.x,mousePosCoordonnee.y);
                    DrawText(pos,250,250,25,MAGENTA);
                }

            EndDrawing();

            break;
        }
    }

    UnloadHome();
    UnloadGame();
    UnloadLevels();

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
