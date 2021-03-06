
#include <stdlib.h>
#include <stdio.h>
#include "glfw/glfw_helper.h"

char *pszWindowTitle = "Example";

void drawScene() {

}

int main()
{
    int windowResult = openGLFWindow(1280, 800, pszWindowTitle, &drawScene);

    return windowResult;
}


