#include "Animation.h"
#include "Application.h"
#include <cmath>

using namespace Eleusis;

void Animation::_setScaling(double scale)
{
    if (scale <= 0) return;

    _scaleFactor = scale;
    _effectiveDuration = static_cast<long long>(_setDuration * _scaleFactor);
    _effectiveDelay    = static_cast<long long>(_setDelay    * _scaleFactor);
}

void Animation::duration_set(long long duration) 
{ 
    if (duration <= 0) return;

    _setDuration = duration;
    _effectiveDuration = static_cast<long long>(duration * _scaleFactor);

    raiseEvent animationParameterChanged(this, nullptr);
}

void Animation::easing_set(std::function<double(double)> easing) 
{ 
    _easing = easing;

    raiseEvent animationParameterChanged(this, nullptr);
}

void Animation::repetition_set(AnimationRepetition repetition) 
{ 
    _repetition = repetition; 

    raiseEvent animationParameterChanged(this, nullptr);
}

void Animation::delay_set(long long delay) 
{ 
    if (delay < 0) delay = 0; 

    _setDelay = delay; 
    _effectiveDelay = static_cast<long long>(delay * _scaleFactor);

    raiseEvent animationParameterChanged(this, nullptr);
}

void Animation::start() 
{ 
    _isRunning = true; 
    _startTimeStamp = Application::timestamp() - _progress - _delayProgress;

    if (_progress == 0)
        _populateDefaultStartValues();

    registerAnimation(); 
    raiseEvent started(this, nullptr);
}

void Animation::startAfter(long long delay)
{ 
    if (_progress != 0) return;

    delay_set(delay); 
    start(); 
}

void Animation::stop() 
{ 
    if (!_isRunning) return;

    _isRunning = false; 
    raiseEvent stopped(this, nullptr); 
}

void Animation::reset() 
{ 
    if (_reverse) reverse(); // reverse again to undo reverse
    
    stop();

    _progress = 0;
    _delayProgress = 0;

    _populateDefaultStartValues();
    _updateToCurrentValues();
}

void Animation::restart()
{
    reset();
    start();
}

void  Animation::reverse()
{
    _reverse = !_reverse;

    if (_progress <= _effectiveDuration)
    {
        _progress = _effectiveDuration - _progress;
        _startTimeStamp = Application::timestamp() - _progress - _effectiveDelay;
    }
}

void Animation::clear()
{
    if (_reverse) reverse(); // reverse again to undo reverse

    stop();

    _progress = 0;
    _delayProgress = 0;
}

void Animation::update(long long timePoint)
{
    _delayProgress = timePoint - _startTimeStamp;

    if (!_isRunning || _delayProgress < _effectiveDelay) return;

    _delayProgress = _effectiveDelay;

    _progress = timePoint - _startTimeStamp - _effectiveDelay;
    if (_repetition == AnimationRepetition::Once)
    {
        if (_progress >= _effectiveDuration)
        {
            _progress = _effectiveDuration;
            stop();
        }
    }

    //if (!_isRunning || _delayProgress < _effectiveDelay) return;

    _updateToCurrentValues();
}

void Animation::toPoint(long long progress)
{
    switch (_repetition)
    {
        case AnimationRepetition::Once: 
        {
            if (progress <= 0) _progress = 0;
            else if (progress > _effectiveDuration) _progress = _effectiveDuration;
            else _progress = static_cast<long long>(progress * _scaleFactor);
            break;
        }
        case AnimationRepetition::Forever:
        {
            if (progress <= 0) _progress = 0;
            else _progress = static_cast<long long>((progress % _effectiveDuration) * _scaleFactor);
            break;
        }
    }
    _delayProgress = _effectiveDelay;

    _populateDefaultStartValues();
    _updateToCurrentValues();
}

void Animation::toPoint(double progress)
{
    switch (_repetition)
    {
        case AnimationRepetition::Once:
        {
            if (progress <= 0) _progress = 0;
            else if (progress > 1.0) _progress = _effectiveDuration;
            else _progress = static_cast<long long>(progress * _effectiveDuration);
        }
        case AnimationRepetition::Forever:
        {
            double l_dummyDouble;
            progress = std::modf(progress, &l_dummyDouble);
            if (progress < 0) progress += 1.0;
            _progress = static_cast<long long>(progress * _effectiveDuration);
        }
    }

    _populateDefaultStartValues();
    _updateToCurrentValues();
}

template <>
Length Animation::_calculateCurrentValue
(AnimationComponent<Length>* component)
{
	double l_startValue = component->startValue();
	double l_endValue = component->endValue();

	long long l_progress = _progress % (_effectiveDuration);
	if (_progress == _effectiveDuration)
		l_progress = _effectiveDuration;

	if (_reverse) l_progress = _effectiveDuration - l_progress;

	double l_quotient = _easing(static_cast<double>(l_progress) / static_cast<double>(_effectiveDuration));

	double l_returnValue = l_startValue + (l_endValue - l_startValue) * l_quotient;

	if (component->endValue().getType() == PointType::Fraction)
		return FractionLength(l_returnValue);

	return DeviceIndependentLength(l_returnValue);
}

template <>
Vector Animation::_calculateCurrentValue
(AnimationComponent<Vector>* component)
{
    Vector l_returnVector;
    
    long long l_progress = _progress % (_effectiveDuration);
    if (_progress == _effectiveDuration)
        l_progress = _effectiveDuration;
    
    if (_reverse) l_progress = _effectiveDuration - l_progress;
    
    double l_quotient = _easing(static_cast<double>(l_progress) / static_cast<double>(_effectiveDuration));
    
    l_returnVector.X = component->startValue().X + (component->endValue().X - component->startValue().X) * l_quotient;
    l_returnVector.Y = component->startValue().Y + (component->endValue().Y - component->startValue().Y) * l_quotient;
    
    return l_returnVector;
}

template <>
RgbaColor Animation::_calculateCurrentValue
(AnimationComponent<RgbaColor>* component)
{
    RgbaColor l_returnColor;
    
    long long l_progress = _progress % (_effectiveDuration);
    if (_progress == _effectiveDuration)
        l_progress = _effectiveDuration;
    
    if (_reverse) l_progress = _effectiveDuration - l_progress;
    
    double l_quotient = _easing(static_cast<double>(l_progress) / static_cast<double>(_effectiveDuration));
    
    l_returnColor.R_set(component->startValue().R_get() + (component->endValue().R_get() - component->startValue().R_get()) * l_quotient);
    l_returnColor.G_set(component->startValue().G_get() + (component->endValue().G_get() - component->startValue().G_get()) * l_quotient);
    l_returnColor.B_set(component->startValue().B_get() + (component->endValue().B_get() - component->startValue().B_get()) * l_quotient);
    l_returnColor.A_set(component->startValue().A_get() + (component->endValue().A_get() - component->startValue().A_get()) * l_quotient);
    
    return l_returnColor;
}
