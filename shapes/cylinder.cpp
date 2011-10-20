#include "cylinder.h"
#include <math.h>
#include <stdlib.h>
#include "../math/algebra3.h"

GLuint Cylinder::restart=65535;

Cylinder::Cylinder(double max_radius)
{
    x = rand() / (double)RAND_MAX*1000.0 - 500;
    y = rand() / (double)RAND_MAX*1000.0 - 500;
    z = rand() / (double)RAND_MAX*1000.0 - 500;

    m_radius = rand() / (double)RAND_MAX*max_radius + max_radius/20.0;

    q = 100*rand()/(double)RAND_MAX;

    for ( int i = 0; i < 3; i++ ) {
        vel[i] = 2.0 * rand()/(double)RAND_MAX;

        if((rand() % 10) >= 5) {
            vel[i] *= -1;
        }
    }
}

Cylinder::Cylinder( double start, double end, glm::vec3 rotation, double radius ) {
    m_start = start;
    m_end = end;
    rotVec = rotation;
    m_radius = radius;

    this->rotMatrix = glm::mat4(1.0f);
    this->rotMatrix = glm::rotate( this->rotMatrix, rotVec[0], glm::vec3(1.0f, 0.0f, 0.0f) );
    this->rotMatrix = glm::rotate( this->rotMatrix, rotVec[1], glm::vec3(0.0f, 1.0f, 0.0f) );
    this->rotMatrix = glm::rotate( this->rotMatrix, rotVec[2], glm::vec3(0.0f, 0.0f, 1.0f) );
}

void Cylinder::buildColors(int num, glm::vec4 *&colors) {
    if ( colors != NULL ) {
        delete [] colors;
    }

    colors = new glm::vec4[num];

    for(int i = 0; i < num; i++) {
        colors[i][0] = 0.2 + (0.8*(rand()/(double)RAND_MAX));
        colors[i][1] = 0.2 + (0.8*(rand()/(double)RAND_MAX));
        colors[i][2] = 0.2 + (0.8*(rand()/(double)RAND_MAX));
        colors[i][3] = 1.0;
    }
}

void Cylinder::buildRotations(int num, glm::mat4 *&rotMatrix) {
    float randDegree = 0.0f;

    if(rotMatrix != NULL) {
        delete [] rotMatrix;
    }

    rotMatrix = new glm::mat4[num];

    for(int i = 0; i < num; i++) {
        randDegree = (float)(rand()/(float)RAND_MAX) * 90.0f;
        rotMatrix[i] = glm::rotate( glm::mat4(1.0f), randDegree, glm::vec3(0.0f, 1.0f, 0.0f) );
    }
}

void Cylinder::buildArrays(int num, glm::vec4 *& vertices, int & num_vertices,
                         GLuint *& indices, int & num_indices)
{
    double step = (2*M_PI) / num;

    num_vertices = 2*num;

    if ( vertices != NULL ) {
        delete [] vertices;
    }

    vertices = new glm::vec4[num_vertices];

    // Front Face
    for(int i = 0; i < num; i++) {
        vertices[i][0] = cos(i*step);
        vertices[i][1] = sin(i*step);
        vertices[i][2] = 1.0;
        vertices[i][3] = 1.0;
    }

    // Back Face
    for(int i = num; i < num_vertices; i++) {
        vertices[i][0] = cos(i*step);
        vertices[i][1] = sin(i*step);
        vertices[i][2] = -1.0;
        vertices[i][3] = 1.0;
    }

    // INDICES
    int count = 0;
    num_indices = num_vertices + 2;

    if ( indices != NULL ) {
        delete [] indices;
    }

    indices = new GLuint[num_indices];

    for(int i = 0; i < num_vertices; i+=2) {
        indices[i+1] = (num_vertices - 1) - count;
        indices[i] = (num-1) - count;
        count++;
    }

    // Close Strip
    indices[num_indices - 2] = indices[0];
    indices[num_indices - 1] = indices[1];
}
