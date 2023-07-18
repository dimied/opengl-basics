
#include "opengl3.h"
#include "glfw/glfw_helper.h"
#include <GL/gl.h>

extern MyWindow myWindow;

void drawSingleTriangle()
{
    // Draw triangle using direct-mode rendering (glBegin, glEnd)
    // This has been deprecated since OpenGL 3
    glBegin(GL_TRIANGLES);
    // top corner
    glColor3f(1, 0, 0);
    glVertex3f(0, 1, 0);
    // right corner
    glColor3f(0, 1, 0);
    glVertex3f(1, 0, 0);
    // left corner
    glColor3f(0, 0, 1);
    glVertex3f(-1, 0, 0);
    glEnd();
}

float counter = 0.0;

void drawRotatingTriangle()
{
    counter += .01;

    int width = myWindow.width;
    int height = myWindow.height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-(float)width / height, (float)width / height, -1.f, 1.f, 1.f, -1.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < 10; ++i)
    {
        float t = (float)i / 10;
        glPushMatrix();

        // scale, then rotate, then Translate
        // glTranslatef(t * sin(counter), 0, 0);
        glRotatef(360 * t * counter, 0, 0, 1);
        // glScalef(1 - t, 1 - t, 1 - t);

        drawSingleTriangle();

        glPopMatrix();
    }
}