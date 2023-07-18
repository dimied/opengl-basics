
#include <stdio.h>

#include "glsl.h"
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
 * @param id
 */
void shaderLinkCheck(GLuint id)
{
    GLint linkStatus, validateStatus;
    GLchar messageData[256];

    glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE)
    {
        glGetProgramInfoLog(id, sizeof(messageData), 0, &messageData[0]);
        printf("Failed to link shader\n");
        printf("%s\n", messageData);
    }

    glValidateProgram(id);
    
    glGetProgramiv(id, GL_VALIDATE_STATUS, &validateStatus);

    if (linkStatus == GL_FALSE)
    {
        glGetProgramInfoLog(id, sizeof(messageData), 0, &messageData[0]);
        printf("Failed to validate shader\n");
        printf("%s\n", messageData);
    }
}
