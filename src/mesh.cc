#include "mesh.h"

#include <algorithm>
#include <vector>

#include <GL/glut.h>

Mesh::Mesh() {
  faces = nullptr;
  normal_vectors = nullptr;
  points = nullptr;
}

Mesh::~Mesh() {
  if (num_of_vertices != 0) {
    delete[] faces;
    delete[] normal_vectors;
    delete[] points;
  }
}

void Mesh::CreatePrism(int n, Point3* points, float length) {
  InitializePrism(n);

  // create the vertex list
  std::vector<Point3> vertices;

  for (int i = 0; i < n; i++) {
    Point3 vertex(points[i].x, points[i].y, points[i].z);
    vertices.push_back(vertex);
  }

  for (int i = 0; i < n; i++) {
    Point3 vertex(points[i].x, points[i].y, length);
    vertices.push_back(vertex);
  }

  // create side faces
  int vertex_count = vertices.size();

  for (int i = 0; i < num_of_faces; i++) {
    faces[i].num_of_vertices = vertex_count;
    faces[i].indices = new Index[vertex_count];

    for (int j = 0; j < n; j++) {
      int next = (j + 1) % n;

      faces[i].indices[j].vertex_index = j;
      faces[i].indices[j + n].vertex_index = j + n;
      faces[i].indices[next].vertex_index = next;
      faces[i].indices[next + n].vertex_index = next + n;
    }
  }

  // create the base and cap faces
  std::copy(vertices.begin(), vertices.end(), this->points);

  // when all is done, ready_to_draw = 1;
  ready_to_draw = 1;
}

// Use OpenGL to draw this mesh in solid object mode
void Mesh::DrawSolid() {
  if (ready_to_draw) {
    for (int f = 0; f < num_of_faces; f++) {  // draw each face
      float color = (float) f / 10;

      glColor3f(color, color, color);
      glBegin(GL_POLYGON);

      for (int v = 0; v < faces[f].num_of_vertices; v++) {
        // int in = faces[f].indices[v].normal_index;
        int iv = faces[f].indices[v].vertex_index;

        // glNormal3f(normal_vectors[in].x, normal_vectors[in].y,
        //            normal_vectors[in].z);
        glVertex3f(points[iv].x, points[iv].y, points[iv].z);
      }

      glEnd();
    }
  }
}

// Use OpenGL to draw this mesh in wireframe mode
void Mesh::DrawWireframe() {
  if (ready_to_draw) {
    for (int f = 0; f < num_of_faces; f++) {
      glColor3f(0.0f, 0.0f, 0.0f);
      glBegin(GL_LINE_LOOP);

      for (int v = 0; v < faces[f].num_of_vertices; v++) {
        int iv = faces[f].indices[v].vertex_index;
        glVertex3f(points[iv].x, points[iv].y, points[iv].z);
      }

      glEnd();
    }
  }
}

void Mesh::InitializePrism(int size) {
  normal_vector_count = size + 2;
  num_of_faces = size + 2;
  num_of_vertices = size * 2;

  faces = new Face[num_of_faces];
  normal_vectors = new Vector3[normal_vector_count];
  points = new Point3[num_of_vertices];
}
