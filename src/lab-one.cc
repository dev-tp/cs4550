#include <math.h>

#include <iostream>

#include <GL/glut.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

#define CIRCUMFERENCE M_PI * 2

static int graph;

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);

  double half_screen_height = SCREEN_HEIGHT / 2.0;

  if (graph == 0) {
    glBegin(GL_POINTS);
    for (double x = 0.0; x < CIRCUMFERENCE; x += 0.005) {
      glVertex2d(100 * x, half_screen_height * cos(x) + half_screen_height);
    }
  } else if (graph == 1) {
    glBegin(GL_POINTS);
    for (double x = 0.0; x < CIRCUMFERENCE * 2; x += 0.005) {
      glVertex2d(50 * x, half_screen_height * cos(x) + half_screen_height);
    }
  } else if (graph == 2) {
    glBegin(GL_POINTS);
    for (double x = 0.0; x < CIRCUMFERENCE * 3; x += 0.005) {
      glVertex2d(50 * x, half_screen_height * sin(x) + half_screen_height);
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

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  std::cout << "Enter a value between 1 and 4 to render a different graph\n";

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow("Lab 1");

  glutDisplayFunc(Display);
  glutKeyboardFunc(GetKey);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  glPointSize(2.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);

  glutMainLoop();

  return 0;
}
