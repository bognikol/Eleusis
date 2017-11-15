#pragma once

#include "dllexport.h"

#include "event.h"

namespace Eleusis
{
    enum class ELEUSIS_API AnimationRepetition
    {
        Once,
        Forever
    };

    class ELEUSIS_API IAnimation
    {
    public:     virtual ~IAnimation() { };

                virtual bool isRunning() = 0;

                virtual void                repetition_set(AnimationRepetition repetition) = 0;
                virtual AnimationRepetition repetition_get() = 0;

                virtual long long duration_get() = 0;
                virtual long long delay_get() = 0;

                virtual void start()   = 0;
                virtual void stop()    = 0;
                virtual void reset()   = 0;
                virtual void restart() = 0;
                virtual void clear()   = 0;

                Event<IAnimation*, EventArgs*> started;
                Event<IAnimation*, EventArgs*> stopped;
                Event<IAnimation*, EventArgs*> animationParameterChanged;
    };
}
