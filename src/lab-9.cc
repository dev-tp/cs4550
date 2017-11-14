#include "lab-9.h"

#include <unistd.h>

#include <GL/glut.h>

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);

  glBegin(GL_LINES);

  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(5.0f, 0.0f, 0.0f);

  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 5.0f, 0.0f);

  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 5.0f);

  glEnd();

  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glPushMatrix();

  float ambient[] = {0.24725f, 0.1995f, 0.0745f, 1.0f};
  float diffusion[] = {0.75164f, 0.60648f, 0.22648f, 1.0f};
  float specular[] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
  float shine = 0.4f * 128.0f;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffusion);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shine);

  glTranslatef(x_position, 0.0f, z_position);
  glRotatef(rotation_angle, 0.0f, 1.0f, 0.0f);
  glutSolidTeapot(1.0);
  glPopMatrix();

  glPushMatrix();

  ambient[0] = 0.19225f;
  ambient[1] = 0.19225f;
  ambient[2] = 0.19225f;
  diffusion[0] = 0.50754f;
  diffusion[1] = 0.50754f;
  diffusion[2] = 0.50754f;
  specular[0] = 0.508273f;
  specular[1] = 0.508273f;
  specular[2] = 0.508273f;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffusion);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shine);

  glTranslatef(x_position, 0.0f, z_position - 3.0f);
  glRotatef(rotation_angle, 0.0f, 1.0f, 0.0f);
  glutSolidTeapot(1.0);
  glPopMatrix();

  glutSwapBuffers();
}

void Idle() {
  if (move_light) {
    light_position[0] += 1.0f;
    light_position[1] += 1.0f;
    usleep(100000);
    glutPostRedisplay();
  }
}

void Initialize() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glColor3f(1.0f, 1.0f, 1.0f);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.5f, 200.0f);

  camera.Set(Point3(4.0f, 4.0f, 4.0f), Point3(0.0f, 0.0f, 0.0f),
             Vector3(0.0f, 1.0f, 0.0f));
}

void RegisterKey(unsigned char key, int x, int y) {
  if (key == 'a') {
    move_light = !move_light;
  } else if (key == 'e') {
    rotation_angle += 1.0;
  } else if (key == 'E') {
    rotation_angle -= 1.0;
  } else if (key == 'r') {
    camera.Roll(1.0);
  } else if (key == 'R') {
    camera.Roll(-1.0);
  } else if (key == 'p') {
    camera.Pitch(1.0);
  } else if (key == 'P') {
    camera.Pitch(-1.0);
  } else if (key == 'w') {
    x_position += 0.1;
    z_position += 0.1;
  } else if (key == 'W') {
    x_position -= 0.1;
    z_position -= 0.1;
  } else if (key == 'y') {
    camera.Yaw(1.0);
  } else if (key == 'Y') {
    camera.Yaw(-1.0);
  }

  glutPostRedisplay();
}

void RegisterSpecialKey(int key, int x, int y) {
  if (key == GLUT_KEY_LEFT)
    camera.Slide(-0.2f, 0.0f, 0.0f);
  else if (key == GLUT_KEY_RIGHT)
    camera.Slide(0.2f, 0.0f, 0.0f);
  else if (key == GLUT_KEY_UP)
    camera.Slide(0.0f, 0.2f, 0.0f);
  else if (key == GLUT_KEY_DOWN)
    camera.Slide(0.0f, -0.2f, 0.0f);
  else if (key == GLUT_KEY_PAGE_UP)
    camera.Slide(0.0f, 0.0f, 1.0f);
  else if (key == GLUT_KEY_PAGE_DOWN)
    camera.Slide(0.0f, 0.0f, -1.0f);

  glutPostRedisplay();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow("Lab 9");

  glutDisplayFunc(Display);
  glutIdleFunc(Idle);
  glutKeyboardFunc(RegisterKey);
  glutSpecialFunc(RegisterSpecialKey);

  Initialize();

  glutMainLoop();

  return 0;
}
