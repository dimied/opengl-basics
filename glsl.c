
#include "glsl.h"
#include <stdio.h>
#include "glsl_macros.h"

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
