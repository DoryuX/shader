#include "sphere.h"
#include <math.h>
#include <stdlib.h>
#include "../math/algebra3.h"

int Sphere::slices=3;
int Sphere::stacks=2;
GLuint Sphere::restart=65535;

Sphere::Sphere(double max_radius)
{
    x = rand() / (double)RAND_MAX*1000.0 - 500;
    y = rand() / (double)RAND_MAX*1000.0 - 500;
    z = rand() / (double)RAND_MAX*1000.0 - 500;
    radius = rand() / (double)RAND_MAX*max_radius + max_radius/20.0;
    red = 0.8*rand()/(double)RAND_MAX + 0.2;
    blue = 0.8*rand()/(double)RAND_MAX;
    green = 0.8*rand()/(double)RAND_MAX + 0.2;
    q = 100*rand()/(double)RAND_MAX;
    for ( int i = 0; i < 3; i++ ) {
        vel[i] = 2.0 * rand()/(double)RAND_MAX;
    }
}

void Sphere::buildArrays(int num, glm::vec4 *& vertices, int & num_vertices,
                         GLuint *& indices, int & num_indices)
{
    glm::vec3 p;
    double slice_angle, stack_angle, xy;
    int top_index;
    int slice, stack, k;

    slices = num;
    if ( slices < 3 ) slices = 3;
    if ( slices > 100 ) slices = 100;
    stacks = slices/4;
    if ( stacks < 2 ) stacks = 2;

/*
 *  This will construct a half sphere of num slices.  Each sphere will consist
 *  of a triangle strip with 2*stacks-1 triangles.  To represent all the
 *  vertices there will need to be stacks vertices for each slice and 1 for
 *  the top point of the sphere (0,0,1).  This means that the number of
 *  vertices is slices * slabs + 1;
 */
    num_vertices = slices * stacks + 1;
    printf("Building arrays, slices = %d, stacks = %d, num_vertices = %d\n",
        slices, stacks, num_vertices );

    if ( vertices != NULL ) delete [] vertices;
    vertices = new glm::vec4[num_vertices];
    top_index = num_vertices-1;
    vertices[top_index] = glm::vec4(0,0,1,1);

    k = 0;
    for ( stack = 0; stack < stacks; stack++ ) {
        stack_angle = stack*M_PI/2.0/stacks;
        xy = cos(stack_angle);
        for ( slice = 0; slice < slices; slice++ ) {
            slice_angle = slice*M_PI*2.0/slices;
            vertices[k][3] = 1;
            vertices[k][2] = sin(stack_angle);
            vertices[k][0] = xy*cos(slice_angle);
            vertices[k][1] = xy*sin(slice_angle);
            printf("stack %d, slice %d, x %g, y %g, z %g\n",
                    stack, slice, vertices[k][0], vertices[k][1], vertices[k][2]);
            k++;
        }
    }
    
/*
 *  For each slice we will generate indices for 2*(stacks-1) triangles
 *  forming quads and 1 more for the top point and finally an extra index for
 *  restarting the triangle strip.  This is a total of 2*(stacks-1) + 2 indices
 *  for the quads, 1 more index for the top point and finally 1 more for the
 *  restart index.  All together this is 2*stacks + 2 per slice.
 */
    num_indices = slices * (2*stacks+2);
    printf("Building arrays, slices = %d, stacks = %d, num_indices = %d\n",
        slices, stacks, num_indices );

    if ( indices != NULL ) delete [] indices;
    indices = new GLuint[num_indices];
    k = 0;
    for ( slice = 0; slice < slices; slice++ ) {
        for ( stack = 0; stack < stacks; stack++ ) {
            indices[k++] = stack*slices + slice;
            indices[k++] = stack*slices + (slice + 1)%slices;
        }
        indices[k++] = top_index;
        indices[k++] = restart;
    }
    printf("Pushed %d indices\n",k);
    for ( k = 0; k < num_indices; k++ ) {
        if ( indices[k] != restart ) {
            printf("index %d, %g %g %g\n",indices[k],
                vertices[indices[k]][0],
                vertices[indices[k]][1],
                vertices[indices[k]][2] );
        } else {
            printf("restart\n");
        }
    }
}
