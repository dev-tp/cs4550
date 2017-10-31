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
  usleep(35000);

  a -= 2;
  b -= 1;
  c -= 3;
  d += 2;

  if (a == 40) {
    a = 100;
    b = 25;
    c = 75;
    d = 0;
  }

  glutPostRedisplay();
}

void Setup() {
  glutDisplayFunc(Display);
  glutIdleFunc(Idle);

  DefaultSetup();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  CreateWindow("Lab 3", Setup);

  return 0;
}
