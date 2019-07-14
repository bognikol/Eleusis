#include "HomeView.h"
#include "TextBlock.h"
#include "Application.h"

using namespace Eleusis;
using namespace Eleusis::SampleApp;
using namespace std;

HomeView::NavigateButton::NavigateButton()
{
	fillColor_set(Colors::Bisque);

	_textBlock = new TextBlock();
	_textBlock->width_set(100._FPs);
	_textBlock->spaceBefore_set(0);
	_textBlock->fontFamily_set("Arial");
	_textBlock->textSize_set(12);
	_textBlock->fillColor_set(Colors::RoyalBlue);
	_textBlock->LayoutGuest.Classic.top(40);
	_textBlock->paragraphAligment_set(ParagraphAlignment::Center);
	insertChild(_textBlock);

	mouseEnter +=
		[this](Node* sender, EventArgs* e)
	{
		if (animate()->isRunning())
		{
			animate()->reverse();
			return;
		}

		animate()->clear();
		animate()->height.endValue(120);
		animate()->start();
	};

	mouseLeave +=
		[this](Node* sender, EventArgs* e)
	{
		animate()->reverse();

        if (!animate()->isRunning())
		    animate()->start();
	};
}

void HomeView::NavigateButton::text_set(string text)
{
	_textBlock->setText(text);
}

string HomeView::NavigateButton::text_get()
{
	return _textBlock->getText();
}

void HomeView::_addOption(string optionName, string buttonText)
{
	if (buttonText.empty())
		buttonText = optionName;

	NavigateButton* l_navigateButton = new NavigateButton();
	l_navigateButton->text_set(buttonText);
	l_navigateButton->setWidthAndHeight(100, 100);
	l_navigateButton->LayoutGuest.Stack.marginRight_set(20);
	l_navigateButton->mouseClick +=
		[this, optionName](Node* sender, EventArgs* e)
	{
		OptionSelectedEventArgs l_e;
		l_e.option = optionName;
		raiseEvent optionSelected(this, &l_e);
	};
	_navigationContainer->insertChild(l_navigateButton);
}


HomeView::HomeView() 
{
	fillColor_set(Colors::RoyalBlue);

	TextBlock* l_aboutEleusis = new TextBlock();
	l_aboutEleusis->LayoutGuest.Classic.topLeft(30._FPs, 20);
    l_aboutEleusis->width_set(650);
	l_aboutEleusis->setText("Welcome to Eleusis.");
	l_aboutEleusis->textSize_set(25);
	l_aboutEleusis->fontFamily_set("Arial");
	l_aboutEleusis->fillColor_set(Colors::White);
    insertChild(l_aboutEleusis);

	Paragraph* l_paragraph1 = new Paragraph();
	l_paragraph1->setText("Eleusis is a lightweight multiplatform pure-C++ GUI library with modern eventing architecture and layouting model.");
    l_paragraph1->spaceAfter_set(120);
	l_paragraph1->textSize_set(12);
	l_aboutEleusis->insertParagraph(l_paragraph1);

    Paragraph* l_paragraph2 = new Paragraph();
    l_paragraph2->setText("This sample application aims to show few capabilities of Eleusis.");
    l_paragraph2->textSize_set(12);
    l_paragraph2->spaceAfter_set(0);
    l_aboutEleusis->insertParagraph(l_paragraph2);

	_navigationContainer = new Container();
	_navigationContainer->LayoutGuest.Classic.topLeft(70._FPs, 20);
	_navigationContainer->LayoutHost.stackOrientation_set(LayoutOrientation::Horizontal);
	insertChild(_navigationContainer);

	_addOption("ANIMATION");
	_addOption("TEXT");
	_addOption("EVENTS");
}
