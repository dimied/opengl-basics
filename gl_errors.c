
#include <GL/gl.h>
#include <stdio.h>

const char *pszGlErrors[] = {
    "Invalid value for an enumeration type",
    "Invalid numeric argument specified.",
    "Invalid operation (in the current state).",
    "Command can cause buffer overflow",
    "Command can cause buffer underflow",
    "Not enough memory to execute the operation.",
    "Framebuffer error"};

unsigned int errorOffsets[] = {
    GL_INVALID_ENUM,
    GL_INVALID_VALUE,
    GL_INVALID_OPERATION,
    GL_STACK_OVERFLOW,
    GL_STACK_UNDERFLOW,
    GL_OUT_OF_MEMORY,
    GL_INVALID_FRAMEBUFFER_OPERATION};

#define HAS_CONSECUTIVE_ERROR_ENUMS                     \
    (((GL_INVALID_VALUE - GL_INVALID_ENUM) == 1) &&     \
     ((GL_INVALID_OPERATION - GL_INVALID_ENUM) == 2) && \
     ((GL_STACK_OVERFLOW - GL_INVALID_ENUM) == 3) &&    \
     ((GL_STACK_UNDERFLOW - GL_INVALID_ENUM) == 4) &&   \
     ((GL_OUT_OF_MEMORY - GL_INVALID_ENUM) == 5) &&     \
     ((GL_INVALID_FRAMEBUFFER_OPERATION - GL_INVALID_ENUM) == 6))

void printErrors(char *pszPrefix)
{
    GLenum err = glGetError();

    int errorOffset = -1;

#if (HAS_CONSECUTIVE_ERROR_ENUMS > 0)
    if (err >= GL_INVALID_ENUM && err <= GL_INVALID_FRAMEBUFFER_OPERATION)
    {
        errorOffset = err - GL_INVALID_ENUM;
    }
#else
    for (int i = 0; i < 7; i++)
    {
        if (errorOffsets[i] == err)
        {
            errorOffset = i;
            break;
        }
    }
#endif

    if (errorOffset >= 0)
    {
        const char *pszError = pszGlErrors[errorOffset];

        if (pszPrefix)
        {
            printf("%s", pszPrefix);
        }
        printf("%s:\n", pszError);
    }
}