#ifndef CS4550_HOMEWORK_3_H_
#define CS4550_HOMEWORK_3_H_

#include <vector>

#include <GL/glut.h>

#include "camera.h"
#include "point3.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

Camera camera;
std::vector<Point3> clicked_points;

#endif  // CS4550_HOMEWORK_3_H_
