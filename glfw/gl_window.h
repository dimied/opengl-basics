#ifndef __MY_GL_WINDOW_STRUCT__
#define __MY_GL_WINDOW_STRUCT__

#include <GLFW/glfw3.h>

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

#endif