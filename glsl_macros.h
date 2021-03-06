#ifndef __MY_GLSL_MACROS__
#define __MY_GLSL_MACROS__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Used to write shader programs inline
#ifndef GLSL
#define GLSL(version, A) "#version " #version "\n" #A
#endif

//Used to generate a vertex array
#ifndef GENVERTEXARRAYS
#define GENVERTEXARRAYS(n, id)               \
    if (GLEW_ARB_vertex_array_object)        \
    {                                        \
        glGenVertexArrays(n, id);            \
    }                                        \
    else if (GLEW_APPLE_vertex_array_object) \
    {                                        \
        glGenVertexArraysAPPLE(1, id);       \
    }
#endif

//Used for binding vertex arrays
#ifndef BIND_VERTEX_ARRAY
#define BIND_VERTEX_ARRAY(id)                \
    if (GLEW_ARB_vertex_array_object)        \
    {                                        \
        glBindVertexArray(id);               \
    }                                        \
    else if (GLEW_APPLE_vertex_array_object) \
    {                                        \
        glBindVertexArrayAPPLE(id);          \
    }
#endif

#endif