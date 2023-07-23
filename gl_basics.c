
#include "gl_basics.h"

int bindIndices(
    GLfloat *pVertexData,
    unsigned int *pIndices,
    GLsizei numIndices,
    GLsizei numVerices,
    GLuint *pIndexBufferObject,
    GLuint *pVertexArrayObject,
    GLuint *pVertexBufferObject)
{
    glGenVertexArrays(1, pVertexArrayObject);
    glBindVertexArray(*pVertexArrayObject);

    glGenBuffers(1, pIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pIndexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 numIndices * 4,
                 pIndexBufferObject,
                 GL_STATIC_DRAW);

    glGenBuffers(1, pVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, *pVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER,
                 numVerices * 4,
                 pVertexBufferObject,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return 0;
}

void drawIndices(
    GLuint vertexArrayObject,
    GLuint *pIndexBufferObject,
    GLsizei numIndices)
{
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pIndexBufferObject);

    glDrawElements(GL_FLOAT, numIndices, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void enableDepthTest() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}