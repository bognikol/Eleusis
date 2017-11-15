#include "CheckBoxTestWindow.h"

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace std;

CheckBoxTestWindow::CheckBoxTestWindow()
{
    Rectangle* _background = new Rectangle(2000, 2000);
    _background->fillColor_set(Colors::White);
    insertChild(_background);

    CheckBox* _chck = new CheckBox();
    _chck->LayoutGuest.Classic.topLeft(50, 50);
    _chck->setText("I am a jerk!");
    _chck->check();
    insertChild(_chck);

}