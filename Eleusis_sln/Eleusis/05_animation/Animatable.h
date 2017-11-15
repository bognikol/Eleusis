#pragma once

#include "dllexport.h"

#include "DefaultAnimation.h"

namespace Eleusis
{
    class ELEUSIS_API IAnimatable
    {
    public:     virtual Animation* animate() = 0;
    };

    template <typename AnimationType, typename Type>
    class Animatable :
        public IAnimatable
    {
    protected:  AnimationType* _animation;

    public:     Animatable()
                {
                    _animation = new AnimationType(static_cast<Type*>(this));
                }

                ~Animatable()
                {
                    delete _animation;
                }

                AnimationType* animate()
                {
                    return _animation;
                };
    };
}



