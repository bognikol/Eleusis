#ifdef __APPLE__

#include "Timer.h"

using namespace Eleusis;
using namespace std;

Timer::Timer(unsigned int duration, TimerRepetition repetition) :
    _duration(duration),
    _repetition(repetition)
{
}

Timer::~Timer()
{
    stop();
}

void Timer::start()
{
    raiseEvent started(this, nullptr);
}

void Timer::stop()
{
}

void Timer::duration_set(unsigned int duration)
{
    _duration = duration;
}

unsigned int Timer::duration_get()
{
    return _duration;
}

void Timer::repetition_set(TimerRepetition repetition)
{
    _repetition = repetition;
}

TimerRepetition Timer::repetition_get()
{
    return _repetition;
}

void Timer::enabled_set(bool enable)
{
    _enabled = enable;
}

bool Timer::enabled_get()
{
    return _enabled;
}

#endif