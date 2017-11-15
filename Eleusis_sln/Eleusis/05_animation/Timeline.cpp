#include "Timeline.h"
#include "Application.h"

using namespace Eleusis;

Timeline::Timeline()
{
    _animationParameterChangedHandler =
        [this](IAnimation* sender, EventArgs* e)
    {
        raiseEvent animationParameterChanged(sender, nullptr);
    };
}

Timeline::~Timeline()
{
    auto l_animationsCopy = _animations;

    for (auto l_animation : l_animationsCopy)
    {
        _animations.remove(l_animation);
        delete l_animation;
    }
}

void Timeline::_updateDuration()
{
    long long l_duration = 0;

    for (auto l_animation : _animations)
        if (l_animation->repetition_get() == AnimationRepetition::Once)
            if (l_duration < l_animation->delay_get() + l_animation->duration_get())
                l_duration = l_animation->delay_get() + l_animation->duration_get();

    _naturalDuration =  l_duration;
}

void Timeline::addAnimation(IAnimation* animation)
{
    _animations.remove(animation);
    _animations.push_back(animation);

    animation->animationParameterChanged += _animationParameterChangedHandler;

    _updateDuration();
}

void Timeline::removeAnimation(IAnimation* animation)
{
    animation->animationParameterChanged -= _animationParameterChangedHandler;

    _animations.remove(animation);

    _updateDuration();
}

void Timeline::deleteAnimation(IAnimation* animation)
{
    bool l_contains = false;

    for (auto l_animation : _animations)
        if (animation == l_animation)
        {
            l_contains = true;
            break;
        }

    if (l_contains)
    {
        animation->animationParameterChanged -= _animationParameterChangedHandler;
        _animations.remove(animation);
        delete animation;
        _updateDuration();
    }
}

bool Timeline::isRunning()
{
    for (auto animation : _animations)
        if (animation->isRunning())
            return true;

    return false;
}

void Timeline::repetition_set(AnimationRepetition repetition) 
{
    _repetition = repetition; 

    raiseEvent animationParameterChanged(this, nullptr);
}

void Timeline::start()
{
    _startTimeStamp = Application::timestamp() - _progressAtStop;

    for (auto l_animation : _animations)
        l_animation->start();
    if (_repetition == AnimationRepetition::Forever)
    {
        unsigned int l_duration = 0;

        if (_naturalDuration - _progressAtStop > 0)
            l_duration = static_cast<unsigned int>(_naturalDuration - _progressAtStop);

        _repetitionTimer.duration_set(l_duration);
        _repetitionTimer.repetition_set(TimerRepetition::Forever);
        _repetitionTimer.elapsed +=
            [this](Timer* sender, EventArgs* e)
        {
            if (_repetitionTimer.duration_get() != _naturalDuration)
                _repetitionTimer.duration_set(static_cast<unsigned int>(_naturalDuration));

            for (auto l_animation : _animations)
                if (l_animation->repetition_get() == AnimationRepetition::Once)
                {
                    l_animation->reset();
                    l_animation->start();
                }
        };
        _repetitionTimer.start();
    }
};

void Timeline::stop()
{
    if (!isRunning()) return;

    _repetitionTimer.stop();
    _progressAtStop = (Application::timestamp() - _startTimeStamp) % _naturalDuration;
    for (auto l_animation : _animations)
        l_animation->stop();
};

void Timeline::reset()
{
    _repetitionTimer.stop();
    _progressAtStop = 0;
    for (auto l_animation : _animations)
        l_animation->reset();
};

void Timeline::restart()
{
    reset();
    start();
}

void Timeline::clear()
{
    _repetitionTimer.stop();

    _startTimeStamp = 0;
    _progressAtStop = 0;

    for (auto l_animation : _animations)
        l_animation->clear();
}