#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    string vertex_code, fragment_code;
    vertex_code = loadFile(vertexPath);
    fragment_code = loadFile(fragmentPath);
    const GLchar* vShaderCode = vertex_code.c_str();
    const GLchar* fShaderCode = fragment_code.c_str();
    GLuint vShader = compile(vShaderCode, GL_VERTEX_SHADER);
    GLuint fShader = compile(fShaderCode, GL_FRAGMENT_SHADER);
    this->program = link(vShader, fShader);
}

void Shader::use()
{
    glUseProgram(this->program);
}

GLuint Shader::link(const GLuint vShader, const GLuint fShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    GLint success;
    GLchar infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "[ERROR] Linking failed\n" << infoLog << std::endl;
        std::exit(-1);
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return program;
}

GLuint Shader::compile(const GLchar* code, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar**)&code, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "[ERROR] Compilation failed\n" << infoLog << std::endl;
        std::exit(-1);
    }
    return shader;
}

std::string Shader::loadFile(const GLchar* filename)
{
    ifstream fs;
    fs.exceptions(ifstream::failbit | ifstream::badbit);
    try
    {
        fs.open(std::string("shader/") + filename);
        std::stringstream ss;
        ss << fs.rdbuf();
        fs.close();
        return ss.str();
    }
    catch(ifstream::failure e)
    {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        std::exit(-1);
    }
    return std::string("");
}

const char* loadCStringFromFile(string filename)
{
    ifstream ifs(filename.c_str(), fstream::in | fstream::ate);
    if(!ifs.is_open())
    {
        std::cout << "Can't load file: " << filename << std::endl;
        std::exit(-1);
    }

    fstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, fstream::beg);

    char* buffer = (char*)new char[fileSize];
    ifs.read(buffer, fileSize);

    return buffer;
}

GLuint loadShader(GLenum shaderType, std::string filename)
{
    GLuint shader = glCreateShader(shaderType);

    const char* prog = loadCStringFromFile(std::string("shader") + "/" + filename);
    
    glShaderSource(shader, 1, (const GLchar**)&prog, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[ERROR] Compilation failed: " << filename << std::endl;
    }

    delete[] prog;
    
    return shader;
}
