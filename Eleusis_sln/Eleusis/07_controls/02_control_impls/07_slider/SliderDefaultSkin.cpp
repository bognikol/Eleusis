#include "SliderDefaultSkin.h"

using namespace Eleusis;
using namespace std;

SliderDefaultSkin::SliderDefaultSkin()
{
    Circle* l_thumb = new Circle(5);
    l_thumb->fillColor_set(Colors::Gray);
    l_thumb->LayoutGuest.Classic.topLeft(20, 20);
    _thumb = l_thumb;

    _track = new Line(100, 0);
    _track->lineThickenss_set(1);
    _track->LayoutGuest.Classic.topLeft(25.5, 25);
    _track->lineColor_set(Colors::Black);

    _thumb->mouseEnter +=
        [this](Node* sender, EventArgs* e)
    {
        Circle* l_thumb = static_cast<Circle*>(_thumb);

        //l_thumb->fillColor_set(Colors::RoyalBlue());
        l_thumb->animate()->radius.endValue(10);
        l_thumb->animate()->radius.startValue(5);
        l_thumb->animate()->start();
    };

    _thumb->mouseLeave +=
        [this](Node* sender, EventArgs* e)
    {
        Circle* l_thumb = static_cast<Circle*>(_thumb);

        l_thumb->fillColor_set(Colors::Gray);
        l_thumb->animate()->radius.endValue(5);
        l_thumb->animate()->start();
    };

    _thumb->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        Circle* l_thumb = static_cast<Circle*>(_thumb);

        _track->animate()->lineColor.endValue(Colors::Red);
        _track->animate()->start();
    };
}
