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
