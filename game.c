#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "game.h"
#include "main.h"
#include "levels.h"


#define SPEED_BALL_X    800.0f
#define SPEED_BALL_Y    -500.0f
#define SPEED_PLATFORM  15
#define NBE_VIE_TOTALE  5



//------------------------------------------------------------------------------------------------

Font roboto;
Font montserrat;
Font roboto_SemiBold;

bool isPaused;

int platformWidth;
Rectangle platform;

int ballWidth;
Vector2 pos_ball;
Vector2 speed_ball;

int indexBrickCollisions;

bool waitingForRespawn;
float respawnStartTime;

int nbeVie;
char cptVie[32];
Vector2 pos_cptVie;

char timer[8];
int timerTotal;
int timerMinutes;
int timerSecondes;
float pausedTime = 0.0f;
float startTime = 0.0f;

Rectangle rectPause;
/*Rectangle rectHome;        // ---NE SERT PLUS, reste au cas du besoin d'un bouton supp     */

Rectangle rectMenuResume;
Rectangle rectMenuRestart;
Rectangle rectMenuHome;



//------------------------------------------------------------------------------------------------

void InitGame(void)
{

    roboto = LoadFont("assets/Roboto-Regular.ttf");
    montserrat = LoadFont("assets/Montserrat-Regular.ttf");
    roboto_SemiBold = LoadFont("assets/Roboto-SemiBold.ttf");

    isPaused = false;


    //#####JEU#####
    platformWidth = 100;
    platform = (Rectangle){screenWidth/2-(platformWidth/2),screenHeight-37,platformWidth,12};


    ballWidth = 5;
    pos_ball = (Vector2){platform.x + (platformWidth/2), platform.y - ballWidth - 2};
    speed_ball = (Vector2){SPEED_BALL_X, SPEED_BALL_Y};

    waitingForRespawn = false;
    respawnStartTime = 0;


    //#####BARRE INFO#####
    nbeVie = NBE_VIE_TOTALE;
    sprintf(cptVie, "Vies restantes : %d/%d", nbeVie, NBE_VIE_TOTALE);
    pos_cptVie = (Vector2){screenWidth-((MeasureTextEx(roboto,cptVie,20,1)).x)-8, 8};

    startTime = GetTime();
    pausedTime = 0;
    sprintf(timer,"00:00");

    rectPause = (Rectangle){8,5,26,26};
    /*rectHome = {42,5,26,26};        // ---NE SERT PLUS, reste au cas du besoin d'un bouton supp     */

    rectMenuResume = (Rectangle){screenWidth/2-95,200,190,50};
    rectMenuRestart = (Rectangle){screenWidth/2-95,300,190,50};
    rectMenuHome = (Rectangle){screenWidth/2-95,400,190,50};
}



//------------------------------------------------------------------------------------------------



void UpdateGame(void)
{
    if (isPaused == false) {
        timerTotal = (int)(GetTime()-pausedTime-startTime);
        timerMinutes = timerTotal/60;
        timerSecondes = timerTotal%60;
        sprintf(timer, "%02d:%02d", timerMinutes, timerSecondes);
    }
    if (isPaused == true) {pausedTime = GetTime()-startTime-pausedTime;}
}



void DrawGame(void)
{
    //===================BARRE INFO===========================================================================================
    //---Fond---
    DrawRectangle(0, 0, screenWidth, 36, GRAY);
    DrawRectangleGradientH(0,3,3,30,WHITE,GRAY);                //Left
    DrawRectangleGradientH(screenWidth-3,3,3,30,GRAY,WHITE);    //Right
    DrawRectangleGradientV(3,33,screenWidth-6,3,GRAY,WHITE);    //Bottom
    DrawRectangleGradientV(3,0,screenWidth-6,3,BLACK,GRAY);     //Top
    DrawRectangleGradientEx((Rectangle){screenWidth-3,33,3,3},GRAY,WHITE,WHITE,WHITE);  //Bottom Right
    DrawRectangleGradientEx((Rectangle){0,33,3,3},WHITE,WHITE,WHITE,GRAY);              //Bottom Left
    DrawRectangleGradientEx((Rectangle){screenWidth-3,0,3,3},BLACK,GRAY,WHITE,WHITE);   //Top Right
    DrawRectangleGradientEx((Rectangle){0,0,3,3},WHITE,WHITE,GRAY,BLACK);               //Top Left

    //---Timer & Vie---
    DrawText(timer, (screenWidth/2)-(MeasureText(timer,20)/2), 8, 20, GREEN);
    DrawTextEx(roboto, cptVie, pos_cptVie, 20, 1, MAROON);

    //---Home & Pause---
    DrawRectangleRec(rectPause,DARKGRAY);   //dessin carre
    DrawRectangleGradientH(8,8,3,20,WHITE,DARKGRAY);
    DrawRectangleGradientH(31,8,3,20,DARKGRAY,WHITE);
    DrawRectangleGradientV(11,5,20,3,WHITE,DARKGRAY);
    DrawRectangleGradientV(11,28,20,3,DARKGRAY,WHITE);
    DrawRectangleGradientEx((Rectangle){31,28,3,3},DARKGRAY,WHITE,WHITE,WHITE);
    DrawRectangleGradientEx((Rectangle){31,5,3,3},WHITE,DARKGRAY,WHITE,WHITE);
    DrawRectangleGradientEx((Rectangle){8,5,3,3},WHITE,WHITE,DARKGRAY,WHITE);
    DrawRectangleGradientEx((Rectangle){8,28,3,3},WHITE,WHITE,WHITE,DARKGRAY);

    DrawRectangle(16,13,4,10,BEIGE); //dessin pause
    DrawRectangle(22,13,4,10,BEIGE);

    if ((CheckCollisionPointRec(GetMousePosition(),rectPause) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) || IsKeyPressed(KEY_F1) == true) {
        isPaused = true;
    }


    /*      // ---NE SERT PLUS, reste au cas du besoin d'un bouton supp
    DrawRectangleRec(rectHome,DARKGRAY);
    DrawRectangleGradientH(42,8,3,20,WHITE,DARKGRAY);
    DrawRectangleGradientH(65,8,3,20,DARKGRAY,WHITE);
    DrawRectangleGradientV(45,5,20,3,WHITE,DARKGRAY);
    DrawRectangleGradientV(45,28,20,3,DARKGRAY,WHITE);
    DrawRectangleGradientEx((Rectangle){65,28,3,3},DARKGRAY,WHITE,WHITE,WHITE);
    DrawRectangleGradientEx((Rectangle){65,5,3,3},WHITE,DARKGRAY,WHITE,WHITE);
    DrawRectangleGradientEx((Rectangle){42,5,3,3},WHITE,WHITE,DARKGRAY,WHITE);
    DrawRectangleGradientEx((Rectangle){42,28,3,3},WHITE,WHITE,WHITE,DARKGRAY);

    if (CheckCollisionPointRec((Vector2){GetMousePosition()},rectHome) == true) {
        // TODO: a implementer
    }
    */






    //===================PLATFORM===========================================================================================
    DrawRectangleRec(platform,ORANGE);
    if (isPaused == false) {
        if (IsKeyDown(KEY_LEFT) == true && platform.x >= 0) {platform.x -= SPEED_PLATFORM;}
        if (IsKeyDown(KEY_RIGHT) == true && (platform.x+platformWidth) <= screenWidth) {platform.x += SPEED_PLATFORM;}
    }



    //===================BALL===============================================================================================
    DrawCircle(pos_ball.x,pos_ball.y,ballWidth,WHITE);

    //-------------------collisions avec les murs-------------------
    if (waitingForRespawn == false && isPaused == false) {
        if (pos_ball.x <= (0+ballWidth) || pos_ball.x >= (screenWidth-ballWidth)) {speed_ball.x = -speed_ball.x;}
        if (pos_ball.y <= (41+ballWidth)) {speed_ball.y = -speed_ball.y;}
        pos_ball.x += speed_ball.x * GetFrameTime();
        pos_ball.y += speed_ball.y * GetFrameTime();
    }

    if (pos_ball.y >= (screenHeight-ballWidth)) {
        nbeVie--;
        sprintf(cptVie, "Vies restantes : %d/%d", nbeVie, NBE_VIE_TOTALE);

        waitingForRespawn = true;
        respawnStartTime = GetTime();
        pos_ball.x = platform.x + (platformWidth/2);
        pos_ball.y = platform.y - ballWidth - 2;
        speed_ball.y = SPEED_BALL_Y;
    }

    if (waitingForRespawn == true) {pos_ball.x = platform.x + (platformWidth/2);}

    if (waitingForRespawn == true && (GetTime() - respawnStartTime) >= 0.5f) {
        waitingForRespawn = false;
    }

    //-------------------collisions avec la platform-------------------
    if (CheckCollisionCircleRec(pos_ball, ballWidth, platform) == true) {
        speed_ball.x = -speed_ball.x;
        speed_ball.y = -speed_ball.y;
        pos_ball.x += speed_ball.x * GetFrameTime();
        pos_ball.y += speed_ball.y * GetFrameTime();
    }


    //-------------------collisions avec les bricks-------------------
    //---Lvl 1---
    indexBrickCollisions = 0;
    for (indexBrickCollisions = 0; indexBrickCollisions < nbeBricks; indexBrickCollisions++) {
        if (brickLevel1[indexBrickCollisions].brickType.exist == true) {
            if (CheckCollisionCircleRec(pos_ball, ballWidth, brickLevel1[indexBrickCollisions].rectBrick) == true) {
                //----Effects Ball
                speed_ball.x = -speed_ball.x;
                speed_ball.y = -speed_ball.y;
                pos_ball.x += speed_ball.x * GetFrameTime();
                pos_ball.y += speed_ball.y * GetFrameTime();

                //----Effects Bricks
                brickLevel1[indexBrickCollisions].brickType.durability--;
                if (brickLevel1[indexBrickCollisions].brickType.durability == 0) {
                    brickLevel1[indexBrickCollisions].brickType.exist = false;
                    brickLevel1[indexBrickCollisions].rectBrick = (Rectangle){0,0,0,0};
                }

            }
        }
    }

    //---Lvl 2---
    indexBrickCollisions = 0;
    for (indexBrickCollisions = 0; indexBrickCollisions < nbeBricks; indexBrickCollisions++) {
        if (brickLevel2[indexBrickCollisions].brickType.exist == true) {
            if (CheckCollisionCircleRec(pos_ball, ballWidth, brickLevel2[indexBrickCollisions].rectBrick) == true) {
                //----Effects Ball
                speed_ball.x = -speed_ball.x;
                speed_ball.y = -speed_ball.y;
                pos_ball.x += speed_ball.x * GetFrameTime();
                pos_ball.y += speed_ball.y * GetFrameTime();

                //----Effects Bricks
                brickLevel2[indexBrickCollisions].brickType.durability--;
                if (brickLevel2[indexBrickCollisions].brickType.durability == 0) {brickLevel2[indexBrickCollisions].brickType.exist = false;}

            }
        }
    }

    //---Lvl 3---
    indexBrickCollisions = 0;
    for (indexBrickCollisions = 0; indexBrickCollisions < nbeBricks; indexBrickCollisions++) {
        if (brickLevel3[indexBrickCollisions].brickType.exist == true) {
            if (CheckCollisionCircleRec(pos_ball, ballWidth, brickLevel3[indexBrickCollisions].rectBrick) == true) {
                //----Effects Ball
                speed_ball.x = -speed_ball.x;
                speed_ball.y = -speed_ball.y;
                pos_ball.x += speed_ball.x * GetFrameTime();
                pos_ball.y += speed_ball.y * GetFrameTime();

                //----Effects Bricks
                brickLevel3[indexBrickCollisions].brickType.durability--;
                if (brickLevel3[indexBrickCollisions].brickType.durability == 0) {brickLevel3[indexBrickCollisions].brickType.exist = false;}

            }
        }
    }

    //---Lvl 4---
    indexBrickCollisions = 0;
    for (indexBrickCollisions = 0; indexBrickCollisions < nbeBricks; indexBrickCollisions++) {
        if (brickLevel4[indexBrickCollisions].brickType.exist == true) {
            if (CheckCollisionCircleRec(pos_ball, ballWidth, brickLevel4[indexBrickCollisions].rectBrick) == true) {
                //----Effects Ball
                speed_ball.x = -speed_ball.x;
                speed_ball.y = -speed_ball.y;
                pos_ball.x += speed_ball.x * GetFrameTime();
                pos_ball.y += speed_ball.y * GetFrameTime();

                //----Effects Bricks
                brickLevel4[indexBrickCollisions].brickType.durability--;
                if (brickLevel4[indexBrickCollisions].brickType.durability == 0) {
                        brickLevel4[indexBrickCollisions].brickType.exist = false;

                }

            }
        }
    }






    //===================SCREEN PAUSE=======================================================================================
    if (isPaused == true) {
        DrawRectangle(0,0,screenWidth,screenHeight,(Color){0,0,0,150});
        //DrawTextEx(roboto,"PAUSE",(Vector2){(screenWidth/2-((MeasureTextEx(roboto,"PAUSE",50,1)).x/2)),110},50,1,WHITE);
        DrawText("PAUSE",(screenWidth/2-(MeasureText("PAUSE",50)/2)),110,50,WHITE);

        DrawRectangleRec(rectMenuResume,DARKGRAY);
        DrawText("RESUME",screenWidth/2-40,215,25,BEIGE);
        DrawPoly((Vector2){rectMenuResume.x+25, rectMenuResume.y+26}, 3, 15, 0, RED);
        DrawRectangleGradientH(rectMenuResume.x, rectMenuResume.y+3, 3, rectMenuResume.height-6, WHITE, DARKGRAY);
        DrawRectangleGradientH(rectMenuResume.x+rectMenuResume.width-3, rectMenuResume.y+3, 3, rectMenuResume.height-6, DARKGRAY, WHITE);
        DrawRectangleGradientV(rectMenuResume.x+3, rectMenuResume.y, rectMenuResume.width-6, 3, WHITE, DARKGRAY);
        DrawRectangleGradientV(rectMenuResume.x+3, rectMenuResume.y+rectMenuResume.height-3, rectMenuResume.width-6, 3, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectMenuResume.x, rectMenuResume.y, 3, 3}, WHITE, WHITE, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectMenuResume.x, rectMenuResume.y+rectMenuResume.height-3, 3, 3}, WHITE, WHITE, WHITE, DARKGRAY);
        DrawRectangleGradientEx((Rectangle){rectMenuResume.x+rectMenuResume.width-3, rectMenuResume.y, 3, 3}, WHITE, DARKGRAY, WHITE, WHITE);
        DrawRectangleGradientEx((Rectangle){rectMenuResume.x+rectMenuResume.width-3, rectMenuResume.y+rectMenuResume.height-3, 3, 3}, DARKGRAY, WHITE, WHITE, WHITE);

        DrawRectangleRec(rectMenuRestart,DARKGRAY);
        DrawText("RESTART",screenWidth/2-40,315,25,BEIGE);
        DrawCircleSector((Vector2){rectMenuRestart.x+25, rectMenuRestart.y+26}, 15, 210, 500, 20, RED);
        DrawCircle(rectMenuRestart.x+25, rectMenuRestart.y+26, 10, DARKGRAY);
        DrawPoly((Vector2){220, 320}, 3, 8, 8, RED);
        DrawRectangleGradientH(rectMenuRestart.x, rectMenuRestart.y+3, 3, rectMenuRestart.height-6, WHITE, DARKGRAY);
        DrawRectangleGradientH(rectMenuRestart.x+rectMenuRestart.width-3, rectMenuRestart.y+3, 3, rectMenuRestart.height-6, DARKGRAY, WHITE);
        DrawRectangleGradientV(rectMenuRestart.x+3, rectMenuRestart.y, rectMenuRestart.width-6, 3, WHITE, DARKGRAY);
        DrawRectangleGradientV(rectMenuRestart.x+3, rectMenuRestart.y+rectMenuRestart.height-3, rectMenuRestart.width-6, 3, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectMenuRestart.x, rectMenuRestart.y, 3, 3}, WHITE, WHITE, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectMenuRestart.x, rectMenuRestart.y+rectMenuRestart.height-3, 3, 3}, WHITE, WHITE, WHITE, DARKGRAY);
        DrawRectangleGradientEx((Rectangle){rectMenuRestart.x+rectMenuRestart.width-3, rectMenuRestart.y, 3, 3}, WHITE, DARKGRAY, WHITE, WHITE);
        DrawRectangleGradientEx((Rectangle){rectMenuRestart.x+rectMenuRestart.width-3, rectMenuRestart.y+rectMenuRestart.height-3, 3, 3}, DARKGRAY, WHITE, WHITE, WHITE);

        DrawRectangleRec(rectMenuHome,DARKGRAY);
        DrawText("HOME",screenWidth/2-40,415,25,BEIGE);
        DrawRectangle(rectMenuHome.x+15, rectMenuHome.y+20, 20, 20, RED);
        DrawRectangle(rectMenuHome.x+22, rectMenuHome.y+30, 7, 10, DARKGRAY);
        DrawPoly((Vector2){230, 417}, 4, 8, 270, RED);
        DrawPoly((Vector2){223, 420}, 3, 7, 285, RED);
        DrawPoly((Vector2){236, 420}, 3, 7, 255, RED);
        DrawRectangleGradientH(rectMenuHome.x, rectMenuHome.y+3, 3, rectMenuHome.height-6, WHITE, DARKGRAY);
        DrawRectangleGradientH(rectMenuHome.x+rectMenuHome.width-3, rectMenuHome.y+3, 3, rectMenuHome.height-6, DARKGRAY, WHITE);
        DrawRectangleGradientV(rectMenuHome.x+3, rectMenuHome.y, rectMenuHome.width-6, 3, WHITE, DARKGRAY);
        DrawRectangleGradientV(rectMenuHome.x+3, rectMenuHome.y+rectMenuHome.height-3, rectMenuHome.width-6, 3, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectMenuHome.x, rectMenuHome.y, 3, 3}, WHITE, WHITE, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectMenuHome.x, rectMenuHome.y+rectMenuHome.height-3, 3, 3}, WHITE, WHITE, WHITE, DARKGRAY);
        DrawRectangleGradientEx((Rectangle){rectMenuHome.x+rectMenuHome.width-3, rectMenuHome.y, 3, 3}, WHITE, DARKGRAY, WHITE, WHITE);
        DrawRectangleGradientEx((Rectangle){rectMenuHome.x+rectMenuHome.width-3, rectMenuHome.y+rectMenuHome.height-3, 3, 3}, DARKGRAY, WHITE, WHITE, WHITE);



        if (CheckCollisionPointRec(GetMousePosition(),rectMenuResume) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {isPaused = false;}
        if (CheckCollisionPointRec(GetMousePosition(),rectMenuRestart) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {InitGame();}
        if (CheckCollisionPointRec(GetMousePosition(),rectMenuHome) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
            InitGame();
            InitLevels();
            currentScreen = SCREEN_HOME;
        }
    }



}


void UnloadGame(void)
{
    UnloadFont(roboto);
    UnloadFont(montserrat);
    UnloadFont(roboto_SemiBold);

}


