
#include "glfw_helper.h"


/**
 * Prints OpenGL to the console. 
 * A context must be available to call that function and get valid result.
 */
void printOpenGLVersion() {
    const GLubyte *pVersion = glGetString(GL_VERSION);
    printf("OpenGL version: %s\n", pVersion);
}

int openGLFWindow(int width, int height, char* pszWindowTitle, drawSceneFunc drawScene)
{
    GLFWwindow *pWindow;

    if (!glfwInit())
    {
        printf("GLFW initialization failed\n");
        return EXIT_FAILURE;
    }
    pWindow = glfwCreateWindow(width, height, pszWindowTitle, NULL, NULL);

    if (!pWindow)
    {
        printf("GLFW window creation failed\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(pWindow);

    // We need a context to execute this, otherwise null is returned.
    printOpenGLVersion();

    while (!glfwWindowShouldClose(pWindow))
    {
        glViewport(0, 0, width, height);
        // Clear contents and set background color
        glClearColor(1, 0, 1, 1);
        // also clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(drawScene) {
            drawScene();
        }

        // After drawing we switch the buffers(front, back)
        glfwSwapBuffers(pWindow);
        // Listening for Window events
        glfwPollEvents();
    }

    //Destroy window and terminate glfw in a clean way
    glfwDestroyWindow(pWindow);

    glfwTerminate();

    return 0;
}

