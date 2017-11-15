#include "ClassicLayoutTestWindow.h"

using namespace Eleusis;
using namespace Eleusis::Test;

ClassicLayoutTestWindow::ClassicLayoutTestWindow()
{
    Eleusis::Rectangle* l_background = new Eleusis::Rectangle(2000, 1200);
    l_background->fillColor_set(Colors::White);
    insertChild(l_background);

    _rect2 = new Rectangle(40._FPs, 500);
    _rect2->fillColor_set(Colors::Yellow);
    _rect2->LayoutGuest.Classic.top(50);
    _rect2->LayoutGuest.Classic.left(50);
    _rect2->LayoutHost.padding(250, 20._FPs, 100, 70);
    insertChild(_rect2);


    _rect = new Rectangle(100, 100);
    _rect->LayoutGuest.Classic.topLeft(50._FPs, 50._FPs);
    _rect->LayoutGuest.Classic.anchorBottom(50._FPs);
    _rect->LayoutGuest.Classic.anchorLeft(50._FPs);

    _rect->fillColor_set(Colors::OrangeRed);
    _rect2->insertChild(_rect);
}