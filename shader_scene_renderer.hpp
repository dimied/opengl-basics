#ifndef __SCENE_RENDERER_WITH_SHADERS__
#define __SCENE_RENDERER_WITH_SHADERS__

#include <GL/glew.h>
#include <stdio.h>
#include <math.h>
#include "scene_renderer.h"
#include "glsl.h"
#include "glsl_macros.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glfw/gl_window.h"
#include <iostream>

// function to display 4x4 matrix

class ShaderSceneRenderer : public SceneRenderer
{
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

    ShaderSceneRenderer()
    {
        time = 0;
    }

    virtual void init()
    {
        //Create shader program and shaders
        shaderID = glCreateProgram();
        GLuint vID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

        pszVertexShader = getShaderCode(shaderType, VERTEX_SHADER);
        pszFragmentShader = getShaderCode(shaderType, FRAGMENT_SHADER);

        //Load shader source code
        glShaderSource(vID, 1, &pszVertexShader, NULL);
        glShaderSource(fID, 1, &pszFragmentShader, NULL);

        //Compile & check for errors
        glCompileShader(vID);
        shaderCompilerCheck(vID);
        printErrors(0);
        glCompileShader(fID);
        shaderCompilerCheck(fID);
        printErrors(0);

        //Add shaders to the program
        glAttachShader(shaderID, vID);
        glAttachShader(shaderID, fID);

        //Link the program
        glLinkProgram(shaderID);
        shaderLinkCheck(shaderID);
        printErrors(0);

        //Use/execute the program
        glUseProgram(shaderID);
        printErrors(0);

        GLuint positionID;
        GLuint colorID;
        GLuint bufferID;
        GLuint vertexArrayID;

        //Get locations of variables in the program
        positionID = glGetAttribLocation(shaderID, "position");

        colorID = glGetAttribLocation(shaderID, "color");

        if (shaderType == SHADER_WITH_MATRICES)
        {
            modelID = glGetUniformLocation(shaderID, "model");
            viewID = glGetUniformLocation(shaderID, "view");
            projectionID = glGetUniformLocation(shaderID, "projection");
            printf("Matrix values... \n");
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
        glBufferData(GL_ARRAY_BUFFER,
                     vertexArrayNumEntries * sizeof(Vertex2D),
                     pVertexData, GL_STATIC_DRAW);

        // Enable Position Attribute
        glEnableVertexAttribArray(positionID);

        glEnableVertexAttribArray(colorID);
        // Specify how to handle data in the buffer
        //                    attribute  num   type     normalize   stride   offset
        glVertexAttribPointer(positionID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);

        glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)sizeof(vec2));

        // Unbind both: vertex array object and vertex buffer object
        BIND_VERTEX_ARRAY(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(0);
        printf("Shaders created... \n");
        printErrors(0);
    }

    virtual void draw()
    {
        if (shaderType == SHADER_WITH_MATRICES)
        {
            drawWithMatrices();
            return;
        }

        //Set program and bind vertex array
        glUseProgram(shaderID);
        BIND_VERTEX_ARRAY(vertexArrayID);

        drawSingleTriangle();

        //Unbind Vertex Array Object
        BIND_VERTEX_ARRAY(0);
        // Unbind shader(s)
        glUseProgram(0);
    }

    float currentWindowRatio()
    {
        if (pWindow)
        {
            return pWindow->width * 1.0 / (pWindow->height * 1.0);
        }
        return 1;
    }

    void drawWithMatrices()
    {
        time += .005;

        glUseProgram(shaderID);
        BIND_VERTEX_ARRAY(vertexArrayID);

        // View Matrix is defined by: eye position, target, Up Vector
        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        float windowRatio = currentWindowRatio();
        //printf("Ratio: %.2lf\n", windowRatio);

        float fovy = M_PI / 3.0f;
        // Projection matrix
        glm::mat4 proj = glm::perspective(fovy, windowRatio, 0.1f, -10.0f);

        // Send data for matrices
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));

        // Important! Otherwise we get a matrix with zeros
        glm::mat4 ident = glm::mat4(1.0f);
        int num = 300;

        for (int i = 0; i < num; i++)
        {
            glm::mat4 scale = glm::scale(ident, glm::vec3(1.0f - (float)i / num));
            float angle = time * M_PI * i / num;
            glm::mat4 rotate = glm::rotate(ident, angle, glm::vec3(0, 0, 1));

            glm::mat4 translate = glm::translate(ident, glm::vec3(sin(time), 0, (float)i / num));

            // Model Transformation matrix
            glm::mat4 model = translate * rotate * scale;

            glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        // Unbind
        BIND_VERTEX_ARRAY(0);
        glUseProgram(0);
    }

    void drawSingleTriangle()
    {
        //Draw Triangle(s)
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    void display_4x4(const glm::mat4& m4)
    {
        //std::cout << tag << '\n';
        for (int col = 0; col < 4; ++col)
        {
            std::cout << "| ";
            for (int row = 0; row < 4; ++row)
            {
                std::cout << m4[row][col] << '\t';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    /**
 * Checks compilation errors
 */
    void shaderCompilerCheck(GLuint id)
    {
        GLint comp;
        glGetShaderiv(id, GL_COMPILE_STATUS, &comp);

        if (comp == GL_FALSE)
        {
            printf("Failed to compile shader\n");
            GLchar messageData[256];
            glGetShaderInfoLog(id, sizeof(messageData), 0, &messageData[0]);
            printf("%s\n", messageData);
        }
    }

    /**
 * Checks shader link errors
 */
    void shaderLinkCheck(GLuint ID)
    {
        GLint linkStatus, validateStatus;
        glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);

        if (linkStatus == GL_FALSE)
        {
            printf("Failed to link shader\n");
            GLchar messageData[256];
            glGetProgramInfoLog(ID, sizeof(messageData), 0, &messageData[0]);
            printf("%s\n", messageData);
        }

        glValidateProgram(ID);
        glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);

        if (linkStatus == GL_FALSE)
        {
            printf("Failed to validate shader\n");
            GLchar messageData[256];
            glGetProgramInfoLog(ID, sizeof(messageData), 0, &messageData[0]);
            printf("%s\n", messageData);
        }
    }
};

#endif