#ifndef CS4550_HOMEWORK_ONE_H_
#define CS4550_HOMEWORK_ONE_H_

#include <math.h>

#include <vector>

#include <GL/glut.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

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

  void CheckForCollision(int position);
  void Draw();
  void SetColor(float red, float green, float blue);
};

static int window_id;
std::vector<Ball> balls;

void InitialState();

#endif  // CS4550_HOMEWORK_ONE_H_
