#ifndef __OPENGL_EXAMPLES_GLFW_HELPER__
#define __OPENGL_EXAMPLES_GLFW_HELPER__

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef void (*drawSceneFunc)();

int openGLFWindow(
    int width,
    int height,
    char *pszWindowTitle,
    drawSceneFunc drawScene);

#endif