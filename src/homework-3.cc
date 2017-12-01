#include "homework-3.h"

#include <math.h>

#include "vector3.h"

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);

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

  glEnable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[material]);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffusion[material]);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular[material]);
  glMaterialf(GL_FRONT, GL_SHININESS, shine[material] * 128.0f);

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
  float light_position[] = {10.0f, 0.0f, 0.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  light_position[0] = -10.0f;
  light_position[1] = 0.0f;
  light_position[2] = -10.0f;
  SetLight(GL_LIGHT1, light_position);

  light_position[0] = 10.0f;
  light_position[1] = 0.0f;
  light_position[2] = 10.0f;
  SetLight(GL_LIGHT2, light_position);

  light_position[0] = 0.0f;
  light_position[1] = -10.0f;
  light_position[2] = 0.0f;
  SetLight(GL_LIGHT3, light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);

  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.5f, 200.0f);

  camera.Set(Point3(look_x, look_y, look_z));
}

void RegisterKeyboardEvent(unsigned char key, int x, int y) {
  switch (key) {
    case 'c': {
      clicked_points.clear();

      look_x = 0.0f;
      look_y = 0.0f;
      look_z = 10.0f;

      spin = false;

      camera.Set(Point3(look_x, look_y, look_z));

      glutPostRedisplay();

      break;
    }
    case 'g': {
      material = material == 0 ? 1 : 0;
      glutPostRedisplay();
      break;
    }
    default: {
      break;
    }
  }
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

void SetLight(int light_source, float position[]) {
  float light_ambient[] = {0.2, 0.2, 0.2, 1.0};
  float light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  float light_specular[] = {1.0, 1.0, 1.0, 1.0};

  glLightfv(light_source, GL_AMBIENT, light_ambient);
  glLightfv(light_source, GL_DIFFUSE, light_diffuse);
  glLightfv(light_source, GL_SPECULAR, light_specular);

  glLightfv(light_source, GL_POSITION, position);
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
  glutKeyboardFunc(RegisterKeyboardEvent);
  glutMotionFunc(RegisterMouseMotionEvent);
  glutMouseFunc(RegisterMouseEvent);

  Initialize();

  glutMainLoop();

  return 0;
}
