#ifndef GAME_H
#define GAME_H

#include "Config.h"
#include "Rendering/Window.h"
#include "Rendering/Renderer.h"
#include "Input.h"
#include "TimeManager.h"

namespace Game {
    struct GameState {
        Config::Config config;
        Window::Window window;
        TimeManager::TimeState time;
        Renderer::RenderState render;
        Input::InputContext input;
        bool running;

        struct Player {
            float posX, posY;
            float prevPosX, prevPosY;
            float velX, velY;
        } player;
    };
    
    bool init (GameState &state);
    void run (GameState &state);
    void updateFixed (GameState &state, float deltaTime);
    void updateVariable (GameState &state, float deltaTime);
    void render (GameState &state, float alpha);
}

#endif // GAME_H