#include "Slider.h"
#include "SliderDefaultSkin.h"

using namespace Eleusis;
using namespace std;

Slider::Slider()
{
    setSkin(new SliderDefaultSkin());
}

void Slider::minValue_set(double value)
{

}

double Slider::minValue_get()
{
    return 0;
}

void Slider::maxValue_set(double value)
{

}

double Slider::maxValue_get()
{
    return 0;
}

void Slider::value_set(double value)
{

}

double Slider::value_get()
{
    return 0;
}

void Slider::_applySkin()
{
    if (!getSkin()) return;

    insertChild(getSkin()->getTrack());
    insertChild(getSkin()->getThumb());
}