#ifndef CS4550_VECTOR3_H_
#define CS4550_VECTOR3_H_

#include <math.h>

class Vector3 {
public:
  float x;
  float y;
  float z;

  Vector3(float x = 0, float y = 0, float z = 0) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Vector3(Vector3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  Vector3 CrossProduct(Vector3 b) {
    Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    return c;
  }

  float DotProduct(Vector3 b) {
    return x * b.x + y * b.y + z * b.z;
  }

  void Flip() {  // Reverse this vector
    x = -x;
    y = -y;
    z = -z;
  }

  void Normalize() {  // Adjust this vector to unit length
    double squared_size = x * x + y * y + z * z;

    if (squared_size < 0.0000001) {
      // cerr << "\nNormalize() sees vector (0,0,0)!";
      return;
    }

    float scale_factor = 1.0f / (float) sqrt(squared_size);

    x *= scale_factor;
    y *= scale_factor;
    z *= scale_factor;
  }

  void Set(float dx, float dy, float dz) {
    x = dx;
    y = dy;
    z = dz;
  }

  void Set(Vector3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  void SetDiff(Point3& a, Point3& b) {
    x = a.x - b.x;
    y = a.y - b.y;
    z = a.z - b.z;
  }
};

#endif  // CS4550_VECTOR3_H_
