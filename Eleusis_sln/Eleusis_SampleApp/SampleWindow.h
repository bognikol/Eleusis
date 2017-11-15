#pragma once

#include "Window.h"

#include "Views/HomeView.h"
#include "Views/AnimationView.h"
#include "Views/TextView.h"
#include "Views/EventsView.h"

namespace Eleusis
{
    namespace SampleApp
    {
        class SampleWindow :
            public Window
        {
			HomeView*        _homeView      = nullptr;

			SectionViewBase* _currentView   = nullptr;

			AnimationView*   _animationView = nullptr;
			TextView*        _textView      = nullptr;
			EventsView*      _eventsView    = nullptr;

        public:
            SampleWindow();

        };
    }
}