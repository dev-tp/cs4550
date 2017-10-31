#include "lab-2.h"

#include <iostream>

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(mode);

  if (shape == CIRCLE) {
    for (double theta = 0.0; theta < 1.0; theta += 0.01) {
      double x = h + radius * cos(CIRCUMFERENCE * theta);
      double y = k + radius * sin(CIRCUMFERENCE * theta);

      glVertex2d(x, y);
    }
  } else {
    for (double theta = 0.0; theta < 1.0; theta += 0.01) {
      double x = h + radius * cos(CIRCUMFERENCE * theta);
      double y = k - 0.5 * radius * sin(CIRCUMFERENCE * theta);

      glVertex2d(x, y);
    }
  }

  glEnd();
  glFlush();
}

void GetKey(unsigned char key, int x, int y) {
  static float width = 1.0f;

  if (key == '+') {
    radius += 10;
  } else if (key == '-') {
    radius -= 10;
  } else if (key == 'B') {
    width -= 1.0f;

    if (width < 0.0f)
      width = 1.0f;

    if (mode == GL_POINTS)
      glPointSize(width);
    else
      glLineWidth(width);

  } else if (key == 'Z') {
    top /= 0.9;
    right /= 0.9;
    UpdateWindowDimensions();
  } else if (key == 'b') {
    width += 1.0f;

    if (mode == GL_POINTS)
      glPointSize(width);
    else
      glLineWidth(width);

  } else if (key == 't' || key == 'T') {
    mode = mode == GL_POINTS ? GL_LINE_LOOP : GL_POINTS;
  } else if (key == 'z') {
    top *= 0.9;
    right *= 0.9;
    UpdateWindowDimensions();
  } else {
    return;
  }

  glutPostRedisplay();
}

void GetSpecialKey(int key, int x, int y) {
  if (key == GLUT_KEY_RIGHT)
    h += 10;
  else if (key == GLUT_KEY_LEFT)
    h -= 10;
  else if (key == GLUT_KEY_UP)
    k += 10;
  else if (key == GLUT_KEY_DOWN)
    k -= 10;
  else
    return;

  glutPostRedisplay();
}

void Setup() {
  glutDisplayFunc(Display);
  glutKeyboardFunc(GetKey);
  glutSpecialFunc(GetSpecialKey);

  DefaultSetup();
}

void UpdateWindowDimensions() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(left, right, bottom, top);
}

int main(int argc, char* argv[]) {
  int option;

  std::cout << "1. Draw a circle\n";
  std::cout << "2. Draw an ellipse\n";
  std::cout << "Choose 1 or 2: ";
  std::cin >> option;

  shape = option == 1 ? CIRCLE : ELLIPSE;

  glutInit(&argc, argv);
  CreateWindow("Lab 2", Setup);

  return 0;
}
