#include "Utils/ErrorMsg.h"

#include "Rendering/Window.h"
#include <glad/glad.h>

namespace Window
{
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        Window *win = static_cast<Window*> (glfwGetWindowUserPointer(window));
        if (win)
        {
            win->width = width;
            win->height = height;
            glViewport(0,0, width, height);
        }
    }

    bool init(Window &window, int width, int height, const char* title)
    {
        if (!glfwInit())
        {
            errorMsg("Failed to initialize GLFW");
            return false;
        }

        window.handle = glfwCreateWindow(width, height, title, NULL, NULL);
        window.width = width;
        window.height = height;
        window.title = title;
        
        if (!window.handle)
        {
            errorMsg("Failed to create GLFW window");
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window.handle);

        // load GLAD immediately after context is current
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            errorMsg("Failed to initialize GLAD");
            glfwDestroyWindow(window.handle);
            glfwTerminate();
            return false;
        }

        glfwSetFramebufferSizeCallback(window.handle, framebuffer_size_callback);

        return true;
    }

    void destroy(Window &window)
    {
        if (window.handle)
            glfwDestroyWindow(window.handle);
        glfwTerminate();
    }

    void swapBuffers(Window &window)
    {
        glfwSwapBuffers(window.handle);
    }

    void pollEvents()
    {
        glfwPollEvents();
    }

    bool shouldClose(Window &window)
    {
        return glfwWindowShouldClose(window.handle);
    }

    GLFWwindow* getHandle(Window &window)
    {
        return window.handle;
    }
}