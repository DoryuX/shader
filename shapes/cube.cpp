#include "cube.h"
#include <math.h>
#include <stdlib.h>
#include "../math/algebra3.h"

#ifndef __gl_h_
#include "GL/glew.h"
#endif

GLuint Cube::restart=65535;

Cube::Cube(double max_radius)
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

Cube::Cube( double start, double end, glm::vec3 rotation, double radius ) {
    m_start = start;
    m_end = end;
    rotVec = rotation;
    m_radius = radius;

    this->rotMatrix = glm::mat4(1.0f);
    this->rotMatrix = glm::rotate( this->rotMatrix, rotVec[0], glm::vec3(1.0f, 0.0f, 0.0f) );
    this->rotMatrix = glm::rotate( this->rotMatrix, rotVec[1], glm::vec3(0.0f, 1.0f, 0.0f) );
    this->rotMatrix = glm::rotate( this->rotMatrix, rotVec[2], glm::vec3(0.0f, 0.0f, 1.0f) );
}

void Cube::buildColors(int num, glm::vec4 *&colors) {
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

void Cube::buildRotations(int num, glm::mat4 *&rotMatrix) {
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

void Cube::buildArrays(int num, glm::vec4 *& vertices, int & num_vertices,
                         GLuint *& indices, int & num_indices)
{
    num_vertices = num;

    if ( vertices != NULL ) {
        cout << "Deleting Vertices" << endl;
        delete [] vertices;
    }

    vertices = new glm::vec4[num_vertices];

    // Front
    vertices[0][0] = -1.0; vertices[0][1] = -1.0; vertices[0][2] = 1.0; vertices[0][3] = 1.0;
    vertices[1][0] =  1.0; vertices[1][1] = -1.0; vertices[1][2] = 1.0; vertices[1][3] = 1.0;
    vertices[2][0] = -1.0; vertices[2][1] =  1.0; vertices[2][2] = 1.0; vertices[2][3] = 1.0;
    vertices[3][0] =  1.0; vertices[3][1] =  1.0; vertices[3][2] = 1.0; vertices[3][3] = 1.0;

    // Right
    vertices[4][0] = 1.0; vertices[4][1] = -1.0; vertices[4][2] =  1.0; vertices[4][3] = 1.0;
    vertices[5][0] = 1.0; vertices[5][1] = -1.0; vertices[5][2] = -1.0; vertices[5][3] = 1.0;
    vertices[6][0] = 1.0; vertices[6][1] =  1.0; vertices[6][2] =  1.0; vertices[6][3] = 1.0;
    vertices[7][0] = 1.0; vertices[7][1] =  1.0; vertices[7][2] = -1.0; vertices[7][3] = 1.0;

    // Back
     vertices[8][0] =  1.0;  vertices[8][1] = -1.0;  vertices[8][2] = -1.0;  vertices[8][3] = 1.0;
     vertices[9][0] = -1.0;  vertices[9][1] = -1.0;  vertices[9][2] = -1.0;  vertices[9][3] = 1.0;
    vertices[10][0] =  1.0; vertices[10][1] =  1.0; vertices[10][2] = -1.0; vertices[10][3] = 1.0;
    vertices[11][0] = -1.0; vertices[11][1] =  1.0; vertices[11][2] = -1.0; vertices[11][3] = 1.0;

    // Let
    vertices[12][0] = -1.0; vertices[12][1] = -1.0; vertices[12][2] = -1.0; vertices[12][3] = 1.0;
    vertices[13][0] = -1.0; vertices[13][1] = -1.0; vertices[13][2] =  1.0; vertices[13][3] = 1.0;
    vertices[14][0] = -1.0; vertices[14][1] =  1.0; vertices[14][2] = -1.0; vertices[14][3] = 1.0;
    vertices[15][0] = -1.0; vertices[15][1] =  1.0; vertices[15][2] =  1.0; vertices[15][3] = 1.0;

    // Bottom
    vertices[16][0] = -1.0; vertices[16][1] = -1.0; vertices[16][2] = -1.0; vertices[16][3] = 1.0;
    vertices[17][0] =  1.0; vertices[17][1] = -1.0; vertices[17][2] = -1.0; vertices[17][3] = 1.0;
    vertices[18][0] = -1.0; vertices[18][1] = -1.0; vertices[18][2] =  1.0; vertices[18][3] = 1.0;
    vertices[19][0] =  1.0; vertices[19][1] = -1.0; vertices[19][2] =  1.0; vertices[19][3] = 1.0;

    // Top
    vertices[20][0] = -1.0; vertices[20][1] = 1.0; vertices[20][2] =  1.0; vertices[20][3] = 1.0;
    vertices[21][0] =  1.0; vertices[21][1] = 1.0; vertices[21][2] =  1.0; vertices[21][3] = 1.0;
    vertices[22][0] = -1.0; vertices[22][1] = 1.0; vertices[22][2] = -1.0; vertices[22][3] = 1.0;
    vertices[23][0] =  1.0; vertices[23][1] = 1.0; vertices[23][2] = -1.0; vertices[23][3] = 1.0;


    // INDICES
    num_indices = 36;

    if ( indices != NULL ) {
        delete [] indices;
    }

    indices = new GLuint[num_indices];

    int n = 0;
    for(int i = 0; i < num_indices; i += 4) {
        indices[n++] = i;
        indices[n++] = i + 1;
        indices[n++] = i + 2;

        indices[n++] = i + 2;
        indices[n++] = i + 1;
        indices[n++] = i + 3;
    }
}
