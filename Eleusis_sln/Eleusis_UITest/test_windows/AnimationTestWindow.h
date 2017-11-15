#pragma once

#include "Window.h"
#include "Timeline.h"
#include "PseudoButton.h"
#include "PseudoTextBox.h"

namespace Eleusis
{
    namespace Test
    {
        class AnimationTestControl :
            public Rectangle
        {
        private:

            TextBlock* _nameTxtBlck;

            PseudoControls::PseudoTextBox* _delayTxtBx;
            PseudoControls::PseudoTextBox* _durationTxtBx;
            PseudoControls::PseudoButton*  _startButton;
            PseudoControls::PseudoButton*  _stopButton;
            PseudoControls::PseudoButton*  _resetButton;
            PseudoControls::PseudoTextBox* _toPointTxtBx;
            PseudoControls::PseudoTextBox* _repetitionTxtBx;

            Animation* _animation;

        public:

            AnimationTestControl(Animation* anim, std::string name = "anim");
        };

        class TimelineTestControl :
            public Rectangle
        {
        private:

            TextBlock* _nameTxtBlck;

            PseudoControls::PseudoButton*  _startButton;
            PseudoControls::PseudoButton*  _stopButton;
            PseudoControls::PseudoButton*  _resetButton;
            PseudoControls::PseudoTextBox* _toPointTxtBx;
            PseudoControls::PseudoTextBox* _repetitionTxtBx;

            Timeline* _animation;

        public:

            TimelineTestControl(Timeline* anim, std::string name = "anim");
        };

        class AnimationTestWindow :
            public Eleusis::Window
        {
        public:
            AnimationTestWindow();

        private:
            Eleusis::Rectangle* l_background;

            Eleusis::Rectangle* _rectangle1;
            Eleusis::Rectangle* _rectangle2;
            Eleusis::Rectangle* _rectangle3;

            Eleusis::RectangleAnimation* _rectAnimation1;
            Eleusis::RectangleAnimation* _rectAnimation2;
            Eleusis::RectangleAnimation* _rectAnimation3;

            Eleusis::Timeline* _timeline1;
            Eleusis::Timeline* _timeline2;

            Eleusis::Test::AnimationTestControl* _animationControl1;
            Eleusis::Test::AnimationTestControl* _animationControl2;
            Eleusis::Test::AnimationTestControl* _animationControl3;
            Eleusis::Test::TimelineTestControl* _timelineControl1;
            Eleusis::Test::TimelineTestControl* _timelineControl2;

            Circle* _circle = nullptr;
        };
    }
}


