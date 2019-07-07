#include "Caret.h"

#include "Application.h"

using namespace Eleusis;

Caret::Caret()
{
    fillColor_set(_fillColor);
    setWidthAndHeight(0, 1); // this is a woraround because caret is not showing on first click on SelectEdit

    _timer = new Timer(600U, TimerRepetition::Forever);

    _timer->elapsed +=
        [this](Timer* sender, EventArgs* e)
    {
        visibility_set(!visibility_get());
    };

    _timer->start();
}

Caret::~Caret()
{
    delete _timer;
}

void Caret::resetTimer()
{
    visibility_set(true);
    _timer->start();
}

void Caret::hide()
{
    visibility_set(false);
    _timer->stop();
}

void Caret::show()
{
    visibility_set(true);
    _timer->start();
}

