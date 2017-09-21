#include "homework-one.h"

#include <time.h>
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

  for (Ball ball : balls)
    ball.Draw();

  glFlush();
}

void GetKey(unsigned char key, int x, int y) {
  if (key == 'a') {
    if (balls.size() < 5) {
      static unsigned int milliseconds = time(nullptr);

      srand(milliseconds++);

      float x = rand() % SCREEN_WIDTH;
      float y = SCREEN_HEIGHT - (rand() % SCREEN_HEIGHT);

      float dx = (rand() % 10) - 5;
      float dy = (rand() % 10) - 5;

      float red = (float) rand() / RAND_MAX;
      float green = (float) rand() / RAND_MAX;
      float blue = (float) rand() / RAND_MAX;

      Ball ball(x, y);
      ball.SetColor(red, green, blue);
      ball.dx = dx;
      ball.dy = dy;
      balls.push_back(ball);
    }
  } else if (key == 'r') {
    if (balls.size() > 1)
      balls.pop_back();
  }
}

void Idle() {
  usleep(10000);

  for (Ball& ball : balls) {
    ball.x += ball.dx;
    ball.y += ball.dy;
  }

  glutPostRedisplay();
}

void Setup() {
  Ball blue_ball(10.0f, 10.0f);
  Ball red_ball(100.0f, 100.0f);

  blue_ball.SetColor(0.0f, 0.0f, 1.0f);
  red_ball.SetColor(1.0f, 0.0f, 0.0f);

  balls.push_back(blue_ball);
  balls.push_back(red_ball);

  glutDisplayFunc(Display);
  glutIdleFunc(Idle);
  glutKeyboardFunc(GetKey);

  DefaultSetup();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  CreateWindow("Homework 1", Setup);

  return 0;
}
