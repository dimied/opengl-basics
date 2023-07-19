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

// Optional
#define USE_GLFW_WINDOW_HINTS 0

// If set then functionaly for older versions is not available
#define USE_CORE_OPENGL_PROFILE 0

#define USE_OPENGL_FORWARD_COMPAT 0

int openGLFWindow(
    MyWindow *pWindow,
    SceneRenderer* pRenderer
);

void destroyGLFWindow(MyWindow *pWindow);

#endif