
#include "PseudoTextBox.h"
#include <cstdlib>
#include <sstream>

using namespace Eleusis;
using namespace Eleusis::PseudoControls;
using namespace std;

PseudoTextBox::PseudoTextBox()
{
    height_set(30);
    width_set(300);
    lineColor_set(Colors::Gray);
    fillColor_set(Colors::White);
    lineThickenss_set(1);
    cornerRadius_set(3);

    _textBlock = new TextBlock();
    _textBlock->width_set(280);
    _textBlock->height_set(20);
    _textBlock->LayoutGuest.Classic.top(5);
    _textBlock->LayoutGuest.Classic.left(10);
    _textBlock->foregroundColor_set(Colors::Black);
    _textBlock->setText("Hello World!");
    insertChild(_textBlock);

    _keyDownEventHandler =
        [this](Window* sender, KeyboardEventArgs* e)
    {
        /*if (!_editMode) return;

        if (e->Characters == "0") return;

        if (e->VirtualKeyCode == VirtualKey::Backspace) // Backspace
        {
            _textBlock->setText(_textBlock->getText().substr(0, _textBlock->getText().size() - 1));
        }
        else
        {
            _textBlock->setText(_textBlock->getText() + string(e->Characters));
        }*/
    };

    mouseDoubleClick += 
        [this](Node* sender, MouseEventArgs* e)
    {
        if (_editMode)
        {
            _editMode = false;
            lineColor_set(Colors::Gray);
            raiseEvent textChanged(this, nullptr);
        }
        else
        {
            _editMode = true;
            lineColor_set(Colors::RoyalBlue);
            _parentWindow = static_cast<Window*>(uiContext());
            _parentWindow->keyDown += _keyDownEventHandler;
            _textBlock->setText("");
        }
    };

    

}

void PseudoTextBox::setText(std::string text)
{
    _textBlock->setText(text);
}

std::string PseudoTextBox::getText()
{
    return _textBlock->getText();
}

void PseudoTextBox::setWidth(double width)
{
    width_set(width);
    _textBlock->width_set(width - 20);
}
