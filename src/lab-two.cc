#include <time.h>

#include <array>
#include <vector>

#include "opengl-window.h"

bool mouse_pressed;
int count = -1;
int mouse_state;
std::vector<std::array<int, 2>> points;

void Display() {
  if (mouse_state == 0 && mouse_pressed) {
    int i = count % 4;

    GLenum mode = i == 0 ? GL_POINTS : i == 1 ? GL_LINES : GL_POLYGON;

    glBegin(mode);

    for (std::array<int, 2> point : points)
      glVertex2i(point[0], SCREEN_HEIGHT - point[1]);

    glEnd();
  }

  mouse_pressed = false;

  glFlush();
}

void GetKey(unsigned char key, int x, int y) {
  if (key == 'c') {
    srand((unsigned) time(nullptr));

    float r = (float) rand() / RAND_MAX;
    float g = (float) rand() / RAND_MAX;
    float b = (float) rand() / RAND_MAX;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(r, g, b, 0.0f);
    glutPostRedisplay();
  }
}

void RegisterMouseEvents(int button, int state, int x, int y) {
  if (state == GLUT_DOWN) {
    mouse_pressed = true;

    if (button == GLUT_LEFT_BUTTON) {
      mouse_state = 0;

      std::array<int, 2> point = {x, y};
      points.push_back(point);

      count++;
    } else if (button == GLUT_RIGHT_BUTTON) {
      mouse_state = 1;
    }
  }

  glutPostRedisplay();
}

void Setup() {
  glutDisplayFunc(Display);
  glutKeyboardFunc(GetKey);
  glutMouseFunc(RegisterMouseEvents);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glPointSize(2.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  CreateWindow("Lab 2", Setup);

  return 0;
}
