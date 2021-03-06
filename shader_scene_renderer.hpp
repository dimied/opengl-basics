#ifndef __SCENE_RENDERER_WITH_SHADERS__
#define __SCENE_RENDERER_WITH_SHADERS__

#include <GL/glew.h>
#include <stdio.h>
#include "scene_renderer.h"
#include "glsl.h"
#include "glsl_macros.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderSceneRenderer : public SceneRenderer
{
    GLuint shaderID;
    GLuint vertexArrayID;

public:
    unsigned int vertexArrayNumEntries;
    Vertex2D *pVertexData;

    char const *pszVertexShader;
    char const *pszFragmentShader;
    int withColor;

    virtual void init()
    {
        //Create shader program and shaders
        GLuint shaderID = glCreateProgram();
        GLuint vID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);
        this->shaderID = shaderID;

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

        GLuint positionID;
        GLuint colorID;
        GLuint bufferID;
        GLuint vertexArrayID;

        //Get locations of variables in the program
        positionID = glGetAttribLocation(shaderID, "position");

        if (withColor)
        {
            colorID = glGetAttribLocation(shaderID, "color");
        }

        //9. Unbind Program
        glUseProgram(0);

        /*-----------------------------------------------------------------------------
     *  CREATE THE VERTEX ARRAY OBJECT
     *-----------------------------------------------------------------------------*/
        GENVERTEXARRAYS(1, &vertexArrayID);
        BIND_VERTEX_ARRAY(vertexArrayID);

        this->vertexArrayID = vertexArrayID;

        /*-----------------------------------------------------------------------------
     *  CREATE THE VERTEX BUFFER OBJECT
     *-----------------------------------------------------------------------------*/
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

        if (withColor)
        {
            glEnableVertexAttribArray(colorID);
        }
        // Specify how to handle data in the buffer
        //                    attribute  num   type     normalize   stride   offset
        glVertexAttribPointer(positionID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);
        if (withColor)
        {
            glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)sizeof(vec2));
        }
        // Unbind both: vertex array object and vertex buffer object
        BIND_VERTEX_ARRAY(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        printf("Shaders created... \n");
    }

    virtual void draw()
    {
        //Set program and bind vertex array
        glUseProgram(shaderID);
        BIND_VERTEX_ARRAY(vertexArrayID);

        drawSingleTriangle();

        //Unbind Vertex Array Object
        BIND_VERTEX_ARRAY(0);
        // Unbind shader(s)
        glUseProgram(0);
    }

    void drawSingleTriangle()
    {
        //Draw Triangle(s)
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
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