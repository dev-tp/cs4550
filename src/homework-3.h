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

float ambient[][4] = {
  {0.24725f, 0.1995f, 0.0745f, 1.0f},
  {0.0f, 0.0f, 0.0f, 1.0f},
};

float diffusion[][4] = {
  {0.75164f, 0.60648f, 0.22648f, 1.0f},
  {0.55f, 0.55f, 0.55f, 1.0f},
};

float specular[][4] = {
  {0.628281f, 0.555802f, 0.366065f, 1.0f},
  {0.70f, 0.70f, 0.70f, 1.0f},
};

float shine[] = {0.4f, 0.25f};

int material = 0;  // 0: Gold, 1: White plastic
int x_origin = 0;
int y_origin = 0;

Camera camera;

std::vector<Point3> clicked_points;

void Spin(int segments = 32);
void SetLight(int light_source, float position[]);

#endif  // CS4550_HOMEWORK_3_H_
