#ifndef POINT_H
#define POINT_H

#ifndef __gl_h_
#include <GL/gl.h>
#endif

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

using namespace std;

class Cube {
public:

    double x, y, z;
    double vel[3];
    double m_radius;
    double m_start;
    double m_end;
    double m_rotation;

    double q;

    glm::vec3 rotVec;
    glm::vec4 color;
    glm::mat4 rotMatrix;

    void draw(double angle,int n);
    static GLuint restart;
    static void buildArrays ( int n, glm::vec4 *& vertices, int & num_vertices,
                              GLuint *& indices, int &num_indices );
    static void buildColors(int n, glm::vec4 *&colors);
    static void buildRotations(int n, glm::mat4 *&rotMatrix);

    Cube( double max_radius = 20 );
    Cube( double, double, glm::vec3, double );
};
#endif
