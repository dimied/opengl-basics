
#include <GL/gl.h>
#include <stdio.h>

char *pszGlErrors[] = {
    "Unacceptable value for an enumeration type",
    "Invalid numeric argument specified.",
    "Invalid operation (in the current state).",
    "Command can cause buffer overflow",
    "Command can cause buffer underflow",
    "Not enough memory to execute the operation.",
    "Framebuffer error"};

#define HAS_CONSECUTIVE_ERROR_ENUMS                 \
    (((GL_INVALID_VALUE - GL_INVALID_ENUM)==1) &&\
    ((GL_INVALID_OPERATION - GL_INVALID_ENUM)==2) &&\
    ((GL_STACK_OVERFLOW - GL_INVALID_ENUM)==3) &&\
    ((GL_STACK_UNDERFLOW - GL_INVALID_ENUM)==4) &&\
    ((GL_OUT_OF_MEMORY - GL_INVALID_ENUM)==5) &&\
    ((GL_INVALID_FRAMEBUFFER_OPERATION - GL_INVALID_ENUM)==6))

void printErrors(char *pszPrefix)
{
    GLenum err = glGetError();

    unsigned int errorOffset = -1;
#if (HAS_CONSECUTIVE_ERROR_ENUMS != 0)
    if (err >= GL_INVALID_ENUM && err <= GL_INVALID_FRAMEBUFFER_OPERATION)
    {
        errorOffset = err - GL_INVALID_ENUM;
    }
#else
    switch (err)
    {
    case GL_INVALID_ENUM:
        errorOffset = 0;
        break;

    case GL_INVALID_VALUE:
        errorOffset = 1;
        break;

    case GL_INVALID_OPERATION:
        errorOffset = 2;
        break;

    case GL_STACK_OVERFLOW:
        errorOffset = 3;
        break;

    case GL_STACK_UNDERFLOW:
        errorOffset = 4;
        break;

    case GL_OUT_OF_MEMORY:
        errorOffset = 5;
        break;

    case GL_INVALID_FRAMEBUFFER_OPERATION:
        errorOffset = 6;
        break;

    case GL_NO_ERROR:
    default:
        return;
    }
#endif

    if (errorOffset >= 0)
    {
        char *pszError = pszGlErrors[errorOffset];

        if (pszPrefix)
        {
            printf("%s:\n", pszPrefix);
        }
        printf("%s:\n", pszError);
    }
}