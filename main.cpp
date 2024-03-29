
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "glfw/glfw_helper.h"
#include "glsl.h"
#include "opengl3.h"
#include "shader_scene_renderer.hpp"
#include <GL/glew.h>

#include "gl_basics.h"

const char *pszWindowTitle = "Example";
MyWindow myWindow;

void drawScene() { drawRotatingTriangle(); }

void mouseMove(GLFWwindow *pWindow, double x, double y) {
  // printf("X=%.0lf, Y=%.0lf\n", x, y);
}

void mouseButtonPressed(GLFWwindow *pWindow, int button, int action, int mods) {
  printf("Button pressed\n");
}

Vertex2D points[] = {
    {{-1, 0}, {1, 0, 0, 1}},
    {{0, 1}, {0, 1, 0, 1}},
    {{1, 0}, {0, 0, 1, 1}},
};

unsigned int numberOfTriangles = 3;

int main() {
  myWindow.width = 800;
  myWindow.height = 600;
  myWindow.pszWindowTitle = (char *)pszWindowTitle;
  myWindow.clearColors.rgba.red = 0.4;
  myWindow.clearColors.rgba.green = 0.4;
  myWindow.clearColors.rgba.blue = 0.4;
  myWindow.clearColors.rgba.alpha = 1;
  myWindow.cursorPosCallback = mouseMove;
  myWindow.mouseButtonCallback = mouseButtonPressed;

  ShaderSceneRenderer *pRenderer = new ShaderSceneRenderer();

  pRenderer->pWindow = &myWindow;

  // SHADER_WITH_COLOR;// SHADER_WITH_MATRICES;
  pRenderer->shaderType = SHADER_WITH_MATRICES;

  pRenderer->pVertexData = points;
  pRenderer->vertexArrayNumEntries = 3;

  printf("Starting ...\n");

  int windowResult = openGLFWindow(&myWindow, pRenderer);

  destroyGLFWindow(&myWindow);

  return windowResult;
}
