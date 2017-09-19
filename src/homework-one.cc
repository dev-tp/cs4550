#include "homework-one.h"

#include <unistd.h>

void Ball::Draw() {
  glBegin(GL_POLYGON);

  glColor3f(red, green, blue);

  for (float theta = 0.0f; theta < 1.0f; theta += 0.01f) {
    float h = x + radius * cos(CIRCUMFERENCE * theta);
    float k = y + radius * sin(CIRCUMFERENCE * theta);

    glVertex2d(h, k);
  }

  glEnd();
}

void Ball::SetColor(float red, float green, float blue) {
  this->red = red;
  this->green = green;
  this->blue = blue;
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);

  blue_ball.Draw();
  red_ball.Draw();

  glFlush();
}

void Idle() {
  usleep(10000);

  blue_ball.x += blue_ball.dx;
  blue_ball.y += blue_ball.dy;

  red_ball.x += red_ball.dx;
  red_ball.y += red_ball.dy;

  glutPostRedisplay();
}

void Setup() {
  blue_ball.SetColor(0.0f, 0.0f, 1.0f);
  red_ball.SetColor(1.0f, 0.0f, 0.0f);

  glutDisplayFunc(Display);
  glutIdleFunc(Idle);

  DefaultSetup();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  CreateWindow("Homework 1", Setup);

  return 0;
}
