#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "levels.h"
#include "main.h"

#define BRICK_WIDTH 108
#define BRICK_HEIGHT 25
#define BRICK_INTERVALE_WIDTH 10
#define BRICK_INTERVALE_HEIGHT 8
#define BRICK_X_START   10
#define BRICK_Y_START   65



BrickType brickEasy, brickMedium, brickHard, brickDemon;



int nbeBricksWidth, nbeBricksHeight, nbeBricks, nbeBrickRemaining;
BrickPhysic *currentBrickLevel = NULL;


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
    nbeBricksWidth = (screenWidth-BRICK_X_START)/(BRICK_WIDTH+BRICK_INTERVALE_WIDTH);
    nbeBricksHeight = ((screenHeight/1.75)-BRICK_Y_START)/(BRICK_HEIGHT+BRICK_INTERVALE_HEIGHT);
    nbeBricks = nbeBricksWidth * nbeBricksHeight;
    nbeBrickRemaining = nbeBricks;



}



void LoadLevel(BrickType brickType) {
    UnloadLevels();

    currentBrickLevel = malloc(nbeBricks * sizeof(BrickPhysic));
    if (currentBrickLevel == NULL) {exit(0);}


    indexLevel = 0;
    for (rowLevel = 0; rowLevel < nbeBricksWidth; rowLevel++) {
        for (colLevel = 0; colLevel < nbeBricksHeight; colLevel++) {
            xBrick = BRICK_X_START + rowLevel * (BRICK_WIDTH+BRICK_INTERVALE_WIDTH);
            yBrick = BRICK_Y_START + colLevel * (BRICK_HEIGHT+BRICK_INTERVALE_HEIGHT);
            currentBrickLevel[indexLevel] = (BrickPhysic){brickType, (Rectangle){xBrick, yBrick, brickType.width, brickType.height}, (Vector2){xBrick+(brickType.width/2.0f), yBrick+(brickType.height/2.0f)}};
            indexLevel++;
        }
    }
}




void DrawLevel(void) {
    indexLevelDraw = 0;
    for (indexLevelDraw = 0; indexLevelDraw < nbeBricks; indexLevelDraw++) {
        if (currentBrickLevel[indexLevelDraw].brickType.exist == true) {
            DrawRectangleRec(currentBrickLevel[indexLevelDraw].rectBrick, currentBrickLevel[indexLevelDraw].brickType.color);
            sprintf(textDrawDurability, "%d", currentBrickLevel[indexLevelDraw].brickType.durability);
            fontSizeTextDrawDurability = (currentBrickLevel[indexLevelDraw].rectBrick.height) * 0.8f;
            DrawText(textDrawDurability, ((currentBrickLevel[indexLevelDraw].rectBrick.x)+((currentBrickLevel[indexLevelDraw].rectBrick.width)/2)-((MeasureTextEx(GetFontDefault(), textDrawDurability, fontSizeTextDrawDurability, 1).x)/2)), ((currentBrickLevel[indexLevelDraw].rectBrick.y)+((currentBrickLevel[indexLevelDraw].rectBrick.height)/2)-(fontSizeTextDrawDurability/2)), fontSizeTextDrawDurability, WHITE);

        }
    }
}



void UnloadLevels(void) {
    if (currentBrickLevel != NULL) {
        free(currentBrickLevel);
        currentBrickLevel = NULL;
    }


}




