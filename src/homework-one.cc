#include "homework-one.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void Ball::CheckForCollision(int position) {
  if (x >= SCREEN_WIDTH) {
    dx = -dx;
  } else if (x <= 0.0f) {
    dx = abs(dx);
  } else if (y >= SCREEN_HEIGHT) {
    dy = -dy;
  } else if (y <= 0.0f) {
    dy = abs(dy);
  } else {
    for (int i = position + 1; i < (signed int) balls.size(); i++) {
      float distance = sqrtf(powf(balls[i].x - x, 2.0f) +
          powf(balls[i].y - y, 2.0f));

      if (distance < balls[i].radius + radius) {
        float norm_x = (balls[i].x - x) / distance;
        float norm_y = (balls[i].y - y) / distance;

        float combined_mass = mass + balls[i].mass;
        float k_value = balls[i].dx * norm_x + balls[i].dy * norm_y;

        k_value = 2 * ((dx * norm_x + dy * norm_y) - k_value) / combined_mass;

        dx = dx - k_value * balls[i].mass * norm_x;
        dy = dy - k_value * balls[i].mass * norm_y;

        balls[i].dx = balls[i].dx + k_value * mass * norm_x;
        balls[i].dy = balls[i].dy + k_value * mass * norm_y;
      }
    }
  }
}

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
  } else if (key == 'n') {
    InitialState();
  } else if (key == 'q') {
    glutDestroyWindow(window_id);
    exit(0);
  }
}

void Idle() {
  usleep(10000);

  for (int i = 0; i < (signed int) balls.size(); i++) {
    balls[i].x += balls[i].dx;
    balls[i].y += balls[i].dy;
    balls[i].CheckForCollision(i);
  }

  glutPostRedisplay();
}

void InitialState() {
  balls.clear();

  Ball blue_ball(10.0f, 10.0f);
  Ball red_ball(100.0f, 100.0f);

  blue_ball.SetColor(0.0f, 0.0f, 1.0f);
  red_ball.SetColor(1.0f, 0.0f, 0.0f);

  balls.push_back(blue_ball);
  balls.push_back(red_ball);
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  window_id = glutCreateWindow("Homework 1");

  InitialState();

  glutDisplayFunc(Display);
  glutIdleFunc(Idle);
  glutKeyboardFunc(GetKey);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);

  glutMainLoop();

  return 0;
}
