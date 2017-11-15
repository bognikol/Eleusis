#include "CheckBox.h"
#include "CheckBoxDefaultSkin.h"

using namespace Eleusis;
using namespace std;

CheckBox::CheckBox()
{
    setSkin(new CheckBoxDefaultSkin());

    mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        _isChecked = !_isChecked;  
        raiseEvent checkChanged(this, nullptr);
    };
}

void CheckBox::setText(std::string text)
{
    if (_text == text)
        return;

    _text = text;
    raiseEvent textChanged(this, nullptr);
}

std::string CheckBox::getText()
{
    return _text;
}

void CheckBox::check()
{
    if (!_isChecked)
        _isChecked = true;

    raiseEvent checkChanged(this, nullptr);
}

void CheckBox::uncheck()
{
    if (_isChecked)
        _isChecked = false;

    raiseEvent checkChanged(this, nullptr);
}

void CheckBox::_applySkin()
{
    if (!getSkin())
        return;

    insertChild(getSkin()->getRectanlge());
    insertChild(getSkin()->getTextBlock());
    insertChild(getSkin()->getCheckMark());

    if (getSkin()->getGotFocusHandler().target())
        gotFocus += getSkin()->getGotFocusHandler();

    if (getSkin()->getLostFocusHandler().target())
        lostFocus += getSkin()->getLostFocusHandler();

    if (getSkin()->getKeyDownHandler().target())
        keyDown += getSkin()->getKeyDownHandler();
    
    if (getSkin()->getKeyUpHandler().target())
        keyUp += getSkin()->getKeyUpHandler();

    if (getSkin()->getMouseClickHandler().target())
        mouseClick += getSkin()->getMouseClickHandler();
    
    if (getSkin()->getMouseDoubleClickHandler().target())
        mouseDoubleClick += getSkin()->getMouseDoubleClickHandler();
   
    if (getSkin()->getMouseDownHandler().target())
        mouseDown += getSkin()->getMouseDownHandler();
    
    if (getSkin()->getMouseUpHandler().target())
        mouseUp += getSkin()->getMouseUpHandler();
    
    if (getSkin()->getMouseScrollHandler().target())
        mouseScroll += getSkin()->getMouseScrollHandler();
    
    if (getSkin()->getMouseMoveHandler().target())
        mouseMove += getSkin()->getMouseMoveHandler();
    
    if (getSkin()->getMouseEnterHandler().target())
        mouseEnter += getSkin()->getMouseEnterHandler();
    
    if (getSkin()->getMouseLeaveHandler().target())
        mouseLeave += getSkin()->getMouseLeaveHandler();

    if (getSkin()->getCheckChangedHandler().target())
        checkChanged += getSkin()->getCheckChangedHandler();

    if (getSkin()->getTextChangedHandler().target())
        textChanged += getSkin()->getTextChangedHandler();
}