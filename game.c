#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raylib.h"
#include "game.h"
#include "main.h"
#include "levels.h"


#define SPEED_BALL_X    400.0f
#define SPEED_BALL_Y    -375.0f
#define SPEED_PLATFORM  15
#define PLATFORM_WIDTH_INIT 150
#define NBE_VIE_TOTALE  5



//------------------------------------------------------------------------------------------------

Font roboto;
Font montserrat;
Font roboto_SemiBold;

bool isPaused, isFinish;

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

char resultL1[64], resultL2[64], resultL3[64];

Rectangle rectPause;
/*Rectangle rectHome;        // ---NE SERT PLUS, reste au cas du besoin d'un bouton supp     */

Rectangle rectMenuResume;
Rectangle rectMenuRestart;
Rectangle rectMenuHome;

Rectangle rectFinishRestart;
Rectangle rectFinishHome;



//------------------------------------------------------------------------------------------------

void InitGame(void)
{

    roboto = LoadFont("assets/Roboto-Regular.ttf");
    montserrat = LoadFont("assets/Montserrat-Regular.ttf");
    roboto_SemiBold = LoadFont("assets/Roboto-SemiBold.ttf");

    isPaused = false;
    isFinish = false;


    //#####JEU#####
    platformWidth = PLATFORM_WIDTH_INIT;
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

    rectFinishRestart = (Rectangle){screenWidth/2-95,screenHeight/2+50,190,50};
    rectFinishHome = (Rectangle){screenWidth/2-95,screenHeight/2+150,190,50};
}



//------------------------------------------------------------------------------------------------



void UpdateGame(void)
{
    if (!isPaused && !isFinish) {
        timerTotal = (int)(GetTime()-pausedTime-startTime);
        timerMinutes = timerTotal/60;
        timerSecondes = timerTotal%60;
        sprintf(timer, "%02d:%02d", timerMinutes, timerSecondes);
    }
    if (isPaused) {pausedTime = GetTime()-startTime-pausedTime;}
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

    if (!isFinish) {
        if ((CheckCollisionPointRec(GetMousePosition(),rectPause) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) || IsKeyPressed(KEY_F1) == true) {
            isPaused = true;
        }
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
    if (!isPaused && !isFinish) {
        if (IsKeyDown(KEY_LEFT) == true && platform.x >= 0) {platform.x -= SPEED_PLATFORM;}
        if (IsKeyDown(KEY_RIGHT) == true && (platform.x+platformWidth) <= screenWidth) {platform.x += SPEED_PLATFORM;}
    }



    //===================BALL===============================================================================================
    DrawCircle(pos_ball.x,pos_ball.y,ballWidth,WHITE);

    //-------------------collisions avec les murs-------------------
    if (!waitingForRespawn && !isPaused && !isFinish) {
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

    if (waitingForRespawn) {pos_ball.x = platform.x + (platformWidth/2);}

    if (waitingForRespawn && (GetTime() - respawnStartTime) >= 0.5f) {
        waitingForRespawn = false;
    }

    //-------------------collisions avec la platform-------------------
    if (CheckCollisionCircleRec(pos_ball, ballWidth, platform)) {
        speed_ball.y = -speed_ball.y;
        pos_ball.x += speed_ball.x * GetFrameTime();
        pos_ball.y += (speed_ball.y * GetFrameTime()) - platform.height;
    }


    //-------------------collisions avec les bricks-------------------
    indexBrickCollisions = 0;
    for (indexBrickCollisions = 0; indexBrickCollisions < nbeBricks; indexBrickCollisions++) {
        if (currentBrickLevel[indexBrickCollisions].brickType.exist) {
            if (CheckCollisionCircleRec(pos_ball, ballWidth, currentBrickLevel[indexBrickCollisions].rectBrick)) {
                //----Effects Ball
                float verticalCollisionBrick = fabsf(pos_ball.x - (currentBrickLevel[indexBrickCollisions].centerBrick.x)) - (((currentBrickLevel[indexBrickCollisions].rectBrick.width)/2.0f)+ballWidth); // gauche et droit
                float horizontalCollisionBrick = fabsf(pos_ball.y - (currentBrickLevel[indexBrickCollisions].centerBrick.y)) - (((currentBrickLevel[indexBrickCollisions].rectBrick.height)/2.0f)+ballWidth); //haut et bas

                if (fabsf(horizontalCollisionBrick) < fabsf(verticalCollisionBrick)) {
                    speed_ball.y = -speed_ball.y;
                } else {
                    speed_ball.x = -speed_ball.x;
                }

                pos_ball.x += speed_ball.x * GetFrameTime();
                pos_ball.y += speed_ball.y * GetFrameTime();

                //----Effects Bricks
                currentBrickLevel[indexBrickCollisions].brickType.durability--;
                if (currentBrickLevel[indexBrickCollisions].brickType.durability == 0) {currentBrickLevel[indexBrickCollisions].brickType.exist = false; nbeBrickRemaining--;}

            }
        }
    }






    //======================================================================================================================
    //-------------------SCREEN PAUSE---------------------------------------------------------------------------------------
    //======================================================================================================================
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
        if (CheckCollisionPointRec(GetMousePosition(),rectMenuRestart) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
            InitGame();
            InitLevels();
            needToLoadLevel = true;
        }
        if (CheckCollisionPointRec(GetMousePosition(),rectMenuHome) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
            InitGame();
            InitLevels();
            needToLoadLevel = true;
            currentScreen = SCREEN_HOME;
        }
    }





    //======================================================================================================================
    //-------------------SCREEN GAME FINISH---------------------------------------------------------------------------------------
    //======================================================================================================================
    //--------------WIN-----------------
    if (nbeBrickRemaining == 0 && nbeVie > 0 && nbeVie <= NBE_VIE_TOTALE) {
        isFinish = true;
        DrawRectangle(0,0,screenWidth,screenHeight,(Color){0,255,0,130});
        //DrawTextEx(roboto,"VICTORY !",(Vector2){(screenWidth/2-((MeasureTextEx(roboto,"VICTORY !",70,1)).x/2)),(screenHeight/2-100)},70,1,WHITE);
        //DrawTextEx(roboto_SemiBold,"VICTORY !",(Vector2){(screenWidth/2-((MeasureTextEx(roboto_SemiBold,"VICTORY !",70,1)).x/2)),(screenHeight/2-100)},70,1,WHITE);
        //DrawTextEx(montserrat,"VICTORY !",(Vector2){(screenWidth/2-((MeasureTextEx(montserrat,"VICTORY !",70,1)).x/2)),(screenHeight/2-100)},70,1,WHITE);
        DrawText("VICTORY !",(screenWidth/2-(MeasureText("VICTORY !",50)/2)),(screenHeight/2-150),50,WHITE);
        //sprintf(resultL1 ,"Congrtulation !\nYou won in %s\nwith %d/%d lives remaining", timer, nbeVie, NBE_VIE_TOTALE);
        sprintf(resultL1 ,"Congratulation !");
        sprintf(resultL2 ,"You won in %s",timer);
        sprintf(resultL3 ,"With %d/%d lives remaining",nbeVie, NBE_VIE_TOTALE);
        //DrawText(resultL1, (screenWidth/2-(MeasureText(resultL1,20)/2)), (screenHeight/2-40), 20, BLACK);
        DrawText(resultL1, (screenWidth/2-(MeasureText(resultL1,20)/2)), (screenHeight/2-80), 20, BLACK);
        DrawText(resultL2, (screenWidth/2-(MeasureText(resultL2,20)/2)), (screenHeight/2-55), 20, BLACK);
        DrawText(resultL3, (screenWidth/2-(MeasureText(resultL3,20)/2)), (screenHeight/2-30), 20, BLACK);



        DrawRectangleRec(rectFinishRestart,DARKGRAY);
        DrawText("RESTART",screenWidth/2-40,(screenHeight/2+50)+15,25,BEIGE);
        DrawCircleSector((Vector2){rectFinishRestart.x+25, rectFinishRestart.y+26}, 15, 210, 500, 20, RED);
        DrawCircle(rectFinishRestart.x+25, rectFinishRestart.y+26, 10, DARKGRAY);
        DrawPoly((Vector2){220, (screenHeight/2+50)+20}, 3, 8, 8, RED);
        DrawRectangleGradientH(rectFinishRestart.x, rectFinishRestart.y+3, 3, rectFinishRestart.height-6, WHITE, DARKGRAY);
        DrawRectangleGradientH(rectFinishRestart.x+rectFinishRestart.width-3, rectFinishRestart.y+3, 3, rectFinishRestart.height-6, DARKGRAY, WHITE);
        DrawRectangleGradientV(rectFinishRestart.x+3, rectFinishRestart.y, rectFinishRestart.width-6, 3, WHITE, DARKGRAY);
        DrawRectangleGradientV(rectFinishRestart.x+3, rectFinishRestart.y+rectFinishRestart.height-3, rectFinishRestart.width-6, 3, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishRestart.x, rectFinishRestart.y, 3, 3}, WHITE, WHITE, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishRestart.x, rectFinishRestart.y+rectFinishRestart.height-3, 3, 3}, WHITE, WHITE, WHITE, DARKGRAY);
        DrawRectangleGradientEx((Rectangle){rectFinishRestart.x+rectFinishRestart.width-3, rectFinishRestart.y, 3, 3}, WHITE, DARKGRAY, WHITE, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishRestart.x+rectFinishRestart.width-3, rectFinishRestart.y+rectFinishRestart.height-3, 3, 3}, DARKGRAY, WHITE, WHITE, WHITE);

        DrawRectangleRec(rectFinishHome,DARKGRAY);
        DrawText("HOME",screenWidth/2-40,(screenHeight/2+150)+15,25,BEIGE);
        DrawRectangle(rectFinishHome.x+15, rectFinishHome.y+20, 20, 20, RED);
        DrawRectangle(rectFinishHome.x+22, rectFinishHome.y+30, 7, 10, DARKGRAY);
        DrawPoly((Vector2){230, (screenHeight/2+150)+17}, 4, 8, 270, RED);
        DrawPoly((Vector2){223, (screenHeight/2+150)+20}, 3, 7, 285, RED);
        DrawPoly((Vector2){236, (screenHeight/2+150)+20}, 3, 7, 255, RED);
        DrawRectangleGradientH(rectFinishHome.x, rectFinishHome.y+3, 3, rectFinishHome.height-6, WHITE, DARKGRAY);
        DrawRectangleGradientH(rectFinishHome.x+rectFinishHome.width-3, rectFinishHome.y+3, 3, rectFinishHome.height-6, DARKGRAY, WHITE);
        DrawRectangleGradientV(rectFinishHome.x+3, rectFinishHome.y, rectFinishHome.width-6, 3, WHITE, DARKGRAY);
        DrawRectangleGradientV(rectFinishHome.x+3, rectFinishHome.y+rectFinishHome.height-3, rectFinishHome.width-6, 3, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishHome.x, rectFinishHome.y, 3, 3}, WHITE, WHITE, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishHome.x, rectFinishHome.y+rectFinishHome.height-3, 3, 3}, WHITE, WHITE, WHITE, DARKGRAY);
        DrawRectangleGradientEx((Rectangle){rectFinishHome.x+rectFinishHome.width-3, rectFinishHome.y, 3, 3}, WHITE, DARKGRAY, WHITE, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishHome.x+rectFinishHome.width-3, rectFinishHome.y+rectFinishHome.height-3, 3, 3}, DARKGRAY, WHITE, WHITE, WHITE);


        if (CheckCollisionPointRec(GetMousePosition(),rectFinishRestart) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
            InitGame();
            InitLevels();
            needToLoadLevel = true;
        }
        if (CheckCollisionPointRec(GetMousePosition(),rectFinishHome) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
            InitGame();
            InitLevels();
            needToLoadLevel = true;
            currentScreen = SCREEN_HOME;
        }


    }



    //--------------LOSE-----------------
    if (nbeVie <= 0 && nbeBrickRemaining != 0) {
        isFinish = true;
        DrawRectangle(0,0,screenWidth,screenHeight,(Color){255,0,0,200});
        //DrawTextEx(roboto,"VICTORY !",(Vector2){(screenWidth/2-((MeasureTextEx(roboto,"VICTORY !",70,1)).x/2)),(screenHeight/2-100)},70,1,WHITE);
        //DrawTextEx(roboto_SemiBold,"VICTORY !",(Vector2){(screenWidth/2-((MeasureTextEx(roboto_SemiBold,"VICTORY !",70,1)).x/2)),(screenHeight/2-100)},70,1,WHITE);
        //DrawTextEx(montserrat,"VICTORY !",(Vector2){(screenWidth/2-((MeasureTextEx(montserrat,"VICTORY !",70,1)).x/2)),(screenHeight/2-100)},70,1,WHITE);
        DrawText("DEFEAT !",(screenWidth/2-(MeasureText("DEFEAT !",50)/2)),(screenHeight/2-150),50,WHITE);

        sprintf(resultL1 ,"Game over !");
        sprintf(resultL2 ,"You lost");
        sprintf(resultL3 ,"With %d/%d bricks remaining", nbeBrickRemaining, nbeBricks);
        DrawText(resultL1, (screenWidth/2-(MeasureText(resultL1,20)/2)), (screenHeight/2-80), 20, BLACK);
        DrawText(resultL2, (screenWidth/2-(MeasureText(resultL2,20)/2)), (screenHeight/2-55), 20, BLACK);
        DrawText(resultL3, (screenWidth/2-(MeasureText(resultL3,20)/2)), (screenHeight/2-30), 20, BLACK);


        DrawRectangleRec(rectFinishRestart,DARKGRAY);
        DrawText("RESTART",screenWidth/2-40,(screenHeight/2+50)+15,25,BEIGE);
        DrawCircleSector((Vector2){rectFinishRestart.x+25, rectFinishRestart.y+26}, 15, 210, 500, 20, RED);
        DrawCircle(rectFinishRestart.x+25, rectFinishRestart.y+26, 10, DARKGRAY);
        DrawPoly((Vector2){220, (screenHeight/2+50)+20}, 3, 8, 8, RED);
        DrawRectangleGradientH(rectFinishRestart.x, rectFinishRestart.y+3, 3, rectFinishRestart.height-6, WHITE, DARKGRAY);
        DrawRectangleGradientH(rectFinishRestart.x+rectFinishRestart.width-3, rectFinishRestart.y+3, 3, rectFinishRestart.height-6, DARKGRAY, WHITE);
        DrawRectangleGradientV(rectFinishRestart.x+3, rectFinishRestart.y, rectFinishRestart.width-6, 3, WHITE, DARKGRAY);
        DrawRectangleGradientV(rectFinishRestart.x+3, rectFinishRestart.y+rectFinishRestart.height-3, rectFinishRestart.width-6, 3, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishRestart.x, rectFinishRestart.y, 3, 3}, WHITE, WHITE, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishRestart.x, rectFinishRestart.y+rectFinishRestart.height-3, 3, 3}, WHITE, WHITE, WHITE, DARKGRAY);
        DrawRectangleGradientEx((Rectangle){rectFinishRestart.x+rectFinishRestart.width-3, rectFinishRestart.y, 3, 3}, WHITE, DARKGRAY, WHITE, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishRestart.x+rectFinishRestart.width-3, rectFinishRestart.y+rectFinishRestart.height-3, 3, 3}, DARKGRAY, WHITE, WHITE, WHITE);

        DrawRectangleRec(rectFinishHome,DARKGRAY);
        DrawText("HOME",screenWidth/2-40,(screenHeight/2+150)+15,25,BEIGE);
        DrawRectangle(rectFinishHome.x+15, rectFinishHome.y+20, 20, 20, RED);
        DrawRectangle(rectFinishHome.x+22, rectFinishHome.y+30, 7, 10, DARKGRAY);
        DrawPoly((Vector2){230, (screenHeight/2+150)+17}, 4, 8, 270, RED);
        DrawPoly((Vector2){223, (screenHeight/2+150)+20}, 3, 7, 285, RED);
        DrawPoly((Vector2){236, (screenHeight/2+150)+20}, 3, 7, 255, RED);
        DrawRectangleGradientH(rectFinishHome.x, rectFinishHome.y+3, 3, rectFinishHome.height-6, WHITE, DARKGRAY);
        DrawRectangleGradientH(rectFinishHome.x+rectFinishHome.width-3, rectFinishHome.y+3, 3, rectFinishHome.height-6, DARKGRAY, WHITE);
        DrawRectangleGradientV(rectFinishHome.x+3, rectFinishHome.y, rectFinishHome.width-6, 3, WHITE, DARKGRAY);
        DrawRectangleGradientV(rectFinishHome.x+3, rectFinishHome.y+rectFinishHome.height-3, rectFinishHome.width-6, 3, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishHome.x, rectFinishHome.y, 3, 3}, WHITE, WHITE, DARKGRAY, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishHome.x, rectFinishHome.y+rectFinishHome.height-3, 3, 3}, WHITE, WHITE, WHITE, DARKGRAY);
        DrawRectangleGradientEx((Rectangle){rectFinishHome.x+rectFinishHome.width-3, rectFinishHome.y, 3, 3}, WHITE, DARKGRAY, WHITE, WHITE);
        DrawRectangleGradientEx((Rectangle){rectFinishHome.x+rectFinishHome.width-3, rectFinishHome.y+rectFinishHome.height-3, 3, 3}, DARKGRAY, WHITE, WHITE, WHITE);


        if (CheckCollisionPointRec(GetMousePosition(),rectFinishRestart) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
            InitGame();
            InitLevels();
            needToLoadLevel = true;
        }
        if (CheckCollisionPointRec(GetMousePosition(),rectFinishHome) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
            InitGame();
            InitLevels();
            needToLoadLevel = true;
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


