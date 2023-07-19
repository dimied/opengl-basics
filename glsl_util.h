#ifndef __MY_GLSL_UTIL__
#define __MY_GLSL_UTIL__

#include <GL/glew.h>

GLint shaderCompileCheck(
    GLuint id,
    GLchar *pMessageData,
    GLsizei messageDataSize);

GLint programLinkCheck(
    GLuint id,
    GLchar *pMessageData,
    GLsizei messageDataSize);

GLint programValidateCheck(
    GLuint id,
    GLchar *pMessageData,
    GLsizei messageDataSize);
#endif