
#include "examples.h"
#include "glsl_util.h"

const char *pExampleVertexShader = "\n\
#version 330\n\
\n\
in vec3 position;\n\
\n\
void main() {\n\
    gl_Position = vec4(position,1.0);\n\
}";

const char *pExampleFragmentShader = "\n\
#version 330\n\
\n\
out vec4 color;\n\
\n\
void main() {\n\
    color = vec4(0.0, 1.0, 1.0, 1.0);\n\
}";

void genBuffers(
    GLfloat *pVertices,
    GLuint numVertices,
    GLuint *pVAO,
    GLuint *pVBO)
{

    glGenVertexArrays(1, pVAO);
    glBindVertexArray(*pVAO);
    {
        glGenBuffers(1, pVBO);
        glBindBuffer(GL_ARRAY_BUFFER, *pVBO);
        {
            glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(float) * numVertices,
                pVertices,
                GL_STATIC_DRAW);

            glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                0);

            glEnableVertexAttribArray(0);
        }
        // Unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
}

int compileExampleShaders()
{
    GLchar errorMessage[256];
    int exitCode = 0;
    GLuint sid = glCreateProgram();

    if (!sid)
    {
        // some error
        return 1;
    }
    GLuint vsID = glCreateShader(GL_VERTEX_SHADER);

    GLuint fsID = glCreateShader(GL_FRAGMENT_SHADER);
    //*pShaderID = sid;
    // Load shader source code
    glShaderSource(vsID, 1, &pExampleVertexShader, NULL);
    glShaderSource(fsID, 1, &pExampleFragmentShader, NULL);

    // Compile & check for errors
    glCompileShader(vsID);

    GLint stateVS = shaderCompileCheck(vsID, &errorMessage[0], 256);
    if (stateVS == GL_FALSE)
    {
        printf("Failed to compile shader\n%s\n", errorMessage);
        ++exitCode;
    }

    glCompileShader(fsID);
    GLint stateFS = shaderCompileCheck(fsID, &errorMessage[0], 256);
    if (stateFS == GL_FALSE)
    {
        printf("Failed to compile shader\n%s\n", errorMessage);
        ++exitCode;
    }

    if (stateVS != GL_FALSE && stateFS != GL_FALSE)
    {
        // Add shaders to the program
        glAttachShader(sid, vsID);
        glAttachShader(sid, fsID);

        // Link the program
        glLinkProgram(sid);
        GLint linkStatus = programLinkCheck(sid, &errorMessage[0], 256);
        if (linkStatus == GL_FALSE)
        {
            printf("Failed to link shader\n%s\n", errorMessage);
            ++exitCode;
        }

        GLint validateStatus = programValidateCheck(sid, &errorMessage[0], 256);
        if (validateStatus == GL_FALSE)
        {
            printf("Failed to validate shader\n%s\n", errorMessage);
            ++exitCode;
        }
    }

    return exitCode;
}