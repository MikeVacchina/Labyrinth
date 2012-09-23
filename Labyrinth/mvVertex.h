#ifndef MVVERTEX
#define MVVERTEX

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

struct mvVertex
{
    GLfloat position[3];
    GLfloat color[3];
};

#endif //MVVERTEX
