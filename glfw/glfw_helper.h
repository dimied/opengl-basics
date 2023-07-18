#ifndef __OPENGL_EXAMPLES_GLFW_HELPER__
#define __OPENGL_EXAMPLES_GLFW_HELPER__

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
//for Windows may be useful
//#include <GL/wglew.h>
#include <GLFW/glfw3.h>
//
#include "gl_window.h"
#include "../scene_renderer.h"

int openGLFWindow(
    MyWindow *pWindow,
    SceneRenderer* pRenderer
);

void destroyGLFWindow(MyWindow *pWindow);

#endif