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
    // TODO Rotate star 180 degrees
    glBegin(GL_LINES);

    glVertex2d(128 + 0.0, 5.5 * 30);
    glVertex2d(128 + 5.0 * 30, 5.0 * 30);

    glVertex2d(128 + 5.0 * 30, 5.0 * 30);
    glVertex2d(128 + 6.5 * 30, 0.0);

    glVertex2d(128 + 6.5 * 30, 0.0);
    glVertex2d(128 + 9.0 * 30, 5.0 * 30);

    glVertex2d(128 + 9.0 * 30, 5.0 * 30);
    glVertex2d(128 + 14.0 * 30, 5.5 * 30);

    glVertex2d(128 + 14.0 * 30, 5.5 * 30);
    glVertex2d(128 + 10.5 * 30, 9.0 * 30);

    glVertex2d(128 + 10.5 * 30, 9.0 * 30);
    glVertex2d(128 + 12.0 * 30, 14.0 * 30);

    glVertex2d(128 + 12.0 * 30, 14.0 * 30);
    glVertex2d(128 + 6.5 * 30, 11.5 * 30);

    glVertex2d(128 + 6.5 * 30, 11.5 * 30);
    glVertex2d(128 + 2.0 * 30, 14.0 * 30);

    glVertex2d(128 + 2.0 * 30, 14.0 * 30);
    glVertex2d(128 + 3.5 * 30, 9.0 * 30);

    glVertex2d(128 + 3.5 * 30, 9.0 * 30);
    glVertex2d(128 + 0.0, 5.5 * 30);
  }

  glEnd();
  glFlush();
}

void GetKey(unsigned char key, int x, int y) {
  graph = 49 <= key && key <= 52 ? key - 49 : 0;
  Display();
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
