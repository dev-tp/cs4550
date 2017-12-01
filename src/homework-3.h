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

#define GLUT_SCROLL_DOWN 3
#define GLUT_SCROLL_UP 4

bool register_motion = false;
bool spin = false;

float delta_phi = 0.0f;
float delta_theta = 0.0f;
float phi = 0.0f;
float rho = 10.0f;
float theta = 0.0f;

float look_x = 0.0f;
float look_y = 0.0f;
float look_z = rho;

int x_origin = 0;
int y_origin = 0;

Camera camera;

std::vector<Point3> clicked_points;

void Spin(int segments = 32);

#endif  // CS4550_HOMEWORK_3_H_
