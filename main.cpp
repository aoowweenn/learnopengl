#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <tuple>

#include "shader.h"
#include "triangle.h"

using namespace std;

#define WIDTH   (800)
#define HEIGHT  (600)
#define TITLE   "MY GL TEST"

tuple<GLuint, GLuint, GLuint> make_triangle()
{
    // Vertex Array Object -> Vertex Buffer Object -> vertices data

    GLuint VBO;
    glGenBuffers(1, &VBO);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    const auto vertices = createTriangle();
    assert(vertices.size() == 9);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // unbind VAO
    
    // create shader program

    GLuint vertexShader, fragmentShader;

    vertexShader = loadShader(GL_VERTEX_SHADER, "tri.vert");
    fragmentShader = loadShader(GL_FRAGMENT_SHADER, "tri.frag");

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    GLchar infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("[ERROR] Shader linking failed\n");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return make_tuple(VAO, VBO, shaderProgram);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __OSX__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwSwapInterval(1); // 0/1: turn vsync off/on

    glewExperimental = GL_TRUE;
}

int main()
{
    init();

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if(window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        exit(-1);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    // GLEW must be initialized after glfwMakeContextCurrent
    if(glewInit() != GLEW_OK)
    {
        printf("failed to initialize GLEW\n");
        exit(-1);
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    
    GLuint triVAO, triVBO, triProg;
    tie(triVAO, triVBO, triProg) = make_triangle();

    double time = glfwGetTime();
    double currTime;
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // active mode
        //glfwWaitEvents(); // passive mode

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(triProg);
        glBindVertexArray(triVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);

        currTime = glfwGetTime();
        printf("\rFPS: %3.2lf", 1.0 / (currTime - time));
        fflush(stdout);
        time = currTime;
    }

    glDeleteVertexArrays(1, &triVAO);
    glDeleteBuffers(1, &triVBO);

    glfwTerminate();
    printf("\n");
    return 0;
}
