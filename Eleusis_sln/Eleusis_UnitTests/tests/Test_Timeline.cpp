#include "gtest/gtest.h"

#include "Timeline.h"
#include "Animation_Impls.h"

#include <iostream>

using namespace std;
using namespace Eleusis;
using namespace ::testing;


class TimelineTest : public Test
{
protected:
    Timeline* _timeline = new Timeline();
    Animation* _animation = new RectangleAnimation();
};

TEST_F(TimelineTest, trialTest)
{
    _timeline->addAnimation(_animation);
    _timeline->start();
}