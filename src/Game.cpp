#include "Utils/errorMsg.h"
#include "Game.h"

namespace Game {
    
    bool init (GameState &state) {
        // Window
        if (!Window::init (state.window, 1280, 720, "TMX Game Test"))
            return false;

        // Renderer
        if (!Renderer::init (state.render))
            return false;

        // Time
        TimeManager::init (state.time);

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
        
    }

    void updateVariable (GameState &state, float deltaTime)
    {

    }

    void render (GameState &state, float alpha)
    {
        Renderer::clearColor (state.render, 0.1f, 0.2f, 0.3f, 1.0f);
        Renderer::drawCircle(state.render, 0.0f, 0.0f, 0.5f);
    }
}