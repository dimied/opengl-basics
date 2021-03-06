
#include "glsl.h"
#include <stdio.h>
#include "glsl_macros.h"

extern ShaderWithColor currentShader;

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

//ID of Vertex Attribute
GLuint positionID;
GLuint colorID;
GLuint bufferID;
GLuint vertexArrayID;

Vertex2D points[] = {
    {{-1, 0}, {1, 0, 0, 1}},
    {{0, 1}, {0, 1, 0, 1}},
    {{1, 0}, {0, 0, 1, 1}},
};

unsigned int numberOfTriangles = 3;

void initShaderForPoints(ShaderWithColor *shaderProg)
{
    //Create shader program and shaders
    GLuint shaderID = glCreateProgram();
    GLuint vID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);
    shaderProg->shaderID = shaderID;

    //Load shader source code
    glShaderSource(vID, 1, &shaderProg->pszVertexShader, NULL);
    glShaderSource(fID, 1, &shaderProg->pszFragmentShader, NULL);

    //Compile & check for errors
    glCompileShader(vID);
    shaderCompilerCheck(vID);
    glCompileShader(fID);
    shaderCompilerCheck(fID);

    //Add shaders to the program
    glAttachShader(shaderID, vID);
    glAttachShader(shaderID, fID);

    //Link the program
    glLinkProgram(shaderID);
    shaderLinkCheck(shaderID);

    //Use/execute the program
    glUseProgram(shaderID);

    //Get locations of variables in the program
    positionID = glGetAttribLocation(shaderID, "position");

    if (shaderProg->withColor)
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

    /*-----------------------------------------------------------------------------
     *  CREATE THE VERTEX BUFFER OBJECT
     *-----------------------------------------------------------------------------*/
    // Generate one buffer
    glGenBuffers(1, &bufferID);
    // Bind it
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    // Send data to GPU using buffer
    glBufferData(GL_ARRAY_BUFFER,
                 numberOfTriangles * sizeof(Vertex2D),
                 points, GL_STATIC_DRAW);

    // Enable Position Attribute
    glEnableVertexAttribArray(positionID);

    if (shaderProg->withColor)
    {
        glEnableVertexAttribArray(colorID);
    }
    // Specify how to handle data in the buffer
    //                    attribute  num   type     normalize   stride   offset
    glVertexAttribPointer(positionID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);
    if (shaderProg->withColor)
    {
        glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)sizeof(vec2));
    }
    // Unbind both: vertex array object and vertex buffer object
    BIND_VERTEX_ARRAY(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawPoints()
{
    //Set program and bind vertex array
    glUseProgram(currentShader.shaderID);
    BIND_VERTEX_ARRAY(vertexArrayID);

    //Draw Triangle(s)
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //Unbind Vertex Array Object
    BIND_VERTEX_ARRAY(0);
    // Unbind shader(s)
    glUseProgram(0);
}
