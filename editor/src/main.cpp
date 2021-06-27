
#include "window.hpp"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>


int main(void)
{
    Bubble::Window window;

    while (!window.ShouldClose())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        window.SwapBuffer();
    }
    return 0;
}