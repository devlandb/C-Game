//
// Created by devla on 4/2/2025.
//
// Function prototypes for the objects

#ifndef OBJECTFUNC_H
#define OBJECTFUNC_H

#include "gba.h"
#include "pixelatedPlane.h"


struct obstacle {
  int row,col;
  int width, height;
  int respawnTimer;
  int collected;
  volatile u16 color;
};

void drawObstacles(void);
void undrawObstacles(int row, int col, int width, int height, volatile u16 color);
void initObstacles(void);
void makeObstacles(void);
void updateObstacles(void);
int checkCollision(void);

void drawHardObs(void);
void initHardObs(void);

int checkHardCollision(void);



#endif //OBJECTFUNC_H
