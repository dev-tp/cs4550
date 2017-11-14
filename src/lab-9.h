#ifndef CS4550_LAB_9_H_
#define CS4550_LAB_9_H_

#include "camera.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

bool move_light;

Camera camera;

float rotation_angle = 0.0f;
float x_position = 0.0f;
float z_position = 0.0f;

float light_position[] = {1.0f, 1.0f, 1.0f, 10.0f};

#endif  // CS4550_LAB_9_H_
