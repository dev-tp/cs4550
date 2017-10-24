#ifndef CS4550_MESH_H_
#define CS4550_MESH_H_

#include "face.h"
#include "point3.h"
#include "vector3.h"

class Mesh {
  int normal_vector_count;
  int num_of_faces;
  int num_of_vertices;

  Face* faces;
  Point3* points;  // array of 3D vertices
  Vector3* normal_vectors;

public:
  int ready_to_draw;

  Mesh() { }
  ~Mesh();

  void CreatePrism(int vertex_count, Point3* point, float length);
  void DrawSolid();
  void DrawWireframe();
  void InitializePrism(int size);
};

#endif  // CS4550_MESH_H_
