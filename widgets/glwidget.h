#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "../shapes/cylinder.h"

using namespace std;

class glWidget : public QGLWidget
{
    Q_OBJECT

    int num_cylinders;
    int num_vertices;

    glm::vec4 *vertices;
    glm::vec4 *positions;
    glm::vec4 *colors;
    glm::vec4 *rotations;

    glm::vec3 *velocities;

    int num_indices;
    GLuint *indices;
    int n;
    int seed;
    int rotateCylinders;
    double max_radius;
    float x_angle;
    float y_angle;

    GLuint seconds;
    GLfloat elapsed_time;

public:
    enum lightParams { ambient, diffuse, emission, position,
                       shininess, specular };
    glWidget ( QWidget *parent=0 );
    ~glWidget();

    char * readFile(QString name);
    vector<Cylinder*> cylinders;
    void setNumCylinders ( int n );
    void setRotate ( int rotate );
    void setMaxRadius ( double radius );
    void setVelocities();
    void buildRotations();
    void updatePositions();
    void updateRotations();

    void printShaderInfoLog( GLuint obj );
    void printProgramInfoLog( GLuint obj );
    void printAttributes( const char* name, GLuint obj );

    void setUniforms();
    void setArrayObject();
    void setShader();

    GLfloat angles[3];
    GLuint vao, vbo[20], pbo;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint locVertex;
    GLuint locInstance;
    GLuint locColor;
    GLuint locDiff;
    GLuint locLight;
    GLuint locMVP;
    GLuint locMV;
    GLuint locNM;
    GLuint locRotMat;
    GLuint locRotations;
    GLuint locVelocities;
    GLuint locElapsedTime;

    GLuint tbo_Positions;

    glm::mat4 MVP;
    glm::mat4 MV;
    glm::mat4 PROJ;
    glm::mat4 NM;
    glm::mat4 *rotMat;

    glm::vec4 light[6];

public slots:
    void rotate();
    void setN ( int n );

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
};

#endif
