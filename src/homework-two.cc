#include "homework-two.h"

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(camera_x, camera_y, camera_z, view_x, view_y, view_z, 0.0, 1.0, 0.0);

  // Add 3D vectors here

  glutSwapBuffers();
}

void Initialize() {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_SMOOTH);

  float light_intensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
  float position[] = {2.0f, 6.0f, 3.0f, 0.0f};

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  // Enable shading
  float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

  glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

  // Enable RGB
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3.5, 3.5, -3.5, 3.5, 0.1, 100.0);
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow("Homework 2");

  Initialize();

  glutDisplayFunc(Display);

  glutMainLoop();

  return 0;
}
