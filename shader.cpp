#include "shader.h"
#include <iostream>
#include <fstream>
using namespace std;

const char* loadCStringFromFile(string filename)
{
    ifstream ifs(filename.c_str(), fstream::in | fstream::ate);
    if(!ifs.is_open())
    {
        cout << "Can't load file: " << filename << endl;
        exit(-1);
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
        cout << "[ERROR] Compilation failed: " << filename << endl;
    }

    delete[] prog;
    
    return shader;
}
