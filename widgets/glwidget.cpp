#include <GL/glew.h>
#include "glwidget.h"
#include <stdio.h>
#include <QFile>
#include <QTime>

long ms_elapsed;
int frames;
QTime qt;

char * glWidget::readFile(QString name)
{
    int n;
    QFile file(name);
    file.open(QIODevice::ReadOnly);
    qint64 size = file.size();
    char *s = new char[size+1];
    n = file.read(s,size);
    s[size] = 0;
    return s;
}

glWidget::glWidget ( QWidget *parent )
: QGLWidget(parent)
{
    setMinimumWidth(800);
    setMinimumHeight(800);

    x_angle = 01.0;
    y_angle = 01.0;

    seconds = 0;
    elapsed_time = 0.0f;

    vertices = NULL;
    positions = NULL;
    colors = NULL;
    indices = NULL;
    rotations = NULL;
    velocities = NULL;
    rotMat = NULL;
    seed = time(NULL);
    srand(seed);
    QTimer *timer = new QTimer(this);
    connect ( timer, SIGNAL(timeout()), this, SLOT(rotate()) );
    timer->start(20);
}

glWidget::~glWidget() {
    delete [] vertices;
    delete [] positions;
    delete [] colors;
    delete [] rotations;
    delete [] rotMat;
    delete [] velocities;
}

void glWidget::setN(int n)
{
    this->n = n;

    // Reinitialize values.
    Cylinder::buildArrays(n,vertices,num_vertices,indices,num_indices);

    update();

    frames = 0;
    qt.start();
}

void glWidget::setRotate(int rotate)
{
    this->rotateCylinders = rotate;
}

void glWidget::setMaxRadius(double radius)
{
    this->max_radius = radius;
}

void glWidget::setNumCylinders(int n)
{
    this->num_cylinders = n;
    cylinders.clear();
    for ( int i = 0; i < n; i++ ) {
        cylinders.push_back ( new Cylinder(max_radius) );
    }
    update();

    Cylinder::buildColors(this->num_cylinders, colors);
    Cylinder::buildRotations(this->num_cylinders, rotMat);

    // Assign some random rotations
    //buildRotations();
}

void glWidget::updatePositions()
{
    int num_cylinders;
    int i;
    Cylinder *c;

    num_cylinders = cylinders.size();
    if ( positions == NULL ) {
        positions = new glm::vec4[num_cylinders];
    }

    for ( i = 0; i < num_cylinders; i++ ) {
        c = cylinders[i];
        c->x = c->x + c->vel[0];
        c->y = c->y + c->vel[1];
        c->z = c->z + c->vel[2];

        if ( c->x < -500 || c->x > 500 ) c->vel[0] = -c->vel[0];
        if ( c->y < -500 || c->y > 500 ) c->vel[1] = -c->vel[1];
        if ( c->z < -500 || c->z > 500 ) c->vel[2] = -c->vel[2];

        positions[i][0] = c->x;
        positions[i][1] = c->y;
        positions[i][2] = c->z;
        positions[i][3] = c->m_radius;
    }
}

void glWidget::buildRotations() {

    if(rotations != NULL) {
        delete [] rotations;
    }

    rotations = new glm::vec4[this->num_cylinders];

    for(int i = 0; i < this->num_cylinders; i++) {
        rotations[i][0] = (float)(rand()/(float)RAND_MAX) * 0.5f;
        rotations[i][1] = (float)(rand()/(float)RAND_MAX) * 0.5f;
        rotations[i][2] = (float)(rand()/(float)RAND_MAX) * 0.5f;
        rotations[i][3] = 1.0f;

        //rotations[i][0] = 30.0f;
        //rotations[i][1] = 0.5f;
        //rotations[i][2] = 0.0f;
        //rotations[i][3] = 1.0f;
    }

    /*
    rotations[0] = glm::vec4(1.0, 0.0, 0.0, 1.0);
    rotations[1] = glm::vec4(0.0, 1.0, 0.0, 1.0);
    rotations[2] = glm::vec4(0.0, 0.0, 1.0, 1.0);
    rotations[3] = glm::vec4(1.0, 1.0, 0.0, 1.0); // Yellow
    rotations[4] = glm::vec4(1.0, 0.0, 1.0, 1.0); // Purple
    */
}

void glWidget::updateRotations()
{
    glm::mat4 t;

    for(int i = 0; i < this->num_cylinders; i++) {
        t = rotMat[i];
        t = glm::rotate(t, rotations[i][0], glm::vec3(1.0, 0.0, 0.0));
        t = glm::rotate(t, rotations[i][1], glm::vec3(0.0, 1.0, 0.0));
        //t = glm::rotate(t, rotations[i][2], glm::vec3(0.0, 0.0, 1.0));

        this->rotMat[i] = t;
    }
}

void glWidget::setVelocities() {

    if(velocities != NULL) {
        delete [] velocities;
        velocities = NULL;
    }

    velocities = new glm::vec3[this->num_cylinders];

    for(int i = 0; i < this->num_cylinders; i++) {
        velocities[i].x = cylinders[i]->vel[0];
        velocities[i].y = cylinders[i]->vel[1];
        velocities[i].z = cylinders[i]->vel[2];
    }
}

void glWidget::setUniforms() {
    locDiff = glGetUniformLocation ( shaderProgram, "diffuse" );
    locLight = glGetUniformLocation ( shaderProgram, "light" );
    locMVP = glGetUniformLocation ( shaderProgram, "MVP" );
    locMV = glGetUniformLocation ( shaderProgram, "MV" );
    locNM = glGetUniformLocation ( shaderProgram, "NM" );
    locElapsedTime = glGetUniformLocation( shaderProgram, "elapsed_time");

    locVertex = glGetAttribLocation ( shaderProgram, "vertex" );
    locInstance = glGetAttribLocation ( shaderProgram, "instance" );
    locColor = glGetAttribLocation ( shaderProgram, "color" );

    light[ambient] = glm::vec4( 0.3f, 0.3f, 0.3f, 1.0f );
    light[specular] = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    light[diffuse] = glm::vec4( 0.6f, 0.6f, 0.6f, 1.0f );
    light[emission] = glm::vec4( 0.2f, 0.2f, 0.2f, 1.0f );
    light[position] = glm::vec4( 600.0f, 1200.0f, 1200.0f, 0.0f );
    light[shininess] = glm::vec4( 128.0f );

    glUniform4fv ( locLight, 6, &light[0][0] );

    tbo_Positions = glGetUniformLocation( shaderProgram, "tex_Positions");

}

void glWidget::setArrayObject() {
    // Bind vertex attributes
    glGenVertexArrays ( 1, &vao );
    glBindVertexArray ( vao );

    glGenBuffers(7,vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo[0]); // vertices
    glEnableVertexAttribArray(locVertex);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*4*num_vertices,
                 vertices, GL_STATIC_DRAW );
    glVertexAttribPointer(locVertex,4,GL_FLOAT,GL_FALSE,0,0);

    glVertexAttribDivisorARB(vbo[0], 1);

    glBindBuffer(GL_ARRAY_BUFFER,vbo[1]); // positions
    glEnableVertexAttribArray(locInstance);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*4*num_cylinders,
                 positions, GL_STATIC_DRAW );
    glVertexAttribPointer(locInstance,4,GL_FLOAT,GL_FALSE,0,0);

    glVertexAttribDivisorARB(locInstance,1);

    glBindBuffer(GL_ARRAY_BUFFER,vbo[2]); // colors
    glEnableVertexAttribArray(locColor);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*4*num_cylinders,
                 colors, GL_STATIC_DRAW );
    glVertexAttribPointer(locColor,4,GL_FLOAT,GL_FALSE,0,0);

    glVertexAttribDivisorARB(locColor,1);

    locRotations = glGetAttribLocation( shaderProgram, "rotations" );

    glBindBuffer(GL_ARRAY_BUFFER,vbo[3]); // rotations
    glEnableVertexAttribArray(locRotations);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*4*num_cylinders,
                 rotations, GL_STATIC_DRAW );
    glVertexAttribPointer(locRotations,4,GL_FLOAT,GL_FALSE,0,0);

    glVertexAttribDivisorARB(locRotations,1);

    locVelocities = glGetAttribLocation( shaderProgram, "velocities" );

    glBindBuffer(GL_ARRAY_BUFFER,vbo[3]); // velocities
    glEnableVertexAttribArray(locVelocities);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3*num_cylinders,
                 velocities, GL_STATIC_DRAW );
    glVertexAttribPointer(locVelocities,3,GL_FLOAT,GL_FALSE,0,0);

    glVertexAttribDivisorARB(locVelocities,1);

    // Set Up Rotation Matrix
    locRotMat = glGetAttribLocation( shaderProgram, "rotationMatrix" );

    glEnableVertexAttribArray( locRotMat );
    glEnableVertexAttribArray( locRotMat + 1 );
    glEnableVertexAttribArray( locRotMat + 2 );
    glEnableVertexAttribArray( locRotMat + 3 );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[4] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, rotMat, GL_STATIC_DRAW );

    glVertexAttribPointer( locRotMat, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)0 );
    glVertexAttribPointer( locRotMat + 1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 4) );
    glVertexAttribPointer( locRotMat + 2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 8) );
    glVertexAttribPointer( locRotMat + 3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 12) );

    glVertexAttribDivisorARB( locRotMat, 1 );
    glVertexAttribDivisorARB( locRotMat + 1, 1 );
    glVertexAttribDivisorARB( locRotMat + 2, 1 );
    glVertexAttribDivisorARB( locRotMat + 3, 1 );

    glGenTextures(1, &tbo_Positions);
    glBindTexture(GL_TEXTURE_BUFFER, tbo_Positions);
    glTexBufferEXT(GL_TEXTURE_BUFFER, GL_RGBA32F, vbo[0]);

    glUniform1i(tbo_Positions, 0);

    //glBindVertexArray(0);
}


void glWidget::setShader() {
    char* code = NULL;
    // Create Vertex Shader
    vertexShader = glCreateShader ( GL_VERTEX_SHADER );
    code = readFile(":/shaders/c.v");
    glShaderSource ( vertexShader, 1, (const GLchar **)&code, NULL );
    glCompileShader ( vertexShader );
    printShaderInfoLog(vertexShader);

    // Create Fragment Shader
    fragmentShader = glCreateShader ( GL_FRAGMENT_SHADER );
    code = readFile(":/shaders/c.f");
    glShaderSource ( fragmentShader, 1, (const GLchar **)&code, NULL );
    glCompileShader ( fragmentShader );
    printShaderInfoLog(fragmentShader);

    // Create Shader Object
    shaderProgram = glCreateProgram();

    // Attach the different shaders
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    //printProgramInfoLog(shaderProgram);
    glUseProgram(shaderProgram);
}

void glWidget::printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}


void glWidget::printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

void glWidget::printAttributes ( const char *name, GLuint obj )
{
    char *attr;
    GLint active, max_length;

    glGetProgramiv ( obj, GL_ACTIVE_ATTRIBUTES, &active );
    glGetProgramiv ( obj, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_length );
    printf("%s: active %d, max_length %d\n",name,active,max_length);
    attr = (char *)malloc ( max_length + 1 );

    for ( int i = 0; i < active; i++ ) {
        GLint size;
        GLenum type;
        glGetActiveAttrib ( obj, i, max_length+1, NULL,
            &size, &type, attr );
        printf("%s %d is at location %d\n",
            attr, type, glGetAttribLocation(obj,attr));
    }
    free ( attr );
}

void glWidget::initializeGL()
{
    glClearColor ( 0.6, 0.75, 0.85, 0.0 );

    glEnable ( GL_DEPTH_TEST );

    PROJ = glm::ortho ( -800.0f, 800.0f, -800.0f, 800.0f, -900.0f, 900.0f );

    glewInit();

    glEnable ( GL_PRIMITIVE_RESTART );
    glPrimitiveRestartIndexNV ( 65535 );

    setShader();
}

void glWidget::resizeGL(int width, int height)
{
    glViewport ( 0, 0, width, height );

    PROJ = glm::ortho( -800.0f, 800.0f, -800.0f, 800.0f, -900.0f, 900.0f );
}

void glWidget::rotate()
{
    x_angle += 0.1; // 0.1
    y_angle += 0.13; // 0.13
    update();
}

void glWidget::paintGL()
{
    static int first = 1;
    srand(seed);
    glEnable ( GL_DEPTH_TEST );
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( first ) {
        Cylinder::buildArrays(n,vertices,num_vertices,indices,num_indices);

        if(positions == NULL) {
            updatePositions();
        }

        if(rotations == NULL) {
            buildRotations();
        }

        if(velocities == NULL) {
            setVelocities();
        }

        setUniforms();
        setArrayObject();

        MV = glm::mat4(1.0f);
        NM = glm::inverseTranspose(MV);
        MVP = PROJ * MV;

        glUniformMatrix4fv ( locNM, 1, GL_FALSE, &NM[0][0] );
        glUniformMatrix4fv ( locMV, 1, GL_FALSE, &MV[0][0] );
        glUniformMatrix4fv ( locMVP,1, GL_FALSE, &MVP[0][0] );

        // Rotations
        glEnableVertexAttribArray( locRotMat );
        glEnableVertexAttribArray( locRotMat + 1 );
        glEnableVertexAttribArray( locRotMat + 2 );
        glEnableVertexAttribArray( locRotMat + 3 );

        glBindBuffer( GL_ARRAY_BUFFER, vbo[4] );
        glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4 * num_cylinders, rotMat, GL_STATIC_DRAW );

        glVertexAttribDivisorARB(locInstance, 1);
        glVertexAttribDivisorARB(locColor, 1);
        glVertexAttribDivisorARB(locRotations, 1);
        glVertexAttribDivisorARB(locVelocities, 1);

        glVertexAttribDivisorARB( locRotMat, 1);
        glVertexAttribDivisorARB( locRotMat + 1, 1 );
        glVertexAttribDivisorARB( locRotMat + 2, 1 );
        glVertexAttribDivisorARB( locRotMat + 3, 1 );

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_BUFFER, vbo[0]);

        first = 0;
    }

    //updatePositions();

    //if ( rotateCylinders ) {
    //if ( 1 ) {
        //updateRotations();
        //MV = glm::rotate ( MV, x_angle, glm::vec3(1.0f,0.0f,0.0f) );
        //MV = glm::rotate ( MV, y_angle, glm::vec3(0.0f,1.0f,0.0f) );
    //}

    //glGetFloatv(GL_MODELVIEW_MATRIX, &MV[0][0]);

    glUniform1f(locElapsedTime, elapsed_time);

    glDrawElementsInstancedEXT ( GL_TRIANGLE_STRIP, num_indices, GL_UNSIGNED_INT, indices, num_cylinders );

    frames++;
    ms_elapsed = qt.elapsed();

    elapsed_time = seconds + (ms_elapsed / 1000.0f);

    if ( ms_elapsed >= 1000 ) {
        double fps = (double)frames / (ms_elapsed/1000.0);
        printf("FPS = %7.2f, elapsed = %7.2f\n",fps, elapsed_time);
        qt.start();
        frames = 0;
        seconds++;
    }
}

