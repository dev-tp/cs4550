#include "homework-3.h"

#include <math.h>

#include "vector3.h"

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
  } else if (button == GLUT_MIDDLE_BUTTON) {
    if (state == GLUT_DOWN) {
      register_motion = true;

      x_origin = x;
      y_origin = y;
    } else {
      register_motion = false;

      theta += delta_theta;
      phi += delta_phi;

      x_origin = 0;
      y_origin = 0;
    }

    return;
  } else if (button == GLUT_SCROLL_DOWN && state == GLUT_DOWN) {
    rho = camera.GetDistanceFromOrigin();

    if (rho > 1) {
      camera.Slide(0.0f, 0.0f, -1.0f);
    }

  } else if (button == GLUT_SCROLL_UP && state == GLUT_DOWN) {
    camera.Slide(0.0f, 0.0f, 1.0f);
    rho = camera.GetDistanceFromOrigin();
  }

  glutPostRedisplay();
}

void RegisterMouseMotionEvent(int x, int y) {
  if (register_motion) {
    delta_theta = (x - x_origin) * 0.01f;
    delta_phi = (y - y_origin) * 0.01f;

    look_x = rho * cos(phi + delta_phi) * sin(theta + delta_theta);
    look_y = rho * sin(phi + delta_phi) * sin(theta + delta_theta);
    look_z = rho * cos(theta + delta_theta);

    camera.Set(Point3(look_x, look_y, look_z));

    glutPostRedisplay();
  }
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
