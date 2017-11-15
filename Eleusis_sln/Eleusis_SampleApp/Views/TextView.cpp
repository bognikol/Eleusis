#include "TextView.h"
#include <memory>

using namespace Eleusis;
using namespace Eleusis::SampleApp;
using namespace std;

TextView::TextView() :
    SectionViewBase()
{
    fillColor_set(Colors::White);

    SelectEdit* l_editTextBlock = new SelectEdit();
    l_editTextBlock->LayoutGuest.Classic.topLeft(50, 50);
    l_editTextBlock->setText("Edit me :-)");
    l_editTextBlock->textSize_set(35);
    l_editTextBlock->fillColor_set(Colors::Gray);
    l_editTextBlock->fontFamily_set("Segoe UI Light");
    l_editTextBlock->width_set(600);
    l_editTextBlock->height_set(100._FPs);
    l_editTextBlock->caretColor_set(Colors::Gray);
    insertChild(l_editTextBlock);

    Paragraph* l_paragraph1 = new Paragraph();
    l_paragraph1->setText("Eleusis tries to offer rich-text editing functionality. Eleusis uses Pango, "
        "text rendering library from GTK family, and adds editing capabilities to it.");
    l_paragraph1->textSize_set(13);
    l_paragraph1->fontFamily_set("Segoe UI");
    l_paragraph1->fontWeight_set(FontWeight::w900_Ultraheavy);
    l_editTextBlock->insertParagraph(l_paragraph1);

    Paragraph* l_paragraph2 = new Paragraph();
    l_paragraph2->setText("TextBlock is basic text object in Eleusis. "
    "TextBlock is made of Paragraphs, and paragraphs consist of ");
    l_paragraph2->textSize_set(20);
    l_paragraph2->fontFamily_set("Palatino Linotype");
    l_paragraph2->fontStyle_set(FontStyle::Italic);
    l_paragraph2->leftIndent_set(100);
    l_editTextBlock->insertParagraph(l_paragraph2);

    Span* l_span1 = new Span("spans.");
    l_span1->backgroundColor_set(Colors::Gold);
    l_span1->fontWeight_set(FontWeight::w700_Ultrabold);
    l_span1->fontStyle_set(FontStyle::Italic);
    l_span1->fontFamily_set("Arial Black");
    l_span1->foregroundColor_set(Colors::White);
    l_paragraph2->insertSpan(l_span1);

    Paragraph* l_paragraph3 = new Paragraph();
    l_paragraph3->setText("Span is an array of characters that have same rendering parameters.");
    l_paragraph3->textSize_set(20);
    l_paragraph3->fontFamily_set("Palatino Linotype");
    l_paragraph3->fontWeight_set(FontWeight::w900_Ultraheavy);
    l_paragraph3->leftIndent_set(20);
    shared_ptr<LinearGradientBrush> l_gradient2 = shared_ptr<LinearGradientBrush>(new LinearGradientBrush());
    l_gradient2->addGradientStop(Colors::GreenYellow, 0.0);
    l_gradient2->addGradientStop(Colors::Magenta, 0.33);
    l_gradient2->addGradientStop(Colors::SkyBlue, 0.67);
    l_gradient2->addGradientStop(Colors::OrangeRed, 1.0);
    l_gradient2->setGradientStrech(0, 300, 600, 400);
    l_paragraph3->fillBrush_set(l_gradient2);
    l_editTextBlock->insertParagraph(l_paragraph3);

    TextualShape* _textualShape = new TextualShape("Hoower");
    _textualShape->fontFamily_set("Times New Roman");
    _textualShape->fillColor_set(Colors::Gray);
    _textualShape->LayoutGuest.Classic.topLeft(300, 800);
    _textualShape->textSize_set(200);
    _textualShape->fontStyle_set(FontStyle::Italic);
    insertChild(_textualShape);

    _textualShape->mouseEnter +=
        [_textualShape](Node* sender, EventArgs* e)
    {
        if (_textualShape->animate()->isRunning())
        {
            _textualShape->animate()->reverse();
            return;
        }

        _textualShape->animate()->clear();
        _textualShape->animate()->fillColor.startValue(Colors::Gray);
        _textualShape->animate()->fillColor.endValue(Colors::Turquoise);
        _textualShape->animate()->start();
    };

    _textualShape->mouseLeave +=
        [_textualShape](Node* sender, EventArgs* e)
    {
        _textualShape->animate()->reverse();

        if (!_textualShape->animate()->isRunning())
            _textualShape->animate()->start();
    };

    

}