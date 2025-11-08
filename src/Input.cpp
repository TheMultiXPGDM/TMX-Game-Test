#include "Input.h"

#include <GLFW/glfw3.h>

namespace Input {
    void init (InputContext &context)
    {
        context.curr.buttons = 0;
        context.prev = context.curr;
    }

    void update (Window::Window &window, Config::InputConfig &config, InputContext &context) {
        context.prev = context.curr;
        context.curr.buttons = 0;
        for (auto [key, buttons] : config.key_to_buttons) {
            int keyState = glfwGetKey(window.handle, key);
            if (keyState == GLFW_PRESS) {
                for (auto button : buttons) {
                    context.curr.buttons |= button;
                }
            }
        }
    }
}