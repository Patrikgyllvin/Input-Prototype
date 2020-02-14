#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

#include <memory>

namespace Engine
{
    class Time
    {
    public:
        Time( double* const dt );
        ~Time();

        static double getTime();

        static double deltaTime();

        static const int TICKS_PER_SEC;

    private:
        static double* mDeltaTime;
    };
}
#endif // TIME_H
