#ifndef CS4550_LAB_2_H_
#define CS4550_LAB_2_H_

#include <math.h>

#include "opengl-window.h"

#define CIRCUMFERENCE M_PI * 2

GLenum mode = GL_POINTS;

enum Shape {
  CIRCLE, ELLIPSE
};

Shape shape;

double left;
double right = SCREEN_WIDTH;
double bottom;
double top = SCREEN_HEIGHT;

int radius = 100;

double h = SCREEN_WIDTH / 2;
double k = SCREEN_HEIGHT / 2;

void Display();
void GetKey(unsigned char, int, int);
void GetSpecialKey(int, int, int);
void Setup();
void UpdateWindowDimensions();

#endif  // CS4550_LAB_2_H_
