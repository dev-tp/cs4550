#ifndef CS4550_OPENGL_WINDOW_H_
#define CS4550_OPENGL_WINDOW_H_

#include <string>

#include <GL/glut.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

void CreateWindow(std::string, void (*setup)());
void DefaultSetup();

#endif  // CS4550_OPENGL_WINDOW_H_
