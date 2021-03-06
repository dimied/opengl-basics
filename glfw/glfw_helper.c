
#include "glfw_helper.h"
#include "../glsl.h"

extern ShaderWithColor currentShader;

void checkGLEW()
{
    // To prevent errors with modern OpenGL
    glewExperimental = 1;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        printf("glew init error\n%s\n", glewGetErrorString(glewError));
    }

    if (!GLEW_VERSION_2_1)
    {
        printf("OpenGL 2.1 not supported!\n");
        return;
    }

    const GLubyte *p = glGetString(GL_VERSION);
    printf("Graphics Driver: %s\n", p);

    p = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("GLSL Version: %s\n", p);

    //3. Check for specific functionality
    if (GLEW_ARB_vertex_array_object)
    {
        printf("genVertexArrays supported\n");
    }
    if (GLEW_APPLE_vertex_array_object)
    {
        printf("genVertexArrayAPPLE supported\n");
    }
}

/**
 * Prints OpenGL to the console. 
 * A context must be available to call that function and get valid result.
 */
void printOpenGLVersion()
{
    const GLubyte *pVersion = glGetString(GL_VERSION);
    printf("OpenGL version: %s\n", pVersion);
}

void destroyGLFWindow(MyWindow *pWindow)
{
    if(pWindow == 0) {
        return;
    }

    if (pWindow->pglfWindow)
    {
        glfwDestroyWindow(pWindow->pglfWindow);
        pWindow->pglfWindow = 0;
        glfwTerminate();
    }
}

int called = 0;

int openGLFWindow(MyWindow *pWindow, drawSceneFunc drawScene)
{
    GLFWwindow *pglfWindow;

    if (!glfwInit())
    {
        printf("GLFW initialization failed\n");
        return EXIT_FAILURE;
    }
    pglfWindow = glfwCreateWindow(pWindow->width,
                                  pWindow->height,
                                  pWindow->pszWindowTitle,
                                  NULL, NULL);

    if (!pglfWindow)
    {
        printf("GLFW window creation failed\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    pWindow->pglfWindow = pglfWindow;

    glfwMakeContextCurrent(pglfWindow);
    glfwSwapInterval(1);

    // We need a context to execute this, otherwise null is returned.
    printOpenGLVersion();
    checkGLEW();

    // Configure depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Blending, especially for transparent objects
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // some default thickness for lines
    glLineWidth(3);   

    //register callbacks for keyboard and mouse
    if (pWindow->keyboardCallback)
    {
        glfwSetKeyCallback(pglfWindow, pWindow->keyboardCallback);
    }

    if (pWindow->cursorPosCallback)
    {
        glfwSetCursorPosCallback(pglfWindow, pWindow->cursorPosCallback);
    }
    
    if (pWindow->mouseButtonCallback)
    {
        glfwSetMouseButtonCallback(pglfWindow, pWindow->mouseButtonCallback);
    }

    if(!called) {
        initShaderForPoints(&currentShader);
        called++;
    }

    while (!glfwWindowShouldClose(pglfWindow))
    {
        // Get current dimensions of the framebuffer
        glfwGetFramebufferSize(pglfWindow, &pWindow->width, &pWindow->height);

        // Set viewport here, 
        // such that on window resize also the viewport gets will be resized
        glViewport(0, 0, pWindow->width, pWindow->height);

        // Clear contents and set background color
        glClearColor(pWindow->clearColors.red,
                     pWindow->clearColors.green,
                     pWindow->clearColors.blue,
                     pWindow->clearColors.alpha);
        // also clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (drawScene)
        {
            //drawScene();
            drawPoints();
        }

        // After drawing we switch the buffers(front, back)
        glfwSwapBuffers(pglfWindow);
        // Listening for Window events
        glfwPollEvents();
    }

    /*
    //Destroy window and terminate glfw in a clean way
    glfwDestroyWindow(pglfWindow);

    glfwTerminate();
*/
    return 0;
}
