#include "PseudoSlider.h"
#include "Window.h"
#include "01_to_string/ToString.h"


using namespace Eleusis;
using namespace Eleusis::PseudoControls;
using namespace std;

PseudoSlider::PseudoSlider()
{
    width_set(320);
    height_set(90);

    _valueTextBlock = new TextBlock();
    _valueTextBlock->width_set(320);
    _valueTextBlock->setText(_text + ": " + to_string(_value));
    insertChild(_valueTextBlock);

    _sliderRect = new Rectangle(300, 20);
    _sliderRect->cornerRadius_set(3);
    _sliderRect->LayoutGuest.Classic.top(30);
    _sliderRect->LayoutGuest.Classic.left(10);
    _sliderRect->fillColor_set(Colors::Orange);
    insertChild(_sliderRect);

    _handleRect = new Rectangle(10, 30);
    _handleRect->fillColor_set(Colors::OrangeRed);
    _handleRect->cornerRadius_set(3);
    _handleRect->LayoutGuest.Classic.left(150 - 15);
    _handleRect->LayoutGuest.Classic.top(-5);
    _sliderRect->insertChild(_handleRect);

    _sliderRect->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {
        if (sender != _sliderRect) return;
        double l_position = e->X - _sliderRect->getApsoluteOffsetVector().X;
        _handleRect->LayoutGuest.Classic.left(l_position - 5);
        _value = l_position / 300 * (_max - _min);
        _valueTextBlock->setText(_text + ": " + to_string(_value));
        raiseEvent valueChanged(this, nullptr);
    };

    _handleRect->mouseDown +=
        [this](Node* sender, MouseEventArgs* e)
    {
        _mouseDownOnHandle = true;
    };

    _handleRect->mouseUp +=
        [this](Node* sender, MouseEventArgs* e)
    {
        _mouseDownOnHandle = false;
    };

    this->mouseLeave +=
        [this](Node* sender, MouseEventArgs* e)
    {
        _mouseDownOnHandle = false;
    };

    this->mouseMove +=
        [this](Node* sender, MouseEventArgs* e)
    {
        if (_mouseDownOnHandle)
        {
            double l_position = e->X - _sliderRect->getApsoluteOffsetVector().X;
            if (l_position < 0) l_position = 0;
            if (l_position > 300) l_position = 300;
            _handleRect->LayoutGuest.Classic.left(l_position - 5);
            _value = l_position / 300 * (_max - _min);
            _valueTextBlock->setText(_text + ": " + to_string(_value));
            raiseEvent valueChanged(this, nullptr);
        }
    };
}

void PseudoSlider::setValue(double value)
{
    _value = value;
    _valueTextBlock->setText(_text + ": " + to_string(_value));
}

double PseudoSlider::getValue()
{
    return _value;
}

void PseudoSlider::setMin(double min)
{
    _min = min;
}

double PseudoSlider::getMin()
{
    return _min;
}

void PseudoSlider::setMax(double max)
{
    _max = max;
}

double PseudoSlider::getMax()
{
    return _max;
}

void PseudoSlider::setText(std::string text)
{
    _text = text;
    _valueTextBlock->setText(_text + ": " + to_string(_value));
}

std::string PseudoSlider::getText()
{
    return _text;
}