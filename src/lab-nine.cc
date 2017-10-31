#include "lab-nine.h"

#include <GL/glut.h>

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);

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

  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(x_position, 0.0f, z_position);
  glRotatef(rotation_angle, 0.0f, 1.0f, 0.0f);
  glutWireTeapot(1.0);
  glPopMatrix();

  glutSwapBuffers();
}

void Initialize() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glColor3f(1.0f, 1.0f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.5f, 200.0f);

  camera.Set(Point3(4.0f, 4.0f, 4.0f), Point3(0.0f, 0.0f, 0.0f),
             Vector3(0.0f, 1.0f, 0.0f));
}

void RegisterKey(unsigned char key, int x, int y) {
  if (key == 'e') {
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
  glutKeyboardFunc(RegisterKey);
  glutSpecialFunc(RegisterSpecialKey);

  Initialize();

  glutMainLoop();

  return 0;
}
