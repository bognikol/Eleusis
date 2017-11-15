#include "Timer.h"

#include <Windows.h>

using namespace Eleusis;
using namespace std;

static std::map<UINT_PTR, Timer*> _activeTimers;

void CALLBACK _timerProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ UINT_PTR idEvent, _In_ DWORD dwTime)
{
    auto l_timerIter = _activeTimers.find(idEvent);
    if (l_timerIter == _activeTimers.end()) 
        return;

    Timer* l_timer = l_timerIter->second;
    if (l_timer->repetition_get() == TimerRepetition::Once) 
        l_timer->stop();
    if (l_timer->enabled_get())
        raiseEvent l_timer->elapsed(l_timer, nullptr);
}

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
    if (_timerID == 0)
    {
        _timerID = SetTimer(nullptr, 0, _duration, _timerProc);
        _activeTimers[_timerID] = this;
    }
    else
    {
        SetTimer(nullptr, _timerID, _duration, _timerProc);
    }

    raiseEvent started(this, nullptr);
}

void Timer::stop()
{
    if (_timerID == 0) return;
    KillTimer(nullptr, _timerID);
    _activeTimers.erase(_timerID);
    _timerID = 0;
}

void Timer::duration_set(unsigned int duration)
{
    _duration = duration;

    if (_timerID != 0)
        SetTimer(nullptr, _timerID, _duration, _timerProc);
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