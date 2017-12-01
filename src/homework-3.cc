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

  glColor3f(1.0f, 1.0f, 1.0f);

  if (spin) {
    Spin();
  } else {
    glBegin(GL_POINTS);

    for (Point3 point : clicked_points) {
      glVertex3f(point.x, point.y, point.z);
    }

    glEnd();
  }

  glutSwapBuffers();
}

void Initialize() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.5f, 200.0f);

  camera.Set(Point3(look_x, look_y, look_z));
}

void RegisterMouseEvent(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !spin) {
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
  } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && !spin) {
    spin = true;
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

void Spin(int segments) {
  float previous_theta = 0.0f;

  for (int i = 0; i <= segments; i++) {
    float theta = 0 < i ? (360.0f / segments) * i : 0.0f;
    theta *= (M_PI / 180.0f);

    if (clicked_points.size() > 1) {
      glBegin(GL_LINE_STRIP);

      for (Point3 point : clicked_points) {
        float x = (point.x * cos(theta)) + (point.z * sin(theta));
        float z = (point.z * cos(theta)) - (point.x * sin(theta));

        glVertex3f(x, point.y, z);
      }

      glEnd();

      if (previous_theta != theta) {
        glBegin(GL_LINES);

        for (Point3 point : clicked_points) {
          float x = (point.x * cos(theta)) + (point.z * sin(theta));
          float z = (point.z * cos(theta)) - (point.x * sin(theta));

          float dx = (point.x * cos(previous_theta)) +
              (point.z * sin(previous_theta));
          float dz = (point.z * cos(previous_theta)) -
              (point.x * sin(previous_theta));

          glVertex3f(x, point.y, z);
          glVertex3f(dx, point.y, dz);
        }

        glEnd();
      }
    }

    previous_theta = theta;
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
