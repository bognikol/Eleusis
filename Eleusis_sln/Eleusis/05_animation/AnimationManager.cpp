#include "AnimationManager.h"
#include "Animation.h"

using namespace Eleusis;
using namespace std;

void AnimationManager::updateAll(long long timeStamp)
{
    list<Animation*> l_animationsToBeRemoved;

    for (auto animation : _animations)
        if (animation->isRunning()) animation->update(timeStamp);
        else l_animationsToBeRemoved.push_back(animation);

    for (auto animation : l_animationsToBeRemoved)
        _animations.remove(animation);

}

void AnimationManager::registerAnimation(Animation* animation)
{ 
    _animations.remove(animation); 
    _animations.push_back(animation); 
}

