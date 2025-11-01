#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

namespace Window
{
    struct Window {
        GLFWwindow* handle;
        int width;
        int height;
        const char* title;
    };

    bool init(Window &window, int width, int height, const char* title);
    void destroy(Window &window);
    void swapBuffers(Window &window);
    bool shouldClose(Window &window);
    void pollEvents();

    GLFWwindow* getHandle(Window &window);
}

#endif // WINDOW_H