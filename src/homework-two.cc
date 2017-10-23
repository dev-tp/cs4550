#include "homework-two.h"

#include <math.h>

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(25.0, 25.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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

  glColor3f(0.8f, 0.8f, 0.8f);

  float depth = 80.0f;

  // Floor
  RenderWall(depth, 0.0f, depth, 0.0f, 0.0f, 0.0f);

  // Ceiling
  RenderWall(depth, 0.1f, depth, 0.0f, depth, 0.0f);

  // Walls
  RenderWall(depth, depth, 0.1f, 0.0f, depth / 2.0f, -depth / 2.0f);
  RenderWall(0.1f, depth, depth, -depth / 2.0f, depth / 2.0f, 0.0f);
  RenderWall(0.1f, depth, depth, depth / 2.0f, depth / 2.0f, 0.0f);
  RenderWall(depth, depth, 0.1f, 0.0f, depth / 2.0f, depth / 2.0f);

  glColor3f(0.5f, 0.5f, 0.5f);

  glTranslatef(position_x, 0.0f, position_z);

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
  if (key == 27) {
    Reset();
  } else if (key == 'c') {
    display_coordinate_system = !display_coordinate_system;
  } else if (key == 'i' && active) {
    upper_arm += upper_arm < 80.0f ? 10.0f : 0.0f;
  } else if (key == 'I' && active) {
    upper_arm -= upper_arm > -80.0f ? 10.0f : 0.0f;
  } else if (key == 'j' && active) {
    lower_arm -= lower_arm > -160.0f ? 10.0f : 0.0f;
  } else if (key == 'J' && active) {
    lower_arm += lower_arm < 160.0f ? 10.0f : 0.0f;
  } else if (key == 'm' && active) {
    finger += finger < 60.0f ? 10.0f : 0.0f;
  } else if (key == 'M' && active) {
    finger -= finger > -60.0f ? 10.0f : 0.0f;
  } else if (key == 'n' && active) {
    wrist += wrist < 120.0f ? 10.0f : 0.0f;
  } else if (key == 'N' && active) {
    wrist -= wrist > -90.0f ? 10.0f : 0.0f;
  } else if (key == 'o') {
    active = !active;
  } else if (key == 'q' || key == 'Q') {
    glutDestroyWindow(window_id);
    exit(0);
  } else if (key == 'r' && active) {
    rotation_angle += 10.0f;
  } else if (key == 'R' && active) {
    rotation_angle -= 10.0f;
  } else if (key == 'u') {
    draw_solid = !draw_solid;
  }

  glutPostRedisplay();
}

void RegisterSpecialKey(int key, int x, int y) {
  if (key == GLUT_KEY_UP && active) {
    position_x += 0.1f * sin(M_PI / 180.0f * rotation_angle);
    position_z += 0.1f * cos(M_PI / 180.0f * rotation_angle);
  } else if (key == GLUT_KEY_DOWN && active) {
    position_x -= 0.1f * sin(M_PI / 180.0f * rotation_angle);
    position_z -= 0.1f * cos(M_PI / 180.0f * rotation_angle);
  }

  glutPostRedisplay();
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

void RenderWall(float x, float y, float z, float translate_x, float translate_y,
                float translate_z) {
  glPushMatrix();
  glTranslatef(translate_x, translate_y, translate_z);
  glScalef(x, y, z);
  DRAW_CUBE();
  glPopMatrix();
}

void Reset() {
  finger = 30.0f;
  lower_arm = 140.0f;
  position_x = 0.0f;
  position_z = 0.0f;
  rotation_angle = 0.0f;
  upper_arm = -60.0f;
  wrist = 10.0f;
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(POSITION_X, POSITION_Y);
  window_id = glutCreateWindow("Homework 2");

  Initialize();

  glutDisplayFunc(Display);
  glutKeyboardFunc(RegisterKey);
  glutSpecialFunc(RegisterSpecialKey);

  glutMainLoop();

  return 0;
}
