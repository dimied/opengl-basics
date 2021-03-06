#ifndef __OPENGL_EXAMPLES_GLFW_HELPER__
#define __OPENGL_EXAMPLES_GLFW_HELPER__

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef void (*drawSceneFunc)();

typedef struct
{
    int width;
    int height;
    char *pszWindowTitle;
    struct
    {
        float red;
        float green;
        float blue;
        float alpha;
    } clearColors;
    GLFWkeyfun keyboardCallback;
    GLFWcursorposfun cursorPosCallback;
    GLFWmousebuttonfun mouseButtonCallback;
    // private
    GLFWwindow *pglfWindow;
} MyWindow;

int openGLFWindow(
    MyWindow *pWindow,
    drawSceneFunc drawScene);

void destroyGLFWindow(MyWindow *pWindow);

#endif