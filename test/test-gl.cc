#include <math.h>

#include <GL/glut.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define POSITION_X (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2
#define POSITION_Y (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);

  double a = SCREEN_WIDTH / 4.0;
  double b = SCREEN_HEIGHT / 2.0;

  for (double x = 0.0; x < 4.0; x += 0.005)
    glVertex2d(a * x, b * exp(-x) * cos(2 * 3.14159265 * x) + b);

  glEnd();
  glFlush();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow("Cosine function");
  glutDisplayFunc(Display);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glPointSize(2.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);

  glutMainLoop();

  return 0;
}
