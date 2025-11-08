#ifndef INPUT_H
#define INPUT_H

#include <cstdint>
#include "Rendering/Window.h"
#include "Config.h"

namespace Input {
    // 16 bit flags
    enum ButtonFlag : uint16_t {
        INPUT_JUMP = 1,
        INPUT_MOVE_LEFT = 2,
        INPUT_MOVE_RIGHT = 4,
        INPUT_SHOT = 8
    };

    struct InputState
    {
        // flags
        uint16_t buttons;
        uint16_t cursorX, cursorY;
    };

    struct InputContext {
        InputState curr, prev;

        bool down(ButtonFlag button) const { return curr.buttons & button; }
        bool pressed(ButtonFlag button) const { return curr.buttons & button && !(prev.buttons & button); }
        bool released(ButtonFlag button) const { return !(curr.buttons & button) && prev.buttons & button; }
    };
    
    void init (InputContext &context);
    void update (Window::Window &window, Config::InputConfig &config, InputContext &context);
}

#endif // INPUT_H