#include "TextBlockTestWindow.h"
#include "Window.h"

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace Eleusis::PseudoControls;
using namespace std;


TextBlockTestWindow::TextBlockTestWindow()
{
    Rectangle* l_background = new Rectangle(2000, 2000);
    l_background->fillColor_set(Colors::White);
    insertChild(l_background);

    /*_tb1p1s1 = new Span();
    _tb1p1s1->setText("Hi I am ŠЋ Bogdan! ");

    _tb1p1s2 = new Span();
    _tb1p1s2->setText("Hi I am Milan! ");

    _tb1p1s3 = new Span();
    _tb1p1s3->setText("Hi I am Petar! ");

    _tb1p1 = new Paragraph();
    _tb1p1->insertSpan(_tb1p1s1);
    _tb1p1->insertSpan(_tb1p1s2);
    _tb1p1->insertSpan(_tb1p1s3);

    _tb1p2s1 = new Span();
    _tb1p2s1->setText("Hi I am Dragan! ");

    _tb1p2s2 = new Span();
    _tb1p2s2->setText("Hi I am Igor! ");

    _tb1p2s3 = new Span();
    _tb1p2s3->setText("Hi I am Milivoje!");

    _tb1p2 = new Paragraph();
    _tb1p2->insertSpan(_tb1p2s1);
    _tb1p2->insertSpan(_tb1p2s2);
    _tb1p2->insertSpan(_tb1p2s3);

    _tb1 = new TextBlock();
    _tb1->insertParagraph(_tb1p1);
    _tb1->insertParagraph(_tb1p2);
    _tb1->width_set(400);
    _tb1->height_set(50);
    _tb1->textSize_set(20);
    _tb1->fontFamily_set("Times New Roman");
    _tb1->LayoutGuest.Classic.top(50);
    _tb1->LayoutGuest.Classic.left(300);

    insertChild(_tb1);



    _btn1 = new PseudoButton();
    _btn1->width_set(100._FPs);
    _btn1->LayoutGuest.Stack.marginBottom_set(10);
    _btn1->setText("Change Span 1 Text");
    _btn1->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {
        _tb1p1s1->foregroundColor_set(Colors::HotPink());
    };

    _btn2 = new PseudoButton();
    _btn2->width_set(100._FPs);
    _btn2->LayoutGuest.Stack.marginBottom_set(10);
    _btn2->setText("Change Par 1 Text");
    _btn2->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {
        //_tb1p1->setText("BLA BLA BLA ... ! ");
    };

    _btn3 = new PseudoButton();
    _btn3->width_set(100._FPs);
    _btn3->LayoutGuest.Stack.marginBottom_set(10);
    _btn3->setText("Change TextBlock Text");
    _btn3->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {
        _tb1->setText("");
    };

    _btn4 = new PseudoButton();
    _btn4->width_set(100._FPs);
    _btn4->LayoutGuest.Stack.marginBottom_set(10);
    _btn4->setText("");

    Rectangle* _buttons = new Rectangle(270, 100._FPs);
    _buttons->fillColor_set(Colors::AliceBlue());
    _buttons->LayoutHost.padding(10, 10, 10, 10);
    _buttons->insertChild(_btn1);
    _buttons->insertChild(_btn2);
    _buttons->insertChild(_btn3);
    _buttons->insertChild(_btn4);
    insertChild(_buttons);*/

    _rect = new Rectangle(200, 200);
    _rect->LayoutGuest.Classic.topLeft(50, 50);
    _rect->fillColor_set(Colors::Pink);
    insertChild(_rect);



    _rect->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {
        int top = 50;

        for (int i = 0; i < 100; i++)
        {
            TextBlock* _txt = new TextBlock();
            _txt->setText(" hdfg hdfg dfl ghh g; gh:SDj hsjgh sjgh SKdf h;swgh DSh Sf h;srgh dhfjh sufe sdkf :Lsif h;sge hcxhv SLdfe QWf hhj vkdshfekuhfg ;KDjvh ug hsuh isxhvfsu fhsghixuvh isuehf iuhv uicxh vzdsh F:Ef uihS uhivusdhuif huiewshf isudh LSDfui hseuif hsudvh SIfuhe SEouil hdsvuhSEUIf hslE ughSUIEfh slif hsIuf hesiuf hSLf uhseuf suf sefhushf us FIEfu hsfue hSLEufh Sfh suefh ");
            _txt->width_set(600);
            _txt->LayoutGuest.Classic.topLeft(top, top);
            top += 3;
            _rect->insertChild(_txt);
            txt[i] = _txt;
        }
    };

    l_background->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {

        for (int i = 0; i < 100; i++)
        {
            _rect->removeChild(txt[i]);
            delete txt[i];
        }
        
        //removeChild(_rect);
        //delete _rect;
    };
}
