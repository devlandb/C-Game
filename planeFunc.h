//
// Created by devla on 4/1/2025.
//
// Defines function prototypes for plane functionality
#ifndef PLANEFUNC_H
#define PLANEFUNC_H

#include "gba.h"


typedef struct {
    int row;
    int col;
    int collected;
    int time;
    int playTime;
} Plane;

extern Plane planeSprite;

void setup(void);
void drawPlane(void);
void undrawPlane(int row, int col, int width, int height, volatile u16 color);
void movePlane(u32 buttons);
void staticMovePlane(void);
#endif //PLANEFUNC_H
