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
};



extern int nbeBricksWidth, nbeBricksHeight, nbeBricks;
extern BrickPhysic *brickLevel1, *brickLevel2, *brickLevel3, *brickLevel4;




void InitLevels(void);
void DrawLevel1(void);
void DrawLevel2(void);
void DrawLevel3(void);
void DrawLevel4(void);
void UnloadLevels(void);



#endif // LEVELS_H
