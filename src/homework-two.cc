#include "homework-two.h"

#include <math.h>
#include <unistd.h>

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

  if (display_coordinate_system) {
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
  }

  glColor3f(0.5f, 0.5f, 0.5f);

  // TODO glTranslate to move robotic arm on direction it is pointing

  glPushMatrix();
  glRotatef(270.0f, 1.0f, 0.0f, 0.0f);

  // Base
  if (draw_solid) {
    glPushMatrix();

    GLUquadric* quadric = gluNewQuadric();
    // gluQuadricDrawStyle(quadric, GL_LINE);

    gluCylinder(quadric, 0.8, 0.8, 0.5, 32, 16);
    glPopMatrix();

    gluDeleteQuadric(quadric);
  }

  float z_axis[] = {0.0f, 0.5f};

  for (float z : z_axis) {
    glBegin(draw_solid ? GL_POLYGON : GL_LINE_LOOP);

    for (float theta = 0.0f; theta < 1.0f; theta += 0.01f) {
      float x = 0.8f * cos(2 * M_PI * theta);
      float y = 0.8f * sin(2 * M_PI * theta);

      glVertex3f(x, y, z);
    }

    glEnd();
  }

  glTranslatef(0.0f, 0.0f, 0.5f);
  glRotatef(rotation_angle, 0.0f, 0.0f, 1.0f);

  // Shoulder joint
  glPushMatrix();
  glRotatef(upper_arm, 1.0f, 0.0f, 0.0f);
  DRAW_SPHERE(0.5);
  glPopMatrix();

  // Upper arm
  glPushMatrix();
  glTranslatef(-0.2f, 0.0f, 0.0f);
  glRotatef(upper_arm, 1.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 1.0f);
  glScalef(0.2f, 0.2f, 2.0f);
  DRAW_CUBE();
  glPopMatrix();

  // Upper arm
  glPushMatrix();
  glTranslatef(0.2f, 0.0f, 0.0f);
  glRotatef(upper_arm, 1.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 1.0f);
  glScalef(0.2f, 0.2f, 2.0f);
  DRAW_CUBE();
  glPopMatrix();

  // Arm joint
  glPushMatrix();
  glRotatef(upper_arm, 1.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 2.0f);
  DRAW_SPHERE(0.4);
  glPopMatrix();

  // Lower arm
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 0.0f);
  glRotatef(upper_arm, 1.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 2.8f);
  glTranslatef(0.0f, 0.0f, -0.8f);
  glRotatef(lower_arm, 1.0f, 0.0f, 0.0f);

  // Hand joint
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 1.8f);
  glRotatef(wrist, 1.0f, 0.0f, 0.0f);

  glPushMatrix();
  glTranslatef(-0.2f, 0.0f, 0.2f);
  glRotatef(10.0f, 0.0f, -1.0f, 0.0f);
  RenderFinger(0.0f, 1.0f, 0.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.1f, 0.2f, 0.2f);
  glRotatef(10.0f, 0.0f, -1.0f, -1.0f);
  RenderFinger(0.0f, 1.0f, 0.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.1f, 0.2f, 0.2f);
  glRotatef(10.0f, 0.0f, 1.0f, 1.0f);
  RenderFinger(0.0f, -1.0f, 0.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.2f, 0.0f, 0.2f);
  glRotatef(10.0f, 0.0f, 1.0f, 0.0f);
  RenderFinger(0.0f, -1.0f, 0.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0f, -0.2f, 0.2f);
  glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
  RenderFinger(-1.0f, 0.0f, 0.0f);
  glPopMatrix();

  DRAW_SPHERE(0.3);
  glPopMatrix();

  glTranslatef(0.0f, 0.0f, 1.0f);
  glScalef(0.2f, 0.2f, 2.0f);
  DRAW_CUBE();
  glPopMatrix();

  glPopMatrix();

  glutSwapBuffers();
}

void RenderFinger(float x, float y, float z) {
  glPushMatrix();
  glScalef(0.1f, 0.1f, 0.4f);
  DRAW_CUBE();
  glPopMatrix();

  glPushMatrix();
  glScalef(0.1f, 0.1f, 0.3f);
  glRotatef(finger, x, y, z);
  glTranslatef(0.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 1.0f);
  DRAW_CUBE();
  glPopMatrix();
}

void Idle() {
  usleep(1000000);
  rotation_angle += 36.0f;
  glutPostRedisplay();
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
  if (key == 'c')
    display_coordinate_system = !display_coordinate_system;
  else if (key == 'i')
    upper_arm -= 10.0f;
  else if (key == 'I')
    upper_arm += 10.0f;
  else if (key == 'j')
    lower_arm += 10.0f;
  else if (key == 'J')
    lower_arm -= 10.0f;
  else if (key == 'm')
    finger += 10.0f;
  else if (key == 'M')
    finger -= 10.0f;
  else if (key == 'n')
    wrist += 10.0f;
  else if (key == 'N')
    wrist -= 10.0f;
  else if (key == 'q' || key == 'Q')
    exit(0);
  else if (key == 'r')
    rotation_angle += 10.0f;
  else if (key == 'R')
    rotation_angle -= 10.0f;
  else if (key == 'u')
    draw_solid = !draw_solid;

  glutPostRedisplay();
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
  // glutIdleFunc(Idle);
  glutKeyboardFunc(RegisterKey);
  glutSpecialFunc(RegisterSpecialKey);

  glutMainLoop();

  return 0;
}
