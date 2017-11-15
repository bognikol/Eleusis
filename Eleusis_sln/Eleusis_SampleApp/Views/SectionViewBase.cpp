#include "SectionViewBase.h"

using namespace Eleusis;
using namespace Eleusis::SampleApp;

SectionViewBase::SectionViewBase()
{
    TextualShape* l_textShape = new TextualShape();
    l_textShape->LayoutGuest.Classic.topLeft(4, 10);
    l_textShape->text_set("BACK");
    l_textShape->fillColor_set(Colors::Black);
    l_textShape->fontFamily_set("Segoe UI");
    l_textShape->fontWeight_set(FontWeight::w900_Ultraheavy);
    l_textShape->letterSpacing_set(1);

	Rectangle* l_backButton = new Rectangle(56, 25);
	l_backButton->fillColor_set(Colors::LightGray);
	l_backButton->LayoutGuest.Classic.topLeft(10, 10);
    l_backButton->insertChild(l_textShape);

    l_backButton->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        raiseEvent backRequested(this, nullptr);
    };

    l_backButton->mouseEnter +=
        [l_backButton](Node* sender, EventArgs* e)
    {
        l_backButton->fillColor_set(Colors::DarkGray);
    };

    l_backButton->mouseLeave +=
        [l_backButton](Node* sender, EventArgs* e)
    {
        l_backButton->fillColor_set(Colors::LightGray);
    };

	insertChild(l_backButton);




}