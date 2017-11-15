#pragma once

#include "dllexport.h"

#include "event.h"
#include <map>


namespace Eleusis
{
    enum class ELEUSIS_API TimerRepetition
    {
        Once,
        Forever
    };

    class ELEUSIS_API Timer
    {
    private:    unsigned int _duration = 5000;
                TimerRepetition _repetition = TimerRepetition::Once;
                bool _enabled = true;

                unsigned int _timerID = 0;

    public:      Timer(unsigned int duration = 5000, TimerRepetition repetition = TimerRepetition::Once);
                ~Timer();
                
                void start();
                void stop();

                void         duration_set(unsigned int duration);
                unsigned int duration_get();

                void            repetition_set(TimerRepetition repetition);
                TimerRepetition repetition_get();

                void enabled_set(bool enable);
                bool enabled_get();

                Event<Timer*, EventArgs*> elapsed;
                Event<Timer*, EventArgs*> started;
    };
}
