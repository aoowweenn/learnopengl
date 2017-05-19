#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    GLuint program;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void use();
    std::string loadFile(const GLchar* path);
    GLuint compile(const GLchar* code, GLenum shaderType);
    GLuint link(const GLuint vShader, const GLuint fShader);
};

GLuint loadShader(GLenum shaderType, std::string filename);

#endif
