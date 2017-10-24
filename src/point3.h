#ifndef CS4550_POINT3_H_
#define CS4550_POINT3_H_

class Point3 {
public:
  float x;
  float y;
  float z;

  Point3(float x = 0, float y = 0, float z = 0) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  void BuildQuadTuple(float v[]) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
  }

  void Set(float dx, float dy, float dz) {
    x = dx;
    y = dy;
    z = dz;
  }

  void Set(Point3& p) {
    x = p.x;
    y = p.y;
    z = p.z;
  }
};

#endif  // CS4550_POINT3_H_
