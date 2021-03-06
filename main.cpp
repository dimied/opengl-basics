
#include <stdlib.h>
#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include "glfw/glfw_helper.h"
#include "opengl3.h"
#include "glsl.h"
#include "shader_scene_renderer.hpp"

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

Vertex2D points[] = {
    {{-1, 0}, {1, 0, 0, 1}},
    {{0, 1}, {0, 1, 0, 1}},
    {{1, 0}, {0, 0, 1, 1}},
};

unsigned int numberOfTriangles = 3;



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

    ShaderSceneRenderer * pRenderer = new ShaderSceneRenderer();
    int id = SHADER_WITH_COLOR;
    
    pRenderer->withColor = 1;
    pRenderer->pszVertexShader  = getShaderCode(id, VERTEX_SHADER);
    pRenderer->pszFragmentShader = getShaderCode(id, FRAGMENT_SHADER);
    pRenderer->pVertexData = points;
    pRenderer->vertexArrayNumEntries = 3;

    printf("Hallo\n");

    int windowResult = openGLFWindow(&myWindow, pRenderer);

    destroyGLFWindow(&myWindow);

    return windowResult;
}
