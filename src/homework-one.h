#ifndef CS4550_HOMEWORK_ONE_H_
#define CS4550_HOMEWORK_ONE_H_

#include <math.h>

#include <vector>

#include "opengl-window.h"

#define CIRCUMFERENCE M_PI * 2

class Ball {
  float red, green, blue;
public:
  float x, y;
  float dx, dy;
  float radius;

  Ball(float x, float y, float radius=10.0f) {
    this->x = x;
    this->y = y;
    this->radius = radius;

    dx = 1.0f;
    dy = 1.0f;
  }
  ~Ball() {}

  void Draw();
  void SetColor(float red, float green, float blue);
};

std::vector<Ball> balls;

#endif  // CS4550_HOMEWORK_ONE_H_
