#ifndef POINT_H
#define POINT_H

#include <GL/gl.h>
#include <vector>
#include <glm/glm.hpp>

using namespace std;

class Sphere {
public:
    double x, y, z;
    double vel[3];
    double radius;
    double red, green, blue;
    double q;
    double alpha;
    void draw(double angle,int n);
    static int slices;
    static int stacks;
    static GLuint restart;
    static void buildArrays ( int n, glm::vec4 *& vertices, int & num_vertices,
                              GLuint *& indices, int &num_indices );
    Sphere (double max_radius = 20);
};
#endif
