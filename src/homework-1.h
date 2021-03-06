#ifndef CS4550_HOMEWORK_1_H_
#define CS4550_HOMEWORK_1_H_

#include <math.h>

#include <vector>

#include <GL/glut.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

#define CIRCUMFERENCE M_PI * 2

class Ball {
  float mass;
  float red, green, blue;
public:
  bool floating;
  float x, y;
  float dx, dy;
  float radius;

  Ball(float x, float y, float radius=10.0f) {
    this->x = x;
    this->y = y;
    this->radius = radius;

    dx = 1.0f;
    dy = 1.0f;

    mass = powf(radius, 3.0f);
  }
  ~Ball() {}

  void CheckForCollision(int position);
  void Draw();
  void SetColor(float red, float green, float blue);
};

static int window_id;

bool slowdown;
float starting_dx, starting_dy;
float starting_x, starting_y;
int ball = -1;
std::vector<Ball> balls;

float Distance(float x0, float y0, float x1, float y1);
void InitialState();

#endif  // CS4550_HOMEWORK_1_H_
