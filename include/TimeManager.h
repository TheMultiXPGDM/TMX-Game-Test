#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

namespace TimeManager
{
    struct TimeState {
        double currentTime;
        double previousTime;
        float deltaTime;
        float accumulator;
        float fixedTimeStep;
    };

    void init(TimeState& time);
    void update(TimeState& time);
    float getDeltaTime(const TimeState& time);
    float getFixedDeltaTime(const TimeState& time);
    float getCurrentTime(const TimeState& time);
    float getAccumulator(const TimeState& time);
    void setFixedTimeStep(TimeState& time, float timeStep);
}

#endif // TIMEMANAGER_H