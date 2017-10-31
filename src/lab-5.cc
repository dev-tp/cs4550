#include "lab-5.h"

#include <math.h>
#include <unistd.h>

#include <iostream>

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camera_x, camera_y, camera_z, view_x, view_y, view_z, 0.0, 1.0, 0.0);

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

  glBegin(GL_LINE_LOOP);

  // Earth's orbital path
  for (float theta = 0.0f; theta < 1.0f; theta += 0.01f) {
    float x = 2.0f * cos(2 * M_PI * theta);
    float z = 2.0f * sin(2 * M_PI * theta);

    glVertex3f(x, 0.0f, z);
  }

  glEnd();

  // The sun
  glPushMatrix();
  glColor3f(1.0f, 0.8413f, 0.0f);
  glRotatef(rotation_angle, 1.0f, 0.0f, 0.0f);
  glutSolidSphere(0.5, 20, 16);
  glPopMatrix();

  // Planet Earth
  glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glRotatef(rotation_angle, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 2.0f);
  glutSolidSphere(0.2, 20, 8);
  glPopMatrix();

  // Earth's moon
  glColor3f(0.5f, 0.5f, 0.5f);
  glPushMatrix();
  glRotatef(rotation_angle, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 2.0f);
  glRotatef(rotation_angle * 2.5f, 0.0f, -1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 0.3f);
  glutSolidSphere(0.05, 10, 4);
  glPopMatrix();

  // Planet Mars
  glColor3f(1.0f, 0.0f, 0.0f);
  glPushMatrix();
  glRotatef(rotation_angle / 2.0f, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 3.0f);
  glutSolidSphere(0.15, 20, 8);
  glPopMatrix();

  glutSwapBuffers();
}

void Idle() {
  if (!camera_rotating) {
    usleep(100000);
    rotation_angle += 10.0f;
  } else {
    static double theta = 0.0;
    theta += 0.01f;

    camera_x = 65.0 * sin(theta);
    camera_z = 20.0 * cos(theta);
  }

  glutPostRedisplay();
}

void Initialize() {
  int color_choice = 0;
  int shading_choice = 0;

  std::cout << "Mono or RGB (0/1): ";
  std::cin >> color_choice;

  std::cout << "With/out Shading (0/1): ";
  std::cin >> shading_choice;

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_SMOOTH);

  float light_intensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
  float position[] = {2.0f, 6.0f, 3.0f, 0.0f};

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  if (shading_choice == 0) {
    float ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    float diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  } else {
    float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  }

  if (color_choice == 1) {
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  }

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3.5, 3.5, -3.5, 3.5, 0.1, 100.0);
}

void RegisterKey(unsigned char key, int x, int y) {
  static int step;

  if (key == 'r') {
    camera_rotating = !camera_rotating;
  } else if (key == 'v') {
    if (step % 3 == 0) {
      camera_x = 25.0;
      camera_y = 25.0;
      camera_z = 25.0;
    } else if (step % 3 == 1) {
      camera_x = 25.0;
      camera_y = 0.0;
      camera_z = 0.0;
    } else {
      camera_x = 0.0;
      camera_y = 25.0;
      camera_z = 25.0;
    }

    step++;

    glutPostRedisplay();
  }
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow("Lab 5");

  Initialize();

  glutDisplayFunc(Display);
  glutIdleFunc(Idle);
  glutKeyboardFunc(RegisterKey);

  glutMainLoop();

  return 0;
}
