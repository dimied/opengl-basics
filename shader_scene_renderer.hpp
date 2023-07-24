#ifndef __SCENE_RENDERER_WITH_SHADERS__
#define __SCENE_RENDERER_WITH_SHADERS__

#include <GL/glew.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
//
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//
#include "gl_shaders.h"
#include "glfw/gl_window.h"
#include "glm_util.h"
#include "glsl.h"
#include "glsl_macros.h"
#include "glsl_util.h"
#include "math_util.h"
#include "scene_renderer.h"

#define ERR_MSG_LEN 512
// function to display 4x4 matrix

class ShaderSceneRenderer : public SceneRenderer {
  GLuint shaderID;
  GLuint vertexArrayID;

public:
  MyWindow *pWindow;

  int shaderType;
  GLuint modelID;
  GLuint viewID;
  GLuint projectionID;

  unsigned int vertexArrayNumEntries;
  Vertex2D *pVertexData;

  char const *pszVertexShader;
  char const *pszFragmentShader;
  float time;

  ShaderSceneRenderer() { time = 0; }

  virtual void init() {
    int exitCode = 0;
    GLchar errorMessage[ERR_MSG_LEN];
    // Create shader program and shaders
    shaderID = glCreateProgram();
    GLuint vID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

    pszVertexShader = getShaderCode(shaderType, VERTEX_SHADER);
    pszFragmentShader = getShaderCode(shaderType, FRAGMENT_SHADER);

    // Load shader source code
    // last parameter is code length, NULL means 0-teminated
    glShaderSource(vID, 1, &pszVertexShader, NULL);
    glShaderSource(fID, 1, &pszFragmentShader, NULL);

    // Compile & check for errors
    glCompileShader(vID);

    GLint stateVS = shaderCompileCheck(vID, &errorMessage[0], ERR_MSG_LEN);
    if (stateVS == GL_FALSE) {
      printf("Failed to compile shader\n%s\n", errorMessage);
      ++exitCode;
      printErrors(0);
    }

    glCompileShader(fID);
    GLint stateFS = shaderCompileCheck(fID, &errorMessage[0], ERR_MSG_LEN);
    if (stateFS == GL_FALSE) {
      printf("Failed to compile shader\n%s\n", errorMessage);
      ++exitCode;
      printErrors(0);
    }

    if (stateVS != GL_FALSE && stateFS != GL_FALSE) {
      // Add shaders to the program
      glAttachShader(shaderID, vID);
      glAttachShader(shaderID, fID);

      // Link the program
      glLinkProgram(shaderID);
      GLint linkStatus =
          programLinkCheck(shaderID, &errorMessage[0], ERR_MSG_LEN);
      if (linkStatus == GL_FALSE) {
        printf("Failed to link shader\n%s\n", errorMessage);
        ++exitCode;
        printErrors(0);
      }

      GLint validateStatus =
          programValidateCheck(shaderID, &errorMessage[0], ERR_MSG_LEN);

      if (validateStatus == GL_FALSE) {
        printf("Failed to validate shader\n%s\n", errorMessage);
        ++exitCode;
        printErrors(0);
      }
    }

    if (exitCode == 0) {
      // Use/execute the program
      glUseProgram(shaderID);
      printErrors(0);

      bindValues();
    }
  }

  void bindValues() {
    GLuint positionID;
    GLuint colorID;
    GLuint bufferID;
    GLuint vertexArrayID;

    // Get locations of variables in the program
    positionID = glGetAttribLocation(shaderID, "position");

    colorID = glGetAttribLocation(shaderID, "color");

    if (shaderType == SHADER_WITH_MATRICES) {
      printf("Use with matrix values... \n");
      modelID = glGetUniformLocation(shaderID, "model");
      viewID = glGetUniformLocation(shaderID, "view");
      projectionID = glGetUniformLocation(shaderID, "projection");
    }

    /*-----------------------------------------------------------------------------
     *  CREATE THE VERTEX ARRAY OBJECT
     *-----------------------------------------------------------------------------*/
    GENVERTEXARRAYS(1, &vertexArrayID);
    BIND_VERTEX_ARRAY(vertexArrayID);

    this->vertexArrayID = vertexArrayID;

    // Generate one buffer
    glGenBuffers(1, &bufferID);
    // Bind it
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    // Send data to GPU using buffer
    glBufferData(GL_ARRAY_BUFFER, vertexArrayNumEntries * sizeof(Vertex2D),
                 pVertexData, GL_STATIC_DRAW);

    // Specify how to handle data in the buffer
    //                    attribute  num   type     normalize   stride   offset
    glVertexAttribPointer(positionID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
                          0);
    // Enable Position Attribute
    glEnableVertexAttribArray(positionID);

    glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
                          (void *)sizeof(vec2));
    glEnableVertexAttribArray(colorID);

    // Unbind both: vertex array object and vertex buffer object
    BIND_VERTEX_ARRAY(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
    printf("Shaders created... \n");
    printErrors(0);
  }

  virtual void draw() {
    if (shaderType == SHADER_WITH_MATRICES) {
      drawWithMatrices();
      return;
    }

    // Set program and bind vertex array
    glUseProgram(shaderID);
    BIND_VERTEX_ARRAY(vertexArrayID);

    drawSingleTriangle();

    // Unbind Vertex Array Object
    BIND_VERTEX_ARRAY(0);
    // Unbind shader(s)
    glUseProgram(0);
  }

  float currentWindowRatio() {
    if (pWindow) {
      return pWindow->width * 1.0 / (pWindow->height * 1.0);
    }
    return 1;
  }

  void drawWithMatrices() {
    time += .005;

    glUseProgram(shaderID);
    BIND_VERTEX_ARRAY(vertexArrayID);

    if (hasView == 0) {
      setView();
    }

    float fieldOfView = M_PI / 3.0f; // 60°
    float windowRatio = currentWindowRatio();
    // printf("Ratio: %.2lf\n", windowRatio);
    float zFar = -10.0f; //- because pointing away from viewer

    // Projection matrix
    glm::mat4 proj = glm::perspective(fieldOfView, windowRatio, 0.1f, zFar);

    // Send data for matrices
    glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));

    // Important! Otherwise we get a matrix with zeros
    glm::mat4 ident = glm::mat4(1.0f);
    int num = 100;

    for (int i = 0; i < num; i++) {
      glm::mat4 scale = glm::scale(ident, glm::vec3(1.0f - (float)i / num));
      float angle = time * M_PI * i / num;
      // around z-axis (0,0,1)
      glm::mat4 rotate = glm::rotate(ident, angle, glm::vec3(0, 0, 1));

      glm::mat4 translate =
          glm::translate(ident, glm::vec3(sin(time), 0.0f, (float)i / num));

      // Model Transformation matrix
      glm::mat4 model = translate * rotate * scale;

      glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
      glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    // Unbind
    BIND_VERTEX_ARRAY(0);
    glUseProgram(0);
  }

  void drawSingleTriangle() {
    // Draw Triangle(s)
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  int hasView = 0;
  glm::mat4 view;
  void setView() {
    float viewer[] = {0, 0, 2};
    float viewAt[] = {0, 0, 0};
    float upVec[] = {0, 1, 0};
    float viewRes[16];
    // View Matrix is defined by: eye position, target, Up Vector
    view =
        glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    float *viewVals = (float *)glm::value_ptr(view);

    lookAtRightHandCM(viewer, viewAt, upVec, viewRes);

    printf("----\n");
    for (int i = 0; i < 4; i++) {
      printf(" %f | %f | %f | %f |\n", viewVals[0], viewVals[4], viewVals[8],
             viewVals[12]);
      ++viewVals;
    }
    printf("----\n");
    viewVals = &viewRes[0];
    for (int i = 0; i < 4; i++) {
      printf(" %f | %f | %f | %f |\n", viewVals[0], viewVals[4], viewVals[8],
             viewVals[12]);
      ++viewVals;
    }
    printf("----\n");
    ++hasView;
  }
};

#endif