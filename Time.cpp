#include "Time.h"

namespace Engine
{
    double* Time::mDeltaTime = nullptr;
    const int Time::TICKS_PER_SEC = 1;

    Time::Time( double* const dt )
    {
        Time::mDeltaTime = dt;
    }

    Time::~Time()
    {}

    double Time::getTime()
    {
        return glfwGetTime();
    }

    double Time::deltaTime()
    {
        return *mDeltaTime;
    }
}
