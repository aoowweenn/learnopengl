#include "triangle.h"
using namespace std;

array<GLfloat, 9> createTriangle()
{
    array<GLfloat, 9> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f, 0.866f * 4 / 3 - 0.5f, 0.0f
    };
    return vertices;
}

tuple<array<GLfloat, 12>, array<GLuint, 6> > createRectangle()
{
    array<GLfloat, 12> vertices = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    
    array<GLuint, 6> indices = {
        0, 1, 2,
        2, 1, 3
    };
    return make_tuple(vertices, indices);
}
