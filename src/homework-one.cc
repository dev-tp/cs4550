#include "homework-one.h"

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);

  // Vertex points here

  glEnd();
  glFlush();
}

void Setup() {
  glutDisplayFunc(Display);
  DefaultSetup();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  CreateWindow("Homework 1", Setup);

  return 0;
}
