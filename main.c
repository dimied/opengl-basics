
#include <stdlib.h>
#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include "glfw/glfw_helper.h"
#include "opengl3.h"
#include "glsl.h"

char *pszWindowTitle = "Example";
MyWindow myWindow;

void drawScene()
{
    // drawSingleTriangle();
    drawRotatingTriangle();
}

void mouseMove(GLFWwindow *pWindow, double x, double y)
{
    //printf("X=%.0lf, Y=%.0lf\n", x, y);
}

void mouseButtonPressed(GLFWwindow *pWindow, int button, int action, int mods)
{
    printf("Button pressed\n");
}

ShaderWithColor currentShader;

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

    currentShader.withColor = 1;
    int id = SHADER_WITH_COLOR;
    currentShader.pszVertexShader = getShaderCode(id, VERTEX_SHADER);
    currentShader.pszFragmentShader = getShaderCode(id, FRAGMENT_SHADER);

    int windowResult = openGLFWindow(&myWindow, &drawScene);

    destroyGLFWindow(&myWindow);

    return windowResult;
}
