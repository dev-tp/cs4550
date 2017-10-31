#ifndef CS4550_LAB_4_H_
#define CS4550_LAB_4_H_

#include <GL/glut.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

struct Point3 {
  float x, y, z;
};

struct Vector3 {
  float vertices[3];
};

float scale = 1.0f;
float tx, ty, tz;
float rotation_angle;
Vector3 octahedron[8];

void DrawTriangle(int a, int b, int c);

#endif  // CS4550_LAB_4_H_
