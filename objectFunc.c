//
// Created by devla on 4/2/2025.
//
#include "gba.h"
#include "objectFunc.h"
#include "planeFunc.h"
#include "main.h"
#define MAX_OBSTACLES 5
#define SPEED 1
#define MAX_HARD_OBS 10

struct obstacle obstacles[MAX_OBSTACLES];
struct obstacle hardObstacles[MAX_HARD_OBS];



void drawObstacles(void) {
  for (int i = 0; i < MAX_OBSTACLES; i++) {
    struct obstacle obstacle = obstacles[i];
    drawRectDMA(obstacle.row, obstacle.col, obstacle.width, obstacle.height, obstacle.color);
  }
}

void drawHardObs(void) {
  for (int i = 0; i < MAX_HARD_OBS; i++) {
    struct obstacle hardObstacle = hardObstacles[i];
    drawRectDMA(hardObstacle.row, hardObstacle.col, hardObstacle.width, hardObstacle.height, hardObstacle.color);
  }
}

void initObstacles(void) {
  for (int i = 0; i < MAX_OBSTACLES; i++) {
    obstacles[i].row = randint(15,160 - 30);
    obstacles[i].col = randint(15,235);
    obstacles[i].width = 5;
    obstacles[i].height = 5;
    obstacles[i].collected = 0;
    obstacles[i].color = (i == MAX_OBSTACLES - 1) ? RED : GREEN;
  }
}
void initHardObs(void) {
  for (int i = 0; i < MAX_HARD_OBS; i++) {
    hardObstacles[i].row = randint(15,160 - 30);
    hardObstacles[i].col = randint(15,235);
    hardObstacles[i].width = 3;
    hardObstacles[i].height = 3;
    hardObstacles[i].collected = 0;
    hardObstacles[i].color = (i % 2 == 0) ? RED : GREEN;
  }
}



/*
void makeObstacles(void) {
  for (int i = 0; i < MAX_OBSTACLES; i++) {
    if (obstacles[i].col + obstacles[i].width < 0) {
      obstacles[i].col = randint(240,600);
      obstacles[i].row = randint(0,160 - 5);
    }
  }
}
 */
int checkCollision(void) {
  for (int i = 0; i < MAX_OBSTACLES; i++) {
    if (planeSprite.row < obstacles[i].row + 5 && planeSprite.row + PIXELATEDPLANE_HEIGHT > obstacles[i].row
        && planeSprite.col < obstacles[i].col + 5 && planeSprite.col + PIXELATEDPLANE_WIDTH > obstacles[i].col &&
        obstacles[i].collected == 0) {
      if (i == MAX_OBSTACLES - 1) {
        return 0;
      }
      obstacles[i].color = BLACK;
      obstacles[i].collected = 1;
      return 1;
    }
  }
  return 2;
}
int checkHardCollision(void) {
  for (int i = 0; i < MAX_HARD_OBS; i++) {
    if (planeSprite.row < hardObstacles[i].row + 5 && planeSprite.row + PIXELATEDPLANE_HEIGHT > hardObstacles[i].row
        && planeSprite.col < hardObstacles[i].col + 5 && planeSprite.col + PIXELATEDPLANE_WIDTH > hardObstacles[i].col &&
        hardObstacles[i].collected == 0) {
      if (i % 2 == 0) {
        return 0;
      }
      hardObstacles[i].color = BLACK;
      hardObstacles[i].collected = 1;
      return 1;
      }
  }
  return 2;
}

/*
void updateObstacles(void) {
  for (int i = 0; i < MAX_OBSTACLES; i++) {
    undrawPlane(obstacles[i].row, obstacles[i].col, obstacles[i].width, obstacles[i].height, BLACK);

    if (checkCollision(planeSprite.row, planeSprite.col, PIXELATEDPLANE_WIDTH, PIXELATEDPLANE_HEIGHT,
                       obstacles[i].row, obstacles[i].col, obstacles[i].width, obstacles[i].height)) {
      planeSprite.lives -= 1;
                       }

    obstacles[i].col -= SPEED;
    if (obstacles[i].col < 0) {
      if (obstacles[i].respawnTimer > 0) {
        obstacles[i].respawnTimer--;
        continue;
      } else if (obstacles[i].respawnTimer == 0) {
          undrawPlane(obstacles[i].row, obstacles[i].col, obstacles[i].width, obstacles[i].height, BLACK);
          obstacles[i].col = 239; //randint(300,600);
          obstacles[i].row = randint(0,160 - 5);
          obstacles[i].respawnTimer = 60;
      }
    }
    drawObstacles(obstacles[i].width, obstacles[i].height, GREEN);
  }
}
 */
