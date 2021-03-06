
#include <stdlib.h>
#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include "glfw/glfw_helper.h"

char *pszWindowTitle = "Example";

void drawScene()
{
}

MyWindow myWindow;

void mouseMove(GLFWwindow *pWindow, double x, double y)
{
    printf("X=%.0lf, Y=%.0lf\n", x, y);
}

void mouseButtonPressed(GLFWwindow *pWindow, int button, int action, int mods)
{
    printf("Button pressed\n");
}

int main()
{
    myWindow.width = 800;
    myWindow.height = 600;
    myWindow.pszWindowTitle = pszWindowTitle;
    myWindow.clearColors.red = 0.4;
    myWindow.clearColors.green = 0.4;
    myWindow.clearColors.blue = 0.4;
    myWindow.clearColors.alpha = 1;
    myWindow.cursorPosCallback = mouseMove;
    myWindow.mouseButtonCallback = mouseButtonPressed;

    int windowResult = openGLFWindow(&myWindow, &drawScene);

    destroyGLFWindow(&myWindow);

    return windowResult;
}
