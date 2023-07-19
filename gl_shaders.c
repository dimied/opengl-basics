#include "glsl.h"

#include "glsl_macros.h"
#include "gl_shaders.h"

const char *vertexShaderCode = GLSL(
    120,
    // for versions 130 and above it should be "in" instead of "attribute"
    attribute vec4 position;

    void main() {
        gl_Position = position;
    });

const char *fragmentShaderCode = GLSL(
    120,
    void main() {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    });

const char *vertexShaderWithColor = GLSL(
    120,

    attribute vec4 position;
    attribute vec4 color;

    varying vec4 dstColor;

    void main() {
        dstColor = color;
        gl_Position = position;
    }

);

const char *fragmentShaderWithColor = GLSL(
    120,

    varying vec4 dstColor;

    void main() {
        gl_FragColor = dstColor;
    }

);

const char *vertexShaderAllMatrices = GLSL(
    120,

    attribute vec4 position;
    attribute vec4 color;

    varying vec4 dstColor;

    // Matrices for transformations
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        dstColor = color;
        gl_Position = projection * view * model * position;
    }

);

const char *fragmentShaderAllMatrices = GLSL(
    120,
    varying vec4 dstColor;

    void main() {
        gl_FragColor = dstColor;
    }

);

const char *getShaderCode(int id, int type)
{
    switch (id)
    {
    case SIMPLE_SHADER:
        return type == VERTEX_SHADER
                   ? vertexShaderCode
                   : fragmentShaderCode;
    case SHADER_WITH_COLOR:
        return type == VERTEX_SHADER
                   ? vertexShaderWithColor
                   : fragmentShaderWithColor;
    case SHADER_WITH_MATRICES:
        return type == VERTEX_SHADER
                   ? vertexShaderAllMatrices
                   : fragmentShaderAllMatrices;
    default:
        break;
    }
    return 0;
}