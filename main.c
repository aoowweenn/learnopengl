#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#define WIDTH   (800)
#define HEIGHT  (600)
#define TITLE   "MY GL TEST"

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

    double time = glfwGetTime();
    double currTime;
    while(!glfwWindowShouldClose(window))
    {
        //glfwPollEvents(); // active mode
        glfwWaitEvents(); // passive mode

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        currTime = glfwGetTime();
        printf("\rFPS: %lf", 1.0 / (currTime - time));
        time = currTime;
    }

    glfwTerminate();
    return 0;
}
