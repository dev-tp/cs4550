#include "lab-three.h"

#include "opengl-window.h"

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_QUADS);

  glVertex2i(corners[0].x, corners[0].y);
  glVertex2i(corners[1].x, corners[0].y);
  glVertex2i(corners[1].x, corners[1].y);
  glVertex2i(corners[0].x, corners[1].y);

  glEnd();
  glFlush();
}

void GetKey(unsigned char key, int x, int y) {
  // TODO Focus on the centre when zooming in/out
  if (key == 'Z') {
    top /= 0.9;
    right /= 0.9;
  } else if (key == 'z') {
    top *= 0.9;
    right *= 0.9;
  } else {
    return;
  }

  UpdateWindowDimensions();
  glutPostRedisplay();
}

void GetSpecialKey(int key, int x, int y) {
  if (key == GLUT_KEY_RIGHT) {
    corners[0].x += 10;
    corners[1].x += 10;
  } else if (key == GLUT_KEY_LEFT) {
    corners[0].x -= 10;
    corners[1].x -= 10;
  } else if (key == GLUT_KEY_UP) {
    corners[0].y += 10;
    corners[1].y += 10;
  } else if (key == GLUT_KEY_DOWN) {
    corners[0].y -= 10;
    corners[1].y -= 10;
  } else {
    return;
  }

  glutPostRedisplay();
}

void Setup() {
  glutDisplayFunc(Display);
  glutKeyboardFunc(GetKey);
  glutSpecialFunc(GetSpecialKey);

  DefaultSetup();
  UpdateWindowDimensions();
}

void UpdateWindowDimensions() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(left, right, bottom, top);
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  right = SCREEN_WIDTH;
  top = SCREEN_HEIGHT;

  for (int i = 0; i < 2; i++) {
    corners[i].x += HALF_SCREEN_WIDTH;
    corners[i].y += HALF_SCREEN_HEIGHT;
  }

  CreateWindow("Lab 3 (Practice)", Setup);

  return 0;
}
