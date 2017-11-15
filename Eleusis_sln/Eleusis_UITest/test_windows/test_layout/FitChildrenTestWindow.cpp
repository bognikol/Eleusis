#pragma once

#include "FitChildrenTestWindow.h"

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace std;


FitChildrenTestWindow::FitChildrenTestWindow()
{
    Rectangle* _back;
    insertChild(_back = new Rectangle(2000, 2000));
    _back->fillColor_set(Colors::White);

    Rectangle* _cont = new Rectangle(500, 500);
    _cont->fillColor_set(Colors::Yellow);
    _cont->LayoutGuest.Classic.topLeft(50, 80);
    _cont->LayoutHost.padding(50, 50, 50, 50);
    insertChild(_cont);

    _child1 = new Rectangle(80, 130);
    _child1->fillColor_set(Colors::Red);
    _cont->insertChild(_child1);

    _child2 = new Rectangle(80, 130);
    _child2->LayoutGuest.Classic.topLeft(90, 50);
    _child2->fillColor_set(Colors::Green);
    /*_cont->*/insertChild(_child2);

    _child3;
    _child4;
    _child5;
    _child6;
    _child7;
}