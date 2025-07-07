#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "levels.h"
#include "main.h"

#define BRICK_WIDTH 50
#define BRICK_HEIGHT 20
#define BRICK_INTERVALE_WIDTH 100
#define BRICK_INTERVALE_HEIGHT 10
#define BRICK_X_START   10
#define BRICK_Y_START   65



BrickType brickEasy;
BrickType brickMedium;
BrickType brickHard;
BrickType brickDemon;



int nbeBricksWidth, nbeBricksHeight, nbeBricks;
BrickPhysic *brickLevel1, *brickLevel2, *brickLevel3, *brickLevel4;


int rowLevel, colLevel, indexLevel;
int xBrick, yBrick;

int indexLevelDraw;
char textDrawDurability[4];
float fontSizeTextDrawDurability;



void InitLevels(void) {

    //------Definition------
    brickEasy = (BrickType){BRICK_WIDTH, BRICK_HEIGHT, 1, true, (Color){0, 180, 255, 255}};
    brickMedium = (BrickType){BRICK_WIDTH, BRICK_HEIGHT, 3, true, (Color){0, 180, 48, 255}};
    brickHard = (BrickType){BRICK_WIDTH, BRICK_HEIGHT, 5, true, (Color){210, 120, 0, 255}};
    brickDemon = (BrickType){BRICK_WIDTH, BRICK_HEIGHT, 15, true, MAROON};



    //------Disposition--------
    nbeBricksWidth = screenWidth/(BRICK_WIDTH+BRICK_INTERVALE_WIDTH);
    nbeBricksHeight = ((screenHeight/1.75)-BRICK_Y_START)/(BRICK_HEIGHT+BRICK_INTERVALE_HEIGHT);
    nbeBricks = nbeBricksWidth * nbeBricksHeight;

    brickLevel1 = malloc(nbeBricks * sizeof(BrickPhysic));
    if (brickLevel1 == NULL) {exit(0);}
    brickLevel2 = malloc(nbeBricks * sizeof(BrickPhysic));
    if (brickLevel2 == NULL) {exit(0);}
    brickLevel3 = malloc(nbeBricks * sizeof(BrickPhysic));
    if (brickLevel3 == NULL) {exit(0);}
    brickLevel4 = malloc(nbeBricks * sizeof(BrickPhysic));
    if (brickLevel4 == NULL) {exit(0);}




    //---------Creation Bricks Lvl 1--------
    indexLevel = 0;
    for (rowLevel = 0; rowLevel < nbeBricksWidth; rowLevel++) {
        for (colLevel = 0; colLevel < nbeBricksHeight; colLevel++) {
            xBrick = BRICK_X_START + rowLevel * (BRICK_WIDTH+BRICK_INTERVALE_WIDTH);
            yBrick = BRICK_Y_START + colLevel * (BRICK_HEIGHT+BRICK_INTERVALE_HEIGHT);
            brickLevel1[indexLevel] = (BrickPhysic){brickEasy, (Rectangle){xBrick, yBrick, brickEasy.width, brickEasy.height}};
            indexLevel++;
        }
    }

    //---------Creation Bricks Lvl 2--------
    indexLevel = 0;
    for (rowLevel = 0; rowLevel < nbeBricksWidth; rowLevel++) {
        for (colLevel = 0; colLevel < nbeBricksHeight; colLevel++) {
            xBrick = BRICK_X_START + rowLevel * (BRICK_WIDTH+BRICK_INTERVALE_WIDTH);
            yBrick = BRICK_Y_START + colLevel * (BRICK_HEIGHT+BRICK_INTERVALE_HEIGHT);
            brickLevel2[indexLevel] = (BrickPhysic){brickMedium, (Rectangle){xBrick, yBrick, brickMedium.width, brickMedium.height}};
            indexLevel++;
        }
    }

    //---------Creation Bricks Lvl 3--------
    indexLevel = 0;
    for (rowLevel = 0; rowLevel < nbeBricksWidth; rowLevel++) {
        for (colLevel = 0; colLevel < nbeBricksHeight; colLevel++) {
            xBrick = BRICK_X_START + rowLevel * (BRICK_WIDTH+BRICK_INTERVALE_WIDTH);
            yBrick = BRICK_Y_START + colLevel * (BRICK_HEIGHT+BRICK_INTERVALE_HEIGHT);
            brickLevel3[indexLevel] = (BrickPhysic){brickHard, (Rectangle){xBrick, yBrick, brickHard.width, brickHard.height}};
            indexLevel++;
        }
    }

    //---------Creation Bricks Lvl 4--------
    indexLevel = 0;
    for (rowLevel = 0; rowLevel < nbeBricksWidth; rowLevel++) {
        for (colLevel = 0; colLevel < nbeBricksHeight; colLevel++) {
            xBrick = BRICK_X_START + rowLevel * (BRICK_WIDTH+BRICK_INTERVALE_WIDTH);
            yBrick = BRICK_Y_START + colLevel * (BRICK_HEIGHT+BRICK_INTERVALE_HEIGHT);
            brickLevel4[indexLevel] = (BrickPhysic){brickDemon, (Rectangle){xBrick, yBrick, brickDemon.width, brickDemon.height}};
            indexLevel++;
        }
    }





}



void DrawLevel1(void) {
    indexLevelDraw = 0;
    for (indexLevelDraw = 0; indexLevelDraw < nbeBricks; indexLevelDraw++) {
        if (brickLevel1[indexLevelDraw].brickType.exist == true) {
            DrawRectangleRec(brickLevel1[indexLevelDraw].rectBrick, brickLevel1[indexLevelDraw].brickType.color);
            sprintf(textDrawDurability, "%d", brickLevel1[indexLevelDraw].brickType.durability);
            fontSizeTextDrawDurability = (brickLevel1[indexLevelDraw].rectBrick.height) * 0.8f;
            DrawText(textDrawDurability, ((brickLevel1[indexLevelDraw].rectBrick.x)+((brickLevel1[indexLevelDraw].rectBrick.width)/2)-((MeasureTextEx(GetFontDefault(), textDrawDurability, fontSizeTextDrawDurability, 1).x)/2)), ((brickLevel1[indexLevelDraw].rectBrick.y)+((brickLevel1[indexLevelDraw].rectBrick.height)/2)-(fontSizeTextDrawDurability/2)), fontSizeTextDrawDurability, WHITE);

        }
    }

}


void DrawLevel2(void) {
    indexLevelDraw = 0;
    for (indexLevelDraw = 0; indexLevelDraw < nbeBricks; indexLevelDraw++) {
        if (brickLevel2[indexLevelDraw].brickType.exist == true) {
            DrawRectangleRec(brickLevel2[indexLevelDraw].rectBrick, brickLevel2[indexLevelDraw].brickType.color);
            sprintf(textDrawDurability, "%d", brickLevel2[indexLevelDraw].brickType.durability);
            fontSizeTextDrawDurability = (brickLevel2[indexLevelDraw].rectBrick.height) * 0.8f;
            DrawText(textDrawDurability, ((brickLevel2[indexLevelDraw].rectBrick.x)+((brickLevel2[indexLevelDraw].rectBrick.width)/2)-((MeasureTextEx(GetFontDefault(), textDrawDurability, fontSizeTextDrawDurability, 1).x)/2)), ((brickLevel2[indexLevelDraw].rectBrick.y)+((brickLevel2[indexLevelDraw].rectBrick.height)/2)-(fontSizeTextDrawDurability/2)), fontSizeTextDrawDurability, WHITE);

        }
    }

}


void DrawLevel3(void) {
    indexLevelDraw = 0;
    for (indexLevelDraw = 0; indexLevelDraw < nbeBricks; indexLevelDraw++) {
        if (brickLevel3[indexLevelDraw].brickType.exist == true) {
            DrawRectangleRec(brickLevel3[indexLevelDraw].rectBrick, brickLevel3[indexLevelDraw].brickType.color);
            sprintf(textDrawDurability, "%d", brickLevel3[indexLevelDraw].brickType.durability);
            fontSizeTextDrawDurability = (brickLevel3[indexLevelDraw].rectBrick.height) * 0.8f;
            DrawText(textDrawDurability, ((brickLevel3[indexLevelDraw].rectBrick.x)+((brickLevel3[indexLevelDraw].rectBrick.width)/2)-((MeasureTextEx(GetFontDefault(), textDrawDurability, fontSizeTextDrawDurability, 1).x)/2)), ((brickLevel3[indexLevelDraw].rectBrick.y)+((brickLevel3[indexLevelDraw].rectBrick.height)/2)-(fontSizeTextDrawDurability/2)), fontSizeTextDrawDurability, WHITE);

        }
    }

}


void DrawLevel4(void) {
    indexLevelDraw = 0;
    for (indexLevelDraw = 0; indexLevelDraw < nbeBricks; indexLevelDraw++) {
        if (brickLevel4[indexLevelDraw].brickType.exist == true) {
            DrawRectangleRec(brickLevel4[indexLevelDraw].rectBrick, brickLevel4[indexLevelDraw].brickType.color);
            sprintf(textDrawDurability, "%d", brickLevel4[indexLevelDraw].brickType.durability);
            fontSizeTextDrawDurability = (brickLevel4[indexLevelDraw].rectBrick.height) * 0.8f;
            DrawText(textDrawDurability, ((brickLevel4[indexLevelDraw].rectBrick.x)+((brickLevel4[indexLevelDraw].rectBrick.width)/2)-((MeasureTextEx(GetFontDefault(), textDrawDurability, fontSizeTextDrawDurability, 1).x)/2)), ((brickLevel4[indexLevelDraw].rectBrick.y)+((brickLevel4[indexLevelDraw].rectBrick.height)/2)-(fontSizeTextDrawDurability/2)), fontSizeTextDrawDurability, WHITE);

        }
    }

}


void UnloadLevels(void) {
    if (brickLevel1 != NULL) {
        free(brickLevel1);
        brickLevel1 = NULL;
    }
    if (brickLevel2 != NULL) {
        free(brickLevel2);
        brickLevel2 = NULL;
    }
    if (brickLevel3 != NULL) {
        free(brickLevel3);
        brickLevel3 = NULL;
    }
    if (brickLevel4 != NULL) {
        free(brickLevel4);
        brickLevel4 = NULL;
    }
}




