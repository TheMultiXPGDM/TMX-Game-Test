#include <stdio.h>
#include "Game.h"

namespace Game {
    bool init (GameState &state) {
        // Load config
        
        // Load default first in case any configuration is missing
        Config::loadConfigDefault(state.config);
        // Then load from file if it exists
        Config::loadConfig(state.config, "config.json");
        // Save config
        Config::saveConfig(state.config, "config.json");

        // Window
        if (!Window::init (state.window, state.config.graphics.width, state.config.graphics.height, "TMX Game Test"))
            return false;

        // Renderer
        if (!Renderer::init (state.render))
            return false;

        // Time
        TimeManager::init (state.time);

        // Input
        Input::init(state.input);

        state.player.posX = 0.0f;
        state.player.posY = 0.0f;
        state.player.velX = 0.0f;
        state.player.velY = 0.0f;

        state.running = true;

        return true;
    }

    void run (GameState &state) {
        while (state.running && !Window::shouldClose (state.window)) {
            TimeManager::update (state.time);

            while (TimeManager::getAccumulator(state.time) >= TimeManager::getFixedDeltaTime(state.time)) {
                updateFixed(state, TimeManager::getFixedDeltaTime(state.time));
                state.time.accumulator -= TimeManager::getFixedDeltaTime(state.time);
            }

            updateVariable(state, TimeManager::getDeltaTime(state.time));

            float alpha = TimeManager::getAccumulator(state.time) / TimeManager::getFixedDeltaTime(state.time);

            render(state, alpha);

            Window::swapBuffers (state.window);
            Window::pollEvents ();
        }
    }

    void updateFixed (GameState &state, float deltaTime)
    {
        Input::update(state.window, state.config.input, state.input);
        
        state.player.prevPosX = state.player.posX;
        state.player.prevPosY = state.player.posY;

        state.player.velY -= 16.0f * deltaTime;

        if (state.input.pressed(Input::ButtonFlag::INPUT_JUMP) && state.player.posY <= 0.0)
            state.player.velY = 8.0f;

        float accel = 64.0f * ((float) state.input.down(Input::ButtonFlag::INPUT_MOVE_RIGHT) - (float) state.input.down(Input::ButtonFlag::INPUT_MOVE_LEFT));
        float friction = 8.0f;
        state.player.velX += accel * deltaTime;
        state.player.velX *= exp( -friction * deltaTime );

        state.player.posX += state.player.velX * deltaTime;
        state.player.posY += state.player.velY * deltaTime;

        if (state.player.posY <= 0)
        {
            state.player.posY = 0;
            state.player.velY = 0;
        }
    }

    void updateVariable (GameState &state, float deltaTime)
    {
        
    }

    void render (GameState &state, float alpha)
    {
        Renderer::clearColor (state.render, 0.1f, 0.2f, 0.3f, 1.0f);
        Renderer::setPerspective(state.render, (float) state.window.width, (float) state.window.height, 0.5f, 0.01f, 100.0f);
        Renderer::setView(state.render, state.player.posX, state.player.posY, 10.0f);
        Renderer::drawCircle(state.render, state.player.prevPosX * (1.0f - alpha) + state.player.posX * alpha, state.player.prevPosY * (1.0f - alpha) + state.player.posY * alpha, 0.5f);
    }
}