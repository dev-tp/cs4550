#include "opengl-window.h"

void CreateWindow(std::string title, void (*setup)()) {
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  glutCreateWindow(title.c_str());

  setup();

  glutMainLoop();
}
