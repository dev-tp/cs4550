#include "homework-two.h"

#include <math.h>

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  double dimension = 45.0;  // Dimension of the orthagonal box

  double camera_x = -2 * dimension * sin(M_PI / 180.0 * azimuth) *
    cos(M_PI / 180.0 * elevation);
  double camera_z = 2 * dimension * cos(M_PI / 180.0 * azimuth) *
    cos(M_PI / 180.0 * elevation);
  double camera_y = 2 * dimension * sin(M_PI / 180.0 * elevation);

  gluLookAt(camera_x, camera_y, camera_z, 0.0, 0.0, 0.0, 0.0,
            cos(M_PI / 180.0 * elevation), 0.0);

  glBegin(GL_LINES);

  // x-axis line
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(100.0f, 0.0f, 0.0f);

  // y-axis line
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 100.0f, 0.0f);

  // z-axis line
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 100.0f);

  glEnd();

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

void RegisterKey(unsigned char key, int x, int y) {
  if (key == 'q')
    exit(0);
}

void RegisterSpecialKey(int key, int x, int y) {
  if (key == GLUT_KEY_RIGHT)
    azimuth -= 5;
  else if (key == GLUT_KEY_LEFT)
    azimuth += 5;
  else if (key == GLUT_KEY_UP)
    elevation += 5;
  else if (key == GLUT_KEY_DOWN)
    elevation -= 5;

  azimuth %= 360;
  elevation %= 360;

  glutPostRedisplay();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow("Homework 2");

  Initialize();

  glutDisplayFunc(Display);
  glutKeyboardFunc(RegisterKey);
  glutSpecialFunc(RegisterSpecialKey);

  glutMainLoop();

  return 0;
}
