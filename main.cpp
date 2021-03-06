#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <tuple>

#include "shader.h"
#include "geometry.h"

using namespace std;

#define WIDTH   (800)
#define HEIGHT  (600)
#define TITLE   "MY GL TEST"

void bindObject(GLuint& VBO, GLuint& VAO, GLuint& EBO, GLsizeiptr VBOsize, const GLvoid* VBOdata, GLsizeiptr EBOsize, GLvoid* EBOdata)
{
    // Vertex Array Object -> Vertex Buffer Object -> vertices data
    
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, VBOsize, VBOdata, GL_STATIC_DRAW);

    if(EBOsize != 0)
    {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOsize, EBOdata, GL_STATIC_DRAW);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // unbind VAO
}

tuple<GLuint, GLuint> make_triangle()
{
    auto triGeometry = Triangle();

    GLuint VBO, VAO, EBO;
    bindObject(VBO, VAO, EBO, triGeometry.vSize(), triGeometry.vData(), 0, nullptr);
    return make_tuple(VAO, VBO);
}

tuple<GLuint, GLuint, GLuint> make_rectangle()
{
    auto recGeometry = Rectangle();

    GLuint VBO, VAO, EBO;
    bindObject(VBO, VAO, EBO, recGeometry.vSize(), recGeometry.vData(), recGeometry.iSize(), recGeometry.iData());
    return make_tuple(VAO, VBO, EBO);
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    
    GLuint triVAO, triVBO;
    tie(triVAO, triVBO) = make_triangle();
    Shader triShader("tri.vert", "tri.frag");

    GLuint recVAO, recVBO, recEBO;
    tie(recVAO, recVBO, recEBO) = make_rectangle();
    Shader recShader("rec.vert", "rec.frag");

    double time = glfwGetTime();
    double currTime;
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // active mode
        //glfwWaitEvents(); // passive mode

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        triShader.use();
        glBindVertexArray(triVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glBindVertexArray(0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        recShader.use();
        glBindVertexArray(recVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
