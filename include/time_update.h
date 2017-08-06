#include <chrono>
#include <iostream>

namespace Time
{
    using namespace std;

    typedef chrono::high_resolution_clock Clock;

    static Clock::time_point initTime;
    static Clock::time_point lastFrameTime;
    static Clock::time_point currentFrameTime;

    static Clock::duration deltaDuration;
    static float deltaTime = 0.0;
    static float scaledDeltaTime = 0.0;
    static float scale = 1.0;

    static void InitTime()
    {
        initTime = Clock::now();
        lastFrameTime = initTime;
        currentFrameTime = initTime;
    }

    static void UpdateTime()
    {
        lastFrameTime = currentFrameTime;
        currentFrameTime = Clock::now();
        deltaDuration = (currentFrameTime - lastFrameTime);
        deltaTime = (float)chrono::duration_cast<chrono::microseconds>(deltaDuration).count() / 1e6f;
        scaledDeltaTime = deltaTime * scale;
    }
}