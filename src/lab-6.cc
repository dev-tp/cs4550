#include "lab-6.h"

#include <unistd.h>

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (!triangular_prism.ready_to_draw) {
    gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0.0, 1.0, 0.0);

    DrawAxes();

    // Draw triangle based on the input
    if (num_of_points == 3) {
      glColor3f(0.5f, 0.5f, 0.5f);
      glBegin(GL_POLYGON);

      for (int i = 0; i < num_of_points; i++)
        glVertex3f(base[i].x, base[i].y, base[i].z);

      glEnd();
    }
  } else {
    gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0.0, 1.0, 0.0);

    DrawAxes();

    if (display_mode)
      triangular_prism.DrawWireframe();
    else
      triangular_prism.DrawSolid();

    usleep(1000);
  }

  glFlush();
}

void DrawAxes() {
  glBegin(GL_LINES);

  // x-axis
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-100, 0, 0);
  glVertex3f(100, 0, 0);

  // y-axis
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0, -100, 0);
  glVertex3f(0, 100, 0);

  // z-axis
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0, 0, -100);
  glVertex3f(0, 0, 100);

  glEnd();
}

void Idle() {
  if (animate && frame < 50.0f) {
    eye_x += 0.1;
    eye_y += 0.1;
    frame += 0.1f;

    glutPostRedisplay();
  }
}

void RegisterKey(unsigned char key, int x, int y) {
  if (key == 'e' && !triangular_prism.ready_to_draw) {
    triangular_prism.CreatePrism(3, base, 10);
    animate = 1;
  } else if (key == 'w') {
    display_mode = (display_mode + 1) % 2;
  }

  glutPostRedisplay();
}

void RegisterMouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && num_of_points < 3) {
    int ry = SCREEN_HEIGHT - y;

    float dx = x * WORLD_WIDTH / (float) SCREEN_WIDTH - WORLD_WIDTH / 2;
    float dy = ry * WORLD_HEIGHT / (float) SCREEN_HEIGHT - WORLD_HEIGHT / 2;

    base[num_of_points].Set(dx, dy, 0.0f);

    num_of_points++;
  }

  glutPostRedisplay();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow("Lab 6");

  // Initialize
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WORLD_WIDTH / 2, WORLD_WIDTH / 2, -WORLD_HEIGHT / 2,
          WORLD_HEIGHT / 2, 0.1, 120.0);

  glutDisplayFunc(Display);
  glutKeyboardFunc(RegisterKey);
  glutMouseFunc(RegisterMouse);
  glutIdleFunc(Idle);

  glutMainLoop();

  return 0;
}
