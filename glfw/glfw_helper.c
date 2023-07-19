
#include "glfw_helper.h"
#include "../glsl.h"
#include "../scene_renderer.h"

GLenum checkGLEW()
{
    // To prevent errors with modern OpenGL
    glewExperimental = GL_TRUE; // 1

    GLenum glewError = glewInit();

    if (glewError != GLEW_OK)
    {
        printf("glew init error\n%s\n", glewGetErrorString(glewError));
        return glewError;
    }

    if (!GLEW_VERSION_2_1)
    {
        printf("OpenGL 2.1 not supported!\n");
        return 1;
    }

    const GLubyte *p = glGetString(GL_VERSION);
    printf("Graphics Driver: %s\n", p);

    p = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("GLSL Version: %s\n", p);

    // 3. Check for specific functionality
    if (GLEW_ARB_vertex_array_object)
    {
        printf("genVertexArrays supported\n");
    }
    if (GLEW_APPLE_vertex_array_object)
    {
        printf("genVertexArrayAPPLE supported\n");
    }

    return GLEW_OK;
}

/**
 * Prints OpenGL to the console.
 * A context must be available to call that function and get valid result.
 */
void printOpenGLVersion()
{
    const GLubyte *pVersion = glGetString(GL_VERSION);
    if(pVersion != 0) {
        printf("OpenGL version: %s\n", pVersion);
    }
}

void destroyGLFWindow(MyWindow *pWindow)
{
    if (pWindow == 0)
    {
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

int openGLFWindow(MyWindow *pWindow, SceneRenderer *pRenderer)
{
    char const *pErr;

    if (!glfwInit())
    {
        printf("GLFW initialization failed\n");
        return EXIT_FAILURE;
    }

#ifdef USE_GLFW_WINDOW_HINTS
#if USE_GLFW_WINDOW_HINTS > 0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
#endif
#endif

#ifdef USE_CORE_OPENGL_PROFILE
#if USE_CORE_OPENGL_PROFILE > 0
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
#endif

#ifdef USE_OPENGL_FORWARD_COMPAT
#if USE_OPENGL_FORWARD_COMPAT > 0
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
#endif

    GLFWwindow *pglfWindow = glfwCreateWindow(
        pWindow->width,
        pWindow->height,
        pWindow->pszWindowTitle,
        NULL, NULL);

    if (!pglfWindow)
    {
        printf("GLFW window creation failed\n");
        glfwGetError(&pErr);
        printf("%s\n", pErr);
        glfwTerminate();
        return EXIT_FAILURE;
    }    

    pWindow->pglfWindow = pglfWindow;

    glfwMakeContextCurrent(pglfWindow);

    glfwSwapInterval(1);

    // We need a context to execute this, otherwise null is returned.

    GLenum glewRes = checkGLEW();

    if (glewRes != GLEW_OK)
    {
        pWindow->pglfWindow = NULL;
        glfwDestroyWindow(pglfWindow);
        pWindow->pglfWindow = 0;
        glfwTerminate();
        return 1;
    }
    printOpenGLVersion();

    // Configure depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Blending, especially for transparent objects
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // some default thickness for lines
    glLineWidth(3);

    
    // register callbacks for keyboard and mouse
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

    if (!called)
    {
        pRenderer->init();
        called++;
    }

    while (!glfwWindowShouldClose(pglfWindow))
    {
        // Get current dimensions of the framebuffer
        glfwGetFramebufferSize(
            pglfWindow,
            &pWindow->width,
            &pWindow->height);

        // Set viewport here,
        // such that on window resize
        // also the viewport gets will be resized
        glViewport(0, 0, pWindow->width, pWindow->height);

        // Clear contents and set background color
        glClearColor(
            pWindow->clearColors.rgba.red,
            pWindow->clearColors.rgba.green,
            pWindow->clearColors.rgba.blue,
            pWindow->clearColors.rgba.alpha);

        // also clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (pRenderer)
        {
            pRenderer->draw();
        }        

        // Switch the buffers(front, back)
        glfwSwapBuffers(pglfWindow);

        // Listening for Window events
        glfwPollEvents();
    }

    if (pWindow->pglfWindow != NULL)
    {
        glfwDestroyWindow(pWindow->pglfWindow);

        pWindow->pglfWindow = NULL;

        glfwTerminate();
    }

    return 0;
}
