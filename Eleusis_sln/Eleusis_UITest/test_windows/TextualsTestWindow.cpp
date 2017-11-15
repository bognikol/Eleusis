#include "TextualsTestWindow.h"

using namespace Eleusis;
using namespace std;

TextualsTestWindow::TextualsTestWindow()
{
    Eleusis::Rectangle* rect = new Eleusis::Rectangle(2000, 1200);
    rect->fillColor_set(Colors::White);
    insertChild(rect);

    auto ss1 = std::shared_ptr<SpanStyle>(new SpanStyle());
    ss1->foregroundColor_set(Colors::Red);

    auto ss2 = std::shared_ptr<SpanStyle>(new SpanStyle());
    ss2->foregroundColor_set(Colors::Black);

    ss3 = std::shared_ptr<SpanStyle>(new SpanStyle());
    ss3->foregroundColor_set(Colors::Red);


    Span* tb1p1s1 = new Span("Span tb1p1s1. My name is Bogdan Nikolic. ");
    Span* tb1p1s2 = new Span("Span tb1p1s2. This should be red. ");
    tb1p1s2->spanStyle_set(ss3);
    Span* tb1p1s3 = new Span("Span tb1p1s3. Nice to meet you. ");
    Paragraph* tb1p1 = new Paragraph();
    tb1p1->insertSpan(tb1p1s1);
    tb1p1->insertSpan(tb1p1s2);
    tb1p1->insertSpan(tb1p1s3);
    tb1p1->spanStyle_set(ss2);

    Span* tb1p2s1 = new Span("This is span tb1p2s1. Belgrade is the capital city of Serbia and it used to be capital of Yugoslavia. ");
    Span* tb1p2s2 = new Span("This is span tb1p2s2. It has population of about 2 million ro even more. ");
    Span* tb1p2s3 = new Span("This is span tb1p2s3. Serbia has population of about 7 milion. ");
    Paragraph* tb1p2 = new Paragraph();
    tb1p2->insertSpan(tb1p2s1);
    tb1p2->insertSpan(tb1p2s2);
    tb1p2->insertSpan(tb1p2s3);

    tb1 = new TextBlock();
    tb1->insertParagraph(tb1p1);
    tb1->insertParagraph(tb1p2);

    tb1->spanStyle_set(ss1);

    tb1->LayoutGuest.Classic.top(50);
    tb1->LayoutGuest.Classic.left(50);
    insertChild(tb1);

    tb1->mouseDown +=
        [this](Node* sender, MouseEventArgs* e)
    {
        //tb1->getCharacterNumber({e->X, e->Y});



        /*Eleusis::Rectangle* r = new Eleusis::Rectangle(20, 20);
        insertChild(r);
        r->LayoutGuest.Classic.top(20);
        r->LayoutGuest.Classic.left(20);
        r->fillColor_set(Colors::Blue());*/
    };

    

    tb1->mouseMove +=
        [this](Node* sender, MouseEventArgs* e)
    {
        Rect rr = tb1->getCharacterExtent(Vector(e->X, e->Y ));
        Eleusis::Rectangle* r = new Eleusis::Rectangle(rr.width(), rr.height());
        insertChild(r);
        r->LayoutGuest.Classic.top(rr.lowVector.Y);
        r->LayoutGuest.Classic.left(rr.lowVector.X);
        r->fillColor_set(RgbaColor(0, 0, 255, 50));
    };
}
