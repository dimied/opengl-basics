#include <GL/glew.h>
#include "glsl_util.h"

GLint shaderCompileCheck(
    GLuint id,
    GLchar *pMessageData,
    GLsizei messageDataSize)
{
    GLint comp;
    glGetShaderiv(id, GL_COMPILE_STATUS, &comp);

    if (comp == GL_FALSE && pMessageData && messageDataSize > 0)
    {
        // printf("Failed to compile shader\n");
        glGetShaderInfoLog(id, messageDataSize, 0, pMessageData);
        // printf("%s\n", messageData);
    }
    return comp;
}

GLint programLinkCheck(
    GLuint id,
    GLchar *pMessageData,
    GLsizei messageDataSize)
{
    GLint linkStatus;
    glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE)
    {
        glGetProgramInfoLog(id, messageDataSize, 0, pMessageData);
    }
    return linkStatus;
}

GLint programValidateCheck(
    GLuint id,
    GLchar *pMessageData,
    GLsizei messageDataSize)
{
    GLint linkStatus, validateStatus;
    glValidateProgram(id);
    glGetProgramiv(id, GL_VALIDATE_STATUS, &validateStatus);

    if (validateStatus == GL_FALSE)
    {
        glGetProgramInfoLog(id, messageDataSize, 0, pMessageData);
    }
    return validateStatus;
}