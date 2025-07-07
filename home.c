#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "home.h"
#include "main.h"

/*
Font roboto;
Font montserrat;
Font roboto_SemiBold;
*/

Color veryEasy;
Color easy;
Color medium;
Color hard;
Color veryHard;

Rectangle rectLvl1;
Rectangle rectLvl2;
Rectangle rectLvl3;
Rectangle rectLvl4;



//------------------------------------------------------------------------------------------------


void InitHome(void)
{
    /*
    roboto = LoadFont("assets/Roboto-Regular.ttf");
    montserrat = LoadFont("Montserrat-Regular.ttf");
    roboto_SemiBold = LoadFont("Roboto-Black.ttf");
    */

    veryEasy = (Color){0, 255, 0, 255};
    easy = (Color){0, 128, 255, 255};
    medium = (Color){0, 0, 139, 255};
    hard = (Color){255, 69, 0, 255};
    veryHard = (Color){139, 0, 20, 255};

    rectLvl1 = (Rectangle){screenWidth/2-100,250,200,60};
    rectLvl2 = (Rectangle){screenWidth/2-100,350,200,60};
    rectLvl3 = (Rectangle){screenWidth/2-100,450,200,60};
    rectLvl4 = (Rectangle){screenWidth/2-100,550,200,60};

}



//------------------------------------------------------------------------------------------------


void DrawHome(void)
{
    //======================FOND==========================
    DrawRectangleGradientV(0,0,screenWidth,screenHeight, (Color){0,0,150,255}, (Color){0,0,0,255});
    //DrawRectangleGradientV(0,0,screenWidth,screenHeight, (Color){0,255,0,255}, (Color){0,0,255,255});
    //DrawRectangleGradientV(0,0,screenWidth,screenHeight, (Color){0,0,255,255}, (Color){255,0,0,255});
    //DrawRectangleGradientV(0,0,screenWidth,screenHeight, (Color){0,255,0,255}, (Color){255,0,0,255});


    DrawText("CASSE", screenWidth/2-MeasureText("CASSE", 60)/2, 80, 60, GOLD);
    DrawText("BRIQUES", screenWidth/2-MeasureText("BRIQUES", 60)/2, 140, 60, GOLD);



    /*          //Pour faire une liste de niveau -> pas utile pour l'instant (seulement le dessin de fait, il faut encore gérer les collisions)
    //======================NIVEAUX=======================
    DrawRectangleRounded((Rectangle){70,240,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){70,290,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){70,340,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){70,390,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){70,440,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){70,490,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){70,540,110,30}, 2.5, 100, ORANGE);

    DrawRectangleRounded((Rectangle){250,240,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){250,290,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){250,340,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){250,390,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){250,440,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){250,490,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){250,540,110,30}, 2.5, 100, ORANGE);

    DrawRectangleRounded((Rectangle){430,240,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){430,290,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){430,340,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){430,390,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){430,440,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){430,490,110,30}, 2.5, 100, ORANGE);
    DrawRectangleRounded((Rectangle){430,540,110,30}, 2.5, 100, ORANGE);
    */


    DrawRectangleRounded(rectLvl1, 0.5, 100, ORANGE);
    DrawRectangleRounded(rectLvl2, 0.5, 100, ORANGE);
    DrawRectangleRounded(rectLvl3, 0.5, 100, ORANGE);
    DrawRectangleRounded(rectLvl4, 0.5, 100, ORANGE);

    DrawText("LEVEL 1", rectLvl1.x+rectLvl1.width/2-MeasureText("LEVEL 1", 40)/2, rectLvl1.y+(rectLvl1.height/2)-20, 40, BLACK);
    DrawText("LEVEL 2", rectLvl2.x+rectLvl2.width/2-MeasureText("LEVEL 2", 40)/2, rectLvl2.y+(rectLvl2.height/2)-20, 40, BLACK);
    DrawText("LEVEL 3", rectLvl3.x+rectLvl3.width/2-MeasureText("LEVEL 3", 40)/2, rectLvl3.y+(rectLvl3.height/2)-20, 40, BLACK);
    DrawText("LEVEL 4", rectLvl4.x+rectLvl4.width/2-MeasureText("LEVEL 4", 40)/2, rectLvl4.y+(rectLvl4.height/2)-20, 40, BLACK);

    if (CheckCollisionPointRec(GetMousePosition(),rectLvl1) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {currentScreen = SCREEN_LEVEL1;}
    if (CheckCollisionPointRec(GetMousePosition(),rectLvl2) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {currentScreen = SCREEN_LEVEL2;}
    if (CheckCollisionPointRec(GetMousePosition(),rectLvl3) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {currentScreen = SCREEN_LEVEL3;}
    if (CheckCollisionPointRec(GetMousePosition(),rectLvl4) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {currentScreen = SCREEN_LEVEL4;}


}


//------------------------------------------------------------------------------------------------


void UnloadHome(void)
{
    /*
    UnloadFont(roboto);
    UnloadFont(montserrat);
    UnloadFont(roboto_SemiBold);
    */

}

