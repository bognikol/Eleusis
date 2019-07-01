#include "SampleWindow.h"

#include "Application.h"

using namespace Eleusis;
using namespace std;

SampleWindow::SampleWindow()
{
    Rectangle* l_background = new Rectangle(2000, 2000);
    l_background->fillColor_set(Colors::White);
    insertChild(l_background);

    _rect = new Rectangle(100, 200);
    _rect->fillColor_set(Colors::YellowGreen);
    _rect->LayoutGuest.Classic.topLeft(100, 100);
    insertChild(_rect);

    _circ = new Circle(40);
    _circ->fillColor_set(Colors::RoyalBlue);
    _circ->LayoutGuest.Classic.topLeft(100, 300);
    _circ->shadowBrush_set(shared_ptr<Brush>(new SolidColorBrush(Colors::Black)));
    _circ->shadowDistance_set({ 10, 10 });
    _circ->shadowOpacity_set(0.5);
    _circ->opacity_set(0.5);
    insertChild(_circ);

    _rect->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {
        //Application::nativeMsgBox("Bingo rect");

        if (e->Button == MouseButton::Left)
        {
            _rect->animate()->width.endValue(500);
            _rect->animate()->restart();
        }
        else
        {
            _rect->animate()->cornerRadius.startValue(20);
            _rect->animate()->cornerRadius.endValue(0);
            _rect->animate()->restart();
        }
    };

    _circ->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {


        _circ->animate()->radius.endValue(100);
        _circ->animate()->restart();
    };

    mouseMove +=
        [this](Window* sender, MouseEventArgs* e)
    {
        _circ->LayoutGuest.Classic.topLeft(e->Y, e->X);
    };
}

SampleWindow::~SampleWindow()
{
}