#ifndef CS4550_FACE_H_
#define CS4550_FACE_H_

struct Index {
  int vertex_index;
  int normal_index;
};

struct Face {
  Index* indices;
  int num_of_vertices;

  Face() { indices = nullptr; }
  ~Face() { delete[] indices; }
};

#endif  // CS4550_FACE_H_
