#include <unistd.h>

#include "opengl-window.h"

int a = 100;
int b = 25;
int c = 75;
int d = 0;

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);

  glVertex2i(50, 0);
  glVertex2i(a, b);
  glVertex2i(100, c);
  glVertex2i(50, 100);
  glVertex2i(0, c);
  glVertex2i(d, b);

  glEnd();
  glFlush();
}

void Idle() {
  static int count = 0;

  sleep(1);

  if (count % 3 == 0) {
    // Hexagon
    a = 100;
    b = 25;
    c = 75;
    d = 0;
  } else if (count % 3 == 1) {
    a = 75;
    b = 0;
    c = 50;
    d = 25;
  } else if (count % 3 == 2) {
    // Triangle
    a = 50;
    b = 0;
    c = 0;
    d = 50;
  }

  count++;

  glutPostRedisplay();
}

void Setup() {
  glutDisplayFunc(Display);
  glutIdleFunc(Idle);

  DefaultSetup();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  CreateWindow("Lab 5", Setup);

  return 0;
}
