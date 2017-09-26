#include "lab-six.h"

void DrawOctahedron() {
  DrawTriangle(4, 0, 1);
  DrawTriangle(4, 1, 2);
  DrawTriangle(4, 2, 3);
  DrawTriangle(4, 3, 0);
  DrawTriangle(5, 0, 1);
  DrawTriangle(5, 1, 2);
  DrawTriangle(5, 2, 3);
  DrawTriangle(5, 3, 0);
}

void DrawTriangle(int a, int b, int c) {
  glBegin(GL_LINE_LOOP);

  glVertex3fv(octahedron[a].vertices);
  glVertex3fv(octahedron[b].vertices);
  glVertex3fv(octahedron[c].vertices);

  glEnd();
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(10.0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  // Transformations go here

  DrawOctahedron();

  glFlush();
}

void GenerateOctahedron() {
  float vertices[][3] = {
    {-1.0f,  0.0f,  1.0f},
    { 1.0f,  0.0f,  1.0f},
    { 1.0f,  0.0f, -1.0f},
    {-1.0f,  0.0f, -1.0f},
    { 0.0f,  1.5f,  0.0f},
    { 0.0f, -1.5f,  0.0f}
  };

  for (int i = 0; i < 8; i++) {
    octahedron[i].vertices[0] = vertices[i][0];
    octahedron[i].vertices[1] = vertices[i][1];
    octahedron[i].vertices[2] = vertices[i][2];
  }
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow("Lab 6");

  glutDisplayFunc(Display);

  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-10.0, 10.0, -10.0, 10.0, 10.0, 40.0);
  GenerateOctahedron();

  glutMainLoop();

  return 0;
}
