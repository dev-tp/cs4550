#include "homework-3.h"

#include <math.h>

#include "vector3.h"

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  camera.Set(Point3(look_x, look_y, look_z));

  glBegin(GL_LINES);

  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-50.0f, 0.0f, 0.0f);
  glVertex3f(50.0f, 0.0f, 0.0f);

  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, -50.0f, 0.0f);
  glVertex3f(0.0f, 50.0f, 0.0f);

  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, -50.0f);
  glVertex3f(0.0f, 0.0f, 50.0f);

  glEnd();

  glBegin(GL_POINTS);
  glColor3f(1.0f, 1.0f, 1.0f);

  for (Point3 point : clicked_points) {
    glVertex3f(point.x, point.y, point.z);
  }

  glEnd();

  glutSwapBuffers();
}

void Initialize() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.5f, 200.0f);

  camera.Set(Point3(look_x, look_y, look_z));
}

void RegisterMouseEvent(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    float dx = x * 10.0f / SCREEN_WIDTH - 10.0f / 2.0f;
    float dy = (SCREEN_HEIGHT - y) * 10.0f / SCREEN_HEIGHT - 10.0f / 2.0f;

    clicked_points.push_back(Point3(dx, dy));

    glutPostRedisplay();
  }

  if (button == GLUT_MIDDLE_BUTTON) {
    if (state == GLUT_DOWN) {
      x_origin = x;
      y_origin = y;
    } else {
      theta += delta_theta;
      phi += delta_phi;

      x_origin = 0;
      y_origin = 0;
    }
  }
}

void RegisterMouseMotionEvent(int x, int y) {
  delta_theta = (x - x_origin) * 0.01f;
  delta_phi = (y - y_origin) * 0.01f;

  look_x = 10.0f * cos(phi + delta_phi) * sin(theta + delta_theta);
  look_y = 10.0f * sin(phi + delta_phi) * sin(theta + delta_theta);
  look_z = 10.0f * cos(theta + delta_theta);

  glutPostRedisplay();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow("Homework 3");

  glutDisplayFunc(Display);
  glutMotionFunc(RegisterMouseMotionEvent);
  glutMouseFunc(RegisterMouseEvent);

  Initialize();

  glutMainLoop();

  return 0;
}
