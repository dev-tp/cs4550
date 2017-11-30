#include "camera.h"

#include <math.h>

#include <GL/glut.h>

void Camera::ApplyTransformation(float angle, Vector3& a, Vector3& b) {
  float cs = (float) cos(M_PI / 180.0f * angle);
  float sn = (float) sin(M_PI / 180.0f * angle);

  Vector3 t(a);

  a.Set(cs * t.x + sn * b.x, cs * t.y + sn * b.y, cs * t.z + sn * b.z);
  b.Set(-sn * t.x + cs * b.x, -sn * t.y + cs * b.y, -sn * t.z + cs * b.z);

  SetModelViewMatrix();
}

// Pitch the camera through angle degrees
void Camera::Pitch(float angle) {
  ApplyTransformation(angle, n, v);
}

// Roll the camera through angle degrees
void Camera::Roll(float angle) {
  ApplyTransformation(angle, u, v);
}

// Create a modelview matrix and send it to OpenGL
void Camera::Set(Point3 eye, Point3 look, Vector3 up) {
  this->eye.Set(eye);

  n.Set(this->eye.x - look.x, this->eye.y - look.y, this->eye.z - look.z);

  u.Set(up.CrossProduct(n));

  n.Normalize();
  u.Normalize();

  v.Set(n.CrossProduct(u));

  SetModelViewMatrix();
}

// Load modelview matrix with existing camera values
void Camera::SetModelViewMatrix() {
  float m[16];

  Vector3 e(eye.x, eye.y, eye.z);

  m[0] = u.x;
  m[4] = u.y;
  m[8] = u.z;
  m[12] = -e.DotProduct(u);

  m[1] = v.x;
  m[5] = v.y;
  m[9] = v.z;
  m[13] = -e.DotProduct(v);

  m[2] = n.x;
  m[6] = n.y;
  m[10] = n.z;
  m[14] = -e.DotProduct(n);

  m[3] = 0.0f;
  m[7] = 0.0f;
  m[11] = 0.0f;
  m[15] = 1.0f;

  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(m);  // Load OpenGL's modelview matrix
}

void Camera::Slide(float du, float dv, float dn) {
  eye.x += du * u.x + dv * v.x + dn * n.x;
  eye.y += du * u.y + dv * v.y + dn * n.y;
  eye.z += du * u.z + dv * v.z + dn * n.z;

  SetModelViewMatrix();
}

// Yaw the camera through angle degrees
void Camera::Yaw(float angle) {
  ApplyTransformation(angle, u, n);
}

float Camera::GetDistanceFromOrigin() {
  return sqrt(powf(eye.x, 2.0f) + powf(eye.y, 2.0f) + powf(eye.z, 2.0f));
}

void SetShape(float angle, float asp, float near_d, float far_d) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angle, asp, near_d, far_d);
}
