#include "ContainerTestWindow.h"
#include "Application.h"

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace std;

ContainerTestWindow::ContainerTestWindow()
{
    Rectangle* _rect = new Rectangle(2000, 2000);
    _rect->fillColor_set(Colors::White);
    insertChild(_rect);

    _cont = new Container(500, 500);
    _cont->LayoutGuest.Classic.topLeft(50, 50);
    insertChild(_cont);

    Rectangle* rect = new Rectangle(50, 50);
    rect->fillColor_set(Colors::Green);
    _cont->insertChild(rect);

    Circle* circ = new Circle(300);
    circ->fillColor_set(Colors::Orange);
    circ->LayoutGuest.Classic.topLeft(200, 200);
    _cont->insertChild(circ);

    Circle* _circ2 = new Circle(100);
    _circ2->fillColor_set(Colors::LawnGreen);
    _circ2->LayoutGuest.Classic.topLeft(80, 80);

    Rectangle* rect2 = new Rectangle(100._FPs, 100._FPs);
    rect2->fillColor_set(Colors::Beige);
    rect2->mouseClick +=
        [this](Node*, EventArgs* e)
    {
        _cont2->clipping_set(!_cont2->clipping_get());
    };

    _cont2 = new Container(200, 200);
    _cont2->LayoutGuest.Classic.topLeft(100, 100);
    _cont2->insertChild(rect2);
    _cont2->insertChild(_circ2);
    //_cont2->clipping_set(true);
    _cont->insertChild(_cont2);

    /*mouseMove +=
        [this](Window* sender, MouseEventArgs* e)
    {
        _cont->LayoutGuest.Classic.topLeft(e->Y, e->X);
    };*/

    _cont->clipping_set(true);

    _cont->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        //Application::nativeMsgBox();
    };

    mouseMove +=
        [this](Window* sender, MouseEventArgs* e)
    {
        _cont2->LayoutGuest.Classic.topLeft(e->Y - _cont->getApsoluteOffsetVector().Y, e->X - _cont->getApsoluteOffsetVector().X);
    };

    keyUp +=
        [this](Window* sender, KeyboardEventArgs* e)
    {
        if (e->VirtualKeyCode == VirtualKey::Space)
            _cont2->clipping_set(!_cont2->clipping_get());
    };
}