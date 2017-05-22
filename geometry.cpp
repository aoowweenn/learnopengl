#include "geometry.h"

Triangle::Triangle()
{
    vertices = {
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3( 0.5f, -0.5f, 0.0f),
        glm::vec3( 0.0f, 0.866f * 4 / 3 - 0.5f, 0.0f)
    };
}

Rectangle::Rectangle()
{
    vertices = {
        glm::vec3( 0.5f,  0.5f, 0.0f),
        glm::vec3( 0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f,  0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f)
    };
    
    indices = {
        0, 1, 2,
        2, 1, 3
    };
}
