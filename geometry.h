#include <GL/glew.h>
#include <vector>
#include <array>
#include <tuple>
//#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

class Triangle
{
public:
    Triangle();
    //Triangle& with(glm::vec3, glm::vec3, glm::vec3);
    const GLuint vSize() { return vertices.size() * sizeof(glm::vec3); };
    const GLfloat* vData() { return static_cast<GLfloat*>(glm::value_ptr(vertices.front())); };
private:
    std::vector<glm::vec3> vertices;
};

class Rectangle
{
public:
    Rectangle();
    //Rectangle& with(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
    const GLuint vSize() { return vertices.size() * sizeof(glm::vec3); };
    const GLfloat* vData() { return static_cast<GLfloat*>(glm::value_ptr(vertices.front())); };
    const GLuint iSize() { return indices.size() * sizeof(glm::uint); };
    GLuint* iData() { return static_cast<GLuint*>(indices.data()); };
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::uint> indices;
};
