#pragma once

#include "dllexport.h"

#include <list>

namespace Eleusis
{
    class Animation;

    class ELEUSIS_API AnimationManager
    {
    private:    std::list<Animation*> _animations;

    public:     void updateAll(long long timeStamp);
                void registerAnimation(Animation* animation);
    };
}

