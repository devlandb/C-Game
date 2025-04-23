//
// Created by devla on 4/1/2025.
//
// Handles plane drawing, plane movement, plane collision detection
#include <stdio.h>
#include "planeFunc.h"
#include "pixelatedPlane.h"
#include "gba.h"


#define SPEED 1

Plane planeSprite;
// should probably put this in main.c when the state changes to play
void setup(void) {
  planeSprite.row = 140;
  planeSprite.col = 120;
  planeSprite.collected = 0;
  planeSprite.time = 10;
  planeSprite.playTime = 0;
}


void drawPlane(void) {
  drawImageDMA(planeSprite.row, planeSprite.col, PIXELATEDPLANE_WIDTH, PIXELATEDPLANE_HEIGHT, pixelatedPlane);
}

void undrawPlane(int row, int col, int width, int height, volatile u16 color) {
  for (int r = row; r < row + height; r++) {
    DMA[DMA_CHANNEL_3].src = &color;
    DMA[DMA_CHANNEL_3].dst = videoBuffer + OFFSET(r, col, WIDTH);
    DMA[DMA_CHANNEL_3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
  }
}

void movePlane(u32 buttons) {
  undrawPlane(planeSprite.row, planeSprite.col, PIXELATEDPLANE_WIDTH, PIXELATEDPLANE_HEIGHT, BLACK);

  // Decide where to place the plane
  if (buttons & BUTTON_LEFT) {
    planeSprite.col += SPEED;
  }
  if (buttons & BUTTON_RIGHT) {
    planeSprite.col -= SPEED;
  }
  if (buttons & BUTTON_DOWN) {
    planeSprite.row -= SPEED;
  }
  if (buttons & BUTTON_UP) {
    planeSprite.row += SPEED;
  }

  // Make sure the plane is always in bounds
  if (planeSprite.row < 0) planeSprite.row = 0;
  if (planeSprite.row > HEIGHT - PIXELATEDPLANE_HEIGHT) planeSprite.row = HEIGHT - PIXELATEDPLANE_HEIGHT;
  if (planeSprite.col < 0) planeSprite.col = 0;
  if (planeSprite.col > WIDTH - PIXELATEDPLANE_WIDTH) planeSprite.col = WIDTH - PIXELATEDPLANE_WIDTH;

  drawPlane();
}
void staticMovePlane(void) {
  undrawPlane(planeSprite.row, planeSprite.col, PIXELATEDPLANE_WIDTH, PIXELATEDPLANE_HEIGHT, BLACK);
  planeSprite.col += SPEED;
  if (planeSprite.col > WIDTH - PIXELATEDPLANE_WIDTH) planeSprite.col = 0;
  drawPlane();
}