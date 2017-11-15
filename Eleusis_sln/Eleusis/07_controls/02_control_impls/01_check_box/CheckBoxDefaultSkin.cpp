#include "CheckBoxDefaultSkin.h"
#include "CheckBox.h"

using namespace Eleusis;
using namespace std;

CheckBoxDefaultSkin::CheckBoxDefaultSkin()
{
    Rectangle* l_rect = new Rectangle(14, 14);
    l_rect->LayoutGuest.Classic.topLeft(0.5, 0.5);
    l_rect->lineColor_set(Colors::Black);
    l_rect->fillColor_set(Colors::Transparent);
    l_rect->lineThickenss_set(1);
    _rect = l_rect;

    GenericShape* l_checkMark = new GenericShape();
    l_checkMark->moveTo(0, 7);
    l_checkMark->lineTo(5, 10);
    l_checkMark->lineTo(16, 1);
    l_checkMark->LayoutGuest.Classic.topLeft(0, 3);
    l_checkMark->lineColor_set(Colors::Transparent);
    l_checkMark->lineThickenss_set(5);
    l_checkMark->strokeJoinStyle_set(StrokeJoinStyle::Round);
    _checkMark = l_checkMark;

    TextBlock* l_text = new TextBlock();
    l_text->setText("This is a check box :-)");
    l_text->LayoutGuest.Classic.topLeft(-1, 23);
    l_text->height_set(20);
    l_text->width_set(150);
    _text = l_text;

    _textChangedHandler =
        [this](CheckBox* sender, EventArgs* e)
    {
        _text->setText(sender->getText());
    };

    _checkChangedHandler = 
        [this](CheckBox* sender, EventArgs* e)
    {
        if (sender->isChecked())
            static_cast<GenericShape*>(_checkMark)->lineColor_set(Colors::Blue);
        else
            static_cast<GenericShape*>(_checkMark)->lineColor_set(Colors::Transparent);
    };

    _mouseDownHandler =
        [this](Node* sender, EventArgs* e)
    {
        static_cast<Rectangle*>(_rect)->fillColor_set(Colors::Purple);
    };


    _mouseUpHandler =
        [this](Node* sender, EventArgs* e)
    {
        static_cast<Rectangle*>(_rect)->fillColor_set(Colors::Azure);
    };

    _mouseEnterHandler =
        [this](Node* sender, EventArgs* e)
    {
        static_cast<Rectangle*>(_rect)->fillColor_set(Colors::Azure);
    };

    _mouseLeaveHandler =
        [this](Node* sender, EventArgs* e)
    {
        static_cast<Rectangle*>(_rect)->fillColor_set(Colors::Transparent);
    };
}