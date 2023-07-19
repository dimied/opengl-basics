#ifndef __MY_GLSL_CODE__
#define __MY_GLSL_CODE__

#include <GL/glew.h>
#include "gl_errors.h"

/**
  * GLSL
  * attribute : incoming vertex data
  * varying : varying properties passed to next process step(s)
  * uniforms: properties, which can be shared by all vertices
  * 
  * Types:
  *  vec2: 2D vector
  *  vec3: 3D vector
  *  vec4: 4D vector (e.g. a vec3 homogenized)
  *  mat2: 2x2 matrix
  *  mat3: 3x3 matrix
  *  mat4: 4x4 matrix
  * 
  *  Common structure:
  *  void main(void) {
  *     // code
  *     // required final vertex position
  *     gl_Position
  *     // required final pixel color
  *     gl_FragColor
  *  }
  */

/**
 * Simple struct for 2D vectors
 */
typedef struct
{
    float x, y;
} vec2;

typedef struct
{
    float r;
    float g;
    float b;
    float a;
} vec4;

typedef struct
{
    vec2 position;
    vec4 color;
} Vertex2D;

enum ShaderCodeType
{
    VERTEX_SHADER,
    FRAGMENT_SHADER
};

enum ExampleShaders
{
    SIMPLE_SHADER,
    SHADER_WITH_COLOR,
    SHADER_WITH_MATRICES
};

#endif