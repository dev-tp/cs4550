#include "opengl-window.h"

struct Point {
  int x, y;
};

Point corners[2] = {
  {.x =  0, .y =  0},
  {.x = 10, .y = 10}
};

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
  if (key == 'Z') {
    // Zoom-out
    glutPostRedisplay();
  } else if (key == 'z') {
    // Zoom-in
    glutPostRedisplay();
  }
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
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  for (int i = 0; i < 2; i++) {
    corners[i].x += HALF_SCREEN_WIDTH;
    corners[i].y += HALF_SCREEN_HEIGHT;
  }

  CreateWindow("Lab 3 (Practice)", Setup);

  return 0;
}
