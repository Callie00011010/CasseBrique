#ifndef LEVELS_H
#define LEVELS_H

#include "raylib.h"

typedef struct BrickType BrickType;
struct BrickType {
    int width;
    int height;
    int durability;
    bool exist;
    Color color;
};

typedef struct BrickPhysic BrickPhysic;
struct BrickPhysic {
    BrickType brickType;
    Rectangle rectBrick;
    Vector2 centerBrick;
};



extern int nbeBricksWidth, nbeBricksHeight, nbeBricks, nbeBrickRemaining;
extern BrickPhysic *currentBrickLevel;


extern BrickType brickEasy, brickMedium, brickHard, brickDemon;


void InitLevels(void);
void UnloadLevels(void);
void DrawLevel(void);
void LoadLevel(BrickType brickType);


#endif // LEVELS_H
