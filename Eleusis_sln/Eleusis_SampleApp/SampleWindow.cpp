#include "SampleWindow.h"

using namespace std;
using namespace Eleusis;
using namespace Eleusis::SampleApp;

SampleWindow::SampleWindow()
{
	auto l_backHandler = 
		[this](SectionViewBase* sender, EventArgs* e)
	{
		if (sender->animate()->isRunning() ||
			_homeView->animate()->isRunning())
			return;

		sender->animate()->clear();
		sender->animate()->left.startValue(0._FPs);
		sender->animate()->left.endValue(100._FPs);
		sender->animate()->easing_set(Easing::OutQuint);
		sender->animate()->duration_set(2000);

		_homeView->animate()->clear();
		_homeView->animate()->left.startValue(FractionLength(-100));
		_homeView->animate()->left.endValue(0._FPs);
		_homeView->animate()->duration_set(2000);
		_homeView->animate()->easing_set(Easing::OutQuint);

		sender->animate()->start();
		_homeView->animate()->start();
	};

	_animationView = new AnimationView();
	_animationView->backRequested += l_backHandler;

	_textView = new TextView();
	_textView->backRequested += l_backHandler;

	_eventsView = new EventsView();
	_eventsView->backRequested += l_backHandler;

    _homeView = new HomeView();
	_homeView->setWidthAndHeight(100._FPs, 100._FPs);
	_homeView->optionSelected +=
		[this](HomeView* sender, HomeView::OptionSelectedEventArgs* e)
	{
		if ((_currentView && _currentView->animate()->isRunning()) ||
			_homeView->animate()->isRunning())
			return;
		
		if (_currentView)
			removeChild(_currentView);

		if (e->option == "ANIMATION")
			_currentView = _animationView;
		else if (e->option == "TEXT")
			_currentView = _textView;
		else if (e->option == "EVENTS")
			_currentView = _eventsView;
		else
		{
			_currentView = nullptr;
			return;
		}

		_currentView->setWidthAndHeight(100._FPs, 100._FPs);
		_currentView->LayoutGuest.Classic.topLeft(0, 100._FPs);
		insertChild(_currentView);

		_currentView->animate()->clear();
		_currentView->animate()->left.startValue(100._FPs);
		_currentView->animate()->left.endValue(0._FPs);
		_currentView->animate()->easing_set(Easing::OutQuint);
		_currentView->animate()->duration_set(2000);

		_homeView->animate()->clear();
		_homeView->animate()->left.startValue(0._FPs);
		_homeView->animate()->left.endValue(FractionLength(-100));
		_homeView->animate()->duration_set(2000);
		_homeView->animate()->easing_set(Easing::OutQuint);

		_currentView->animate()->start();
		_homeView->animate()->start();
	};

    insertChild(_homeView);
}