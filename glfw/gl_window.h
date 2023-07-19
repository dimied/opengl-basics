#ifndef __MY_GL_WINDOW_STRUCT__
#define __MY_GL_WINDOW_STRUCT__

#include <GLFW/glfw3.h>

typedef struct
{
    int width;
    int height;
    char *pszWindowTitle;
    union {
        struct {
        float red;
        float green;
        float blue;
        float alpha;
        } rgba;
        float values[4];
    } clearColors;
    GLFWkeyfun keyboardCallback;
    GLFWcursorposfun cursorPosCallback;
    GLFWmousebuttonfun mouseButtonCallback;
    
    GLFWwindow *pglfWindow;
} MyWindow;

#endif