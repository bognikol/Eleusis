#include "SliderTestWindow.h"

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace std;

SliderTestWindow::SliderTestWindow()
{
    Rectangle* _background = new Rectangle(2000, 2000);
    _background->fillColor_set(Colors::White);
    insertChild(_background);

    _slider = new Slider();
    _slider->LayoutGuest.Classic.topLeft(50, 50);
    insertChild(_slider);
}