#include "MouseEventTextBlockTestWindow.h"
#include "Window.h"
#include "Application.h"

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace std;


MouseEventTextBlockTestWindow::MouseEventTextBlockTestWindow()
{
    Rectangle* l_background = new Rectangle(2000, 2000);
    l_background->fillColor_set(Colors::White);
    insertChild(l_background);

    _tb1p1s1 = new Span();
    _tb1p1s1->setText("Hi I am Bogdan! ");
    _tb1p1s1->backgroundColor_set(Colors::Magenta);
    _tb1p1s1->foregroundColor_set(Colors::White);

    _tb1p1s2 = new Span();
    _tb1p1s2->setText("Hi I am Milan! ");

    _tb1p1s3 = new Span();
    _tb1p1s3->backgroundColor_set(Colors::Moccasin);
    _tb1p1s3->setText("Hi I am Petar! ");

    _tb1p1 = new Paragraph();
    _tb1p1->insertSpan(_tb1p1s1);
    _tb1p1->insertSpan(_tb1p1s2);
    _tb1p1->insertSpan(_tb1p1s3);



    _tb1p2s1 = new Span();
    _tb1p2s1->setText("Hi I am Dragan! ");


    _tb1p2s2 = new Span();
    _tb1p2s2->setText("Hi I am Igor! ");
    _tb1p2s2->mouseClick +=
        [](Span* sender, EventArgs* e)
    {
        Application::nativeMsgBox("Span No.2");
    };

    _tb1p2s3 = new Span();
    _tb1p2s3->setText("Hi I am Milivoje!  awljf aoiuf askgf hds aiogf asgf asdhbf ryfg akrygf aiorfg wioyrf ysbfy fgaoer fjyarbf ajrybf ouaybr fiuayerb iuerybv aeryb vaeurybf aeruyb urybv erabu");
    _tb1p2s3->backgroundColor_set(Colors::Aqua);
    _tb1p2s3->mouseClick +=
        [](Span* sender, EventArgs* e)
    {
        Application::nativeMsgBox("BLA!");
    };

    _tb1p2s3->mouseEnter +=
        [this](Span* sender, MouseEventArgs* e)
    {
        _tb1p2s3->underline_set(UnderlineType::Single);
    };

    _tb1p2s3->mouseLeave +=
        [this](Span* sender, MouseEventArgs* e)
    {
        _tb1p2s3->underline_set(UnderlineType::None);
    };

    _tb1p2 = new Paragraph();
    _tb1p2->insertSpan(_tb1p2s1);
    _tb1p2->insertSpan(_tb1p2s2);
    _tb1p2->insertSpan(_tb1p2s3);
    _tb1p2->leftIndent_set(40);

    _tb1p2->mouseClick +=
        [this](Paragraph* sender, EventArgs* e)
    {

    };

    _tb1 = new TextBlock();
    _tb1->insertParagraph(_tb1p1);
    _tb1->insertParagraph(_tb1p2);
    _tb1->width_set(150);
    _tb1->LayoutGuest.Classic.top(50);
    _tb1->LayoutGuest.Classic.left(50);

    Rectangle* rect = new Rectangle(200, 200, 3);
    rect->fillColor_set(Colors::DeepSkyBlue);
    rect->LayoutGuest.Classic.top(120);
    rect->LayoutGuest.Classic.left(70);
    _tb1->insertChild(rect);


    insertChild(_tb1);

}

