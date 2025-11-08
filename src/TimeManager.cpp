#include "TimeManager.h"

#include <GLFW/glfw3.h>

namespace TimeManager {
    void init(TimeState& time) {
        time.currentTime = 0.0f;
        time.previousTime = 0.0f;
        time.deltaTime = 0.0f;
        time.accumulator = 0.0f;
        time.fixedTimeStep = 1.0f / 100.0f; // 100 updates per second

        time.previousTime = glfwGetTime();
    }

    void update(TimeState& time) {
        time.currentTime = glfwGetTime();
        time.deltaTime = (float) (time.currentTime - time.previousTime);
        time.previousTime = time.currentTime;
        time.accumulator += time.deltaTime;
    }

    float getDeltaTime(const TimeState& time) {
        return time.deltaTime;
    }

    double getCurrentTime(const TimeState& time) {
        return time.currentTime;
    }

    float getAccumulator(const TimeState& time) {
        return time.accumulator;
    }

    float getFixedDeltaTime(const TimeState& time) {
        return time.fixedTimeStep;
    }

    void setFixedTimeStep(TimeState& time, float timeStep) {
        time.fixedTimeStep = timeStep;
    }
};