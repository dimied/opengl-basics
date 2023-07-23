#ifndef __MY_GL_BASICS__
#define __MY_GL_BASICS__

#include <GL/glew.h>
#include <GL/gl.h>

/*
 * Draws indexed vertices.
 */
int bindIndices(
    GLfloat *pVertexData,
    unsigned int *pIndices,
    GLsizei numIndices,
    GLsizei numVerices,
    GLuint *pIndexBufferObject,
    GLuint *pVertexArrayObject,
    GLuint *pVertexBufferObject);

void drawIndices(
    GLuint vertexArrayObject,
    GLuint *pIndexBufferObject,
    GLsizei numIndices);

void enableDepthTest();


#endif