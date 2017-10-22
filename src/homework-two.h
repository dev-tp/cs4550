#ifndef CS4550_HOMEWORK_TWO_H_
#define CS4550_HOMEWORK_TWO_H_

#include <GL/glut.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

#define DRAW_CUBE()   \
  if (draw_solid)     \
    glutSolidCube(1); \
  else                \
    glutWireCube(1);

#define DRAW_SPHERE(radius)          \
  if (draw_solid)                    \
    glutSolidSphere(radius, 32, 16); \
  else                               \
    glutWireSphere(radius, 32, 16);

bool display_coordinate_system = true;
bool draw_solid = true;

int azimuth = 340;
int elevation = 30;
float rotation_angle = 0.0f;

float finger = 30.0f;
float lower_arm = 140.0f;
float upper_arm = -60.0f;
float wrist = 10.0f;

void RenderFinger(float x, float y, float z);

#endif  // CS4550_HOMEWORK_TWO_H_
