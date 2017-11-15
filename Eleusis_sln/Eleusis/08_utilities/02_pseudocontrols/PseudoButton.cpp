#include "PseudoButton.h"

using namespace Eleusis;
using namespace Eleusis::PseudoControls;
using namespace std;

PseudoButton::PseudoButton()
{
    _textBlock = new TextBlock();
    _textBlock->setText("PseudoButton");
    _textBlock->foregroundColor_set(Colors::Black);
    _textBlock->LayoutGuest.Classic.top(5);
    _textBlock->width_set(130);
    _textBlock->paragraphAligment_set(ParagraphAlignment::Center);

    width_set(130);
    height_set(30);
    cornerRadius_set(5);
    fillColor_set(Colors::LightGray);
    insertChild(_textBlock);

    mouseEnter +=
        [this](Node* sender, MouseEventArgs* e)
    {
        fillColor_set(Colors::LightBlue);
    };

    mouseLeave +=
        [this](Node* sender, MouseEventArgs* e)
    {
        fillColor_set(Colors::LightGray);
    };

    /*mouseDown +=
        [this](Node* sender, MouseEventArgs* e)
    {
        LayoutGuest.Classic.top(getRelativeOffsetVector().Y + 1);
    };

    mouseUp +=
        [this](Node* sender, MouseEventArgs* e)
    {
        LayoutGuest.Classic.top(getRelativeOffsetVector().Y - 1);
    };*/

}

void PseudoButton::setText(std::string text)
{
    _textBlock->setText(text);
}

std::string PseudoButton::getText()
{
    return _textBlock->getText();
}

void PseudoButton::setWidth(double width)
{
    width_set(width);
    _textBlock->width_set(width);


}