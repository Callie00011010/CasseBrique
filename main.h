#ifndef MAIN_H
#define MAIN_H


typedef enum {
    SCREEN_HOME, SCREEN_LEVEL1, SCREEN_LEVEL2, SCREEN_LEVEL3, SCREEN_LEVEL4
} CurrentScreen;

extern const int screenWidth;
extern const int screenHeight;

extern CurrentScreen currentScreen;
extern bool needToLoadLevel;


#endif // MAIN_H
