#ifndef CS4550_LAB_SEVEN_H_
#define CS4550_LAB_SEVEN_H_

#include <GL/glut.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

double camera_x = 25.0;
double camera_y = 25.0;
double camera_z = 25.0;

double view_x = 0.0;
double view_y = 0.0;
double view_z = 0.0;

#endif  // CS4550_LAB_SEVEN_H_
