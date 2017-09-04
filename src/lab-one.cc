#include <math.h>

#include <iostream>

#include "opengl-window.h"

#define CIRCUMFERENCE M_PI * 2

static int graph;

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);

  if (0 <= graph && graph <= 2) {
    glBegin(GL_POINTS);

    double half_screen_height = SCREEN_HEIGHT / 2.0;
    double limit = graph == 0 ? 1.0 : graph == 1 ? 2.0 : 3.0;
    int a = graph == 0 ? 100 : 50;

    for (double x = 0.0; x < CIRCUMFERENCE * limit; x += 0.005) {
      double b = graph == 2 ? sin(x) : cos(x);
      glVertex2d(a * x, half_screen_height * b + half_screen_height);
    }

  } else {
    glBegin(GL_LINES);

    double points[10][2] = {
      { 0.0, 5.5 },
      { 5.0, 5.0 },
      { 6.5, 0.0 },
      { 9.0, 5.0 },
      { 14.0, 5.5 },
      { 10.5, 9.0 },
      { 12.0, 14.0 },
      { 6.5, 11.5 },
      { 2.0, 14.0 },
      { 3.5, 9.0 }
    };

    glVertex2d(128 + points[0][0] * 30, SCREEN_HEIGHT - points[0][1] * 30);

    for (int i = 1; i < 10; i++) {
      glVertex2d(128 + points[i][0] * 30, SCREEN_HEIGHT - points[i][1] * 30);
      glVertex2d(128 + points[i][0] * 30, SCREEN_HEIGHT - points[i][1] * 30);
    }

    glVertex2d(128 + points[0][0] * 30, SCREEN_HEIGHT - points[0][1] * 30);
  }

  glEnd();
  glFlush();
}

void GetKey(unsigned char key, int x, int y) {
  graph = 49 <= key && key <= 52 ? key - 49 : 0;
  glutPostRedisplay();
}

void Setup() {
  std::cout << "Enter a value between 1 and 4 to render a different graph\n";

  glutDisplayFunc(Display);
  glutKeyboardFunc(GetKey);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  glPointSize(2.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  CreateWindow("Lab 1", Setup);

  return 0;
}
