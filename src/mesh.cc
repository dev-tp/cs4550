#include "mesh.h"

#include <GL/glut.h>

Mesh::~Mesh() {
  if (num_of_vertices != 0) {
    delete[] points;
    delete[] normal_vectors;
    delete[] faces;
  }
}

void Mesh::CreatePrism(int vertex_count, Point3* points, float length) {
  InitializePrism(vertex_count);

  // create the vertex list

  // create side faces

  // create the base and cap faces

  // when all is done, ready_to_draw = 1;
}

// Use OpenGL to draw this mesh in solid object mode
void Mesh::DrawSolid() {
  if (ready_to_draw) {
    for (int f = 0; f < num_of_faces; f++) {  // draw each face
      float color = (float) f / 10;

      glColor3f(color, color, color);
      glBegin(GL_POLYGON);

      for (int v = 0; v < faces[f].num_of_vertices; v++) {
        int in = faces[f].indices[v].normal_index;
        int iv =  faces[f].indices[v].vertex_index;

        glNormal3f(normal_vectors[in].x, normal_vectors[in].y,
                   normal_vectors[in].z);
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
        int iv =  faces[f].indices[v].vertex_index;
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
