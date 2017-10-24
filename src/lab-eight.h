#ifndef CS4550_LAB_EIGHT_H_
#define CS4550_LAB_EIGHT_H_

#include <GL/glut.h>

#include "mesh.h"
#include "point3.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

#define WORLD_HEIGHT 100.0f
#define WORLD_WIDTH 100.0f

double eye_x = 0.0;
double eye_y = 0.0;
double eye_z = 50.0;

double look_x = 0.0;
double look_y = 0.0;
double look_z = 0.0;

float frame = 0.0f;

int animate = 0;
int display_mode = 0;
int num_of_points = 0;

Mesh triangular_prism;
Point3 base[3];

void DrawAxes();

#endif  // CS4550_LAB_EIGHT_H_
