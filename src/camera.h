#ifndef CS4550_CAMERA_H_
#define CS4550_CAMERA_H_

#include "point3.h"
#include "vector3.h"

class Camera {
  Point3 eye;
  Vector3 n;
  Vector3 u;
  Vector3 v;

  void ApplyTransformation(float angle, Vector3& a, Vector3& b);
  void SetModelViewMatrix();
public:
  Camera() { }
  ~Camera() { }

  void Pitch(float angle);
  void Roll(float angle);
  void Set(Point3 eye, Point3 look = Point3(),
           Vector3 up = Vector3(0.0f, 1.0f, 0.0f));
  void Slide(float du, float dv, float dn);
  void Yaw(float angle);
};

void SetShape(float angle, float asp, float near_d, float far_d);

#endif  // CS4550_CAMERA_H_
