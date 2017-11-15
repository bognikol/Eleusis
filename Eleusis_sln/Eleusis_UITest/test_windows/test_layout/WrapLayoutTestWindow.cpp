#include "WrapLayoutTestWindow.h"

using namespace Eleusis;
using namespace Eleusis::Test;

WrapLayoutTestWindow::WrapLayoutTestWindow()
{
    Eleusis::Rectangle* l_background = new Eleusis::Rectangle(2000, 1200);
    l_background->fillColor_set(Colors::Orange);
    insertChild(l_background);

    _rect = new Rectangle(80._FPs, 80._FPs);
    _rect->LayoutGuest.Classic.topLeft(10._FPs, 10._FPs);
    _rect->fillColor_set(Colors::DeepSkyBlue);
    _rect->LayoutHost.wrapOrientation_set(LayoutOrientation::Horizontal);
    insertChild(_rect);

    for (int i = 0; i <= 20; i++)
    {
        Rectangle* l_rect = new Rectangle(rand() % 50 + 50, rand() % 50 + 50);
        l_rect->LayoutGuest.Wrap.margin(20, 20, 20, 20);

        l_rect->fillColor_set(RgbaColor(rand() % 256, rand() % 256, rand() % 256));
        _rect->insertChild(l_rect);
    }



}