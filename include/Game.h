#ifndef GAME_H
#define GAME_H

#include "Rendering/Window.h"
#include "Rendering/Renderer.h"
#include "TimeManager.h"

namespace Game {
    struct GameState {
        Window::Window window;
        TimeManager::TimeState time;
        Renderer::RenderState render;
        bool running;
    };
    
    bool init (GameState &state);
    void run (GameState &state);
    void updateFixed (GameState &state, float deltaTime);
    void updateVariable (GameState &state, float deltaTime);
    void render (GameState &state, float alpha);
}

#endif // GAME_H