#pragma once

#include "dllexport.h"

#include <list>
#include <chrono>

#include "VisualParameters.h"
#include "Colors.h"
#include "Easing.h"
#include "AnimationComponent.h"
#include "01_Vectoring/Length.h"
#include "IAnimation.h"

namespace Eleusis
{   
    class ELEUSIS_API Animation :
		public IAnimation
    {
    protected:      bool      _isRunning = false;
                    long long _progress = 0;
                    long long _effectiveProgress() { return static_cast<long long>(_progress * _scaleFactor); }
                    long long _delayProgress = 0;
                    long long _startTimeStamp = 0;
                    
                    long long _setDuration = 400;
                    long long _effectiveDuration = 400;

					long long _setDelay = 0;
                    long long _effectiveDelay = 0;

                    bool _reverse = false;

                    double _scaleFactor = 1.0;
                    virtual void _setScaling(double scale);

                    std::function<double(double)> _easing = Easing::InOutCubic;
                    AnimationRepetition _repetition = AnimationRepetition::Once;

                    template <typename Type>
                    Type _calculateCurrentValue(AnimationComponent<Type>* component);

                    virtual void _populateDefaultStartValues() = 0;
                    virtual void _updateToCurrentValues()      = 0;

    public:         virtual ~Animation() { };
					
					virtual bool isRunning() { return _isRunning; };

                    virtual void      duration_set(long long duration);
                    virtual long long duration_get() { return _setDuration; };
                    virtual long long effectiveDuration() { return _effectiveDuration; };

                    virtual void                          easing_set(std::function<double(double)> easing);
                    virtual std::function<double(double)> easing_get() { return _easing; };

                    virtual void                repetition_set(AnimationRepetition repetition);
                    virtual AnimationRepetition repetition_get() { return _repetition; };

                    virtual void      delay_set(long long delay);
                    virtual long long delay_get() { return _setDelay; };
                    virtual long long effectiveDelay() { return _effectiveDelay; };

                    virtual void start();
                    virtual void startAfter(long long delay);
                    virtual void stop();
                    virtual void reset();
                    virtual void restart();
                    virtual void reverse();        
                    virtual void clear();
                    
                    virtual void registerAnimation() = 0;
    
                    virtual void update(long long timePoint);

                    virtual void toPoint(long long progress);
                    virtual void toPoint(double    progress);
    };

    template <typename Type>
    Type Animation::_calculateCurrentValue
    (AnimationComponent<Type>* component)
    {
        long long l_progress = _progress % (_effectiveDuration);
        if (_progress == _effectiveDuration) 
            l_progress = _effectiveDuration;

        if (_reverse) l_progress = _effectiveDuration  - l_progress;

        double l_quotient = _easing(static_cast<double>(l_progress) / static_cast<double>(_effectiveDuration));

        return component->startValue() +
            (component->endValue() - component->startValue()) * l_quotient;
    }

	template <>
	Length Animation::_calculateCurrentValue(AnimationComponent<Length>* component);

    template <>
    Vector Animation::_calculateCurrentValue(AnimationComponent<Vector>* component);
    
    template <>
    RgbaColor Animation::_calculateCurrentValue(AnimationComponent<RgbaColor>* component);
}

