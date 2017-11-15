#include "StackLayoutTestWindow.h"

using namespace Eleusis;
using namespace Eleusis::Test;


StackLayoutTestWindow::StackLayoutTestWindow()
{
    Eleusis::Rectangle* l_background = new Eleusis::Rectangle(2000, 1200);
    l_background->fillColor_set(Colors::White);
    insertChild(l_background);

    _rect = new Rectangle(FitChildren, FitChildren);
    //_rect->LayoutHost.padding(10, 20, 30, 40);
    _rect->LayoutGuest.Classic.topLeft(30, 30);
    _rect->fillColor_set(Colors::DarkOrchid);
    _rect->LayoutHost.stackAlignment_set(LayoutAlignment::TopLeft);
    _rect->LayoutHost.stackOrientation_set(LayoutOrientation::Vertical);
    insertChild(_rect);

    _rect1 = new Rectangle(50, 150);
    _rect1->fillColor_set(Colors::Aqua);
    _rect1->LayoutGuest.Stack.margin(0, 0, 0, 0);
    _rect->insertChild(_rect1);

    _rect2 = new Rectangle(55, 270);
    _rect2->fillColor_set(Colors::Yellow );
    _rect2->LayoutGuest.Stack.margin(0, 0, 0, 0);
    _rect->insertChild(_rect2);

    _rect3 = new Rectangle(FitChildren, FitChildren);
    _rect3->fillColor_set(Colors::Beige);
    _rect3->LayoutGuest.Stack.margin(70, 33, 53, 13);
    _rect->insertChild(_rect3);

    _rect4 = new Rectangle(500, 20);
    _rect4->fillColor_set(Colors::MediumPurple);
    _rect4->LayoutGuest.Stack.margin(10, 20, 30, 40);
    _rect3->insertChild(_rect4);

    _rect4->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {
        _rect4->height_set(50);
    };
}
