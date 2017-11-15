#pragma once

#include "dllexport.h"

#include "Animation.h"
#include "Timer.h"

#include <list>

namespace Eleusis
{
    class ELEUSIS_API Timeline :
        public IAnimation
    {
    private:    std::list<IAnimation*> _animations;

                Timer _repetitionTimer;
                long long _startTimeStamp = 0;
                long long _progressAtStop = 0;
                    
                AnimationRepetition _repetition = AnimationRepetition::Once;

                long long _naturalDuration = 0;
                void _updateDuration();

                Handler<IAnimation*, EventArgs*> _animationParameterChangedHandler;

    public:     Timeline();
                virtual ~Timeline();
        
                void addAnimation(IAnimation* animation);
                void removeAnimation(IAnimation* animation);
                void deleteAnimation(IAnimation* animation);
        
                virtual bool isRunning();

                virtual long long duration_get() { return _naturalDuration; };
                virtual long long delay_get() { return 0; };

                virtual void repetition_set(AnimationRepetition repetition);
                virtual AnimationRepetition repetition_get() { return _repetition; };

                virtual void start();
                virtual void stop() ;
                virtual void reset();
                virtual void restart();
                virtual void clear();
    };
}

