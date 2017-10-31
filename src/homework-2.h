#ifndef CS4550_HOMEWORK_2_H_
#define CS4550_HOMEWORK_2_H_

#include <GL/glut.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

bool active;
bool camera_rotating;
bool display_coordinate_system;
bool draw_solid = true;
bool reset;
bool throwing_ball;

double camera_x = 25.0;
double camera_y = 25.0;
double camera_z = 25.0;
double theta = 0.0;

float ball_movement = 0.5f;
float finger = 30.0f;
float lower_arm = 140.0f;
float position_x = 0.0f;
float position_z = 0.0f;
float rotation_angle = 0.0f;
float upper_arm = -60.0f;
float wrist = 10.0f;

int window_id = 0;

void DrawCube();
void DrawSphere(double radius);
void RenderFinger(float x, float y, float z);
void RenderWall(float x, float y, float z, float translate_x, float translate_y,
                float translate_z);
void Reset();

#endif  // CS4550_HOMEWORK_2_H_
