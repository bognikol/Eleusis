#include "EleusisWindowTestWindow.h"
#include "Colors.h"
#include "Timer.h"
#include "TextBlock.h"
#include "PseudoButton.h"
#include "PseudoTextBox.h"
#include "Timeline.h"
#include "AnimationTestWindow.h"
#include "Application.h"

#include <string>

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace Eleusis::PseudoControls;

EleusisWindowTestWindow::EleusisWindowTestWindow()
{
    Eleusis::Rectangle* rect = new Eleusis::Rectangle(2000, 1200);
    rect->fillColor_set(Colors::White);
    insertChild(rect);

    win = new Test::AnimationTestWindow();

    PseudoButton* btn1 = new PseudoButton();
    btn1->LayoutGuest.Classic.top(20);
    btn1->LayoutGuest.Classic.left(20);
    btn1->setText("Hide");
    btn1->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        win->hide();
    };
    insertChild(btn1);

    PseudoButton* btn2 = new PseudoButton();
    btn2->LayoutGuest.Classic.top(60);
    btn2->LayoutGuest.Classic.left(20);
    btn2->setText("Maximize");
    btn2->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        win->maximize();
    };
    insertChild(btn2);

    PseudoButton* btn3 = new PseudoButton();
    btn3->LayoutGuest.Classic.top(100);
    btn3->LayoutGuest.Classic.left(20);
    btn3->setText("Minimize");
    btn3->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        win->minimize();
    };
    insertChild(btn3);

    PseudoButton* btn4 = new PseudoButton();
    btn4->LayoutGuest.Classic.top(140);
    btn4->LayoutGuest.Classic.left(20);
    btn4->setText("Show");
    btn4->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        win->show();
    };
    insertChild(btn4);

    PseudoButton* btn5 = new PseudoButton();
    btn5->LayoutGuest.Classic.top(180);
    btn5->LayoutGuest.Classic.left(20);
    btn5->setText("Focus");
    btn5->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        win->focus();
    };
    insertChild(btn5);

    PseudoButton* btn6 = new PseudoButton();
    btn6->LayoutGuest.Classic.top(220);
    btn6->LayoutGuest.Classic.left(20);
    btn6->setText("Enalbe");
    btn6->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        win->enable();
    };
    insertChild(btn6);

    PseudoButton* btn7 = new PseudoButton();
    btn7->LayoutGuest.Classic.top(260);
    btn7->LayoutGuest.Classic.left(20);
    btn7->setText("Disable");
    btn7->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        win->disable();
    };
    insertChild(btn7);

    PseudoButton* btn8 = new PseudoButton();
    btn8->LayoutGuest.Classic.top(300);
    btn8->LayoutGuest.Classic.left(20);
    btn8->setText("Position and Size");
    btn8->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        Application::nativeMsgBox("Position and Size", "Size X: " + std::to_string(win->getSize().X) +
            "\nSize Y: " + std::to_string(win->getSize().Y) +
            "\nPosition X: " + std::to_string(win->getPosition().X) +
            "\nPosition Y: " + std::to_string(win->getPosition().Y));
    };
    insertChild(btn8);

    txt1 = new PseudoTextBox();
    txt1->LayoutGuest.Classic.top(20);
    txt1->LayoutGuest.Classic.left(200);
    txt1->setText("50");
    txt1->width_set(80);
    insertChild(txt1);

    txt2 = new PseudoTextBox();
    txt2->LayoutGuest.Classic.top(20);
    txt2->LayoutGuest.Classic.left(300);
    txt2->setText("50");
    txt2->width_set(80);
    insertChild(txt2);

    PseudoButton* btn9 = new PseudoButton();
    btn9->LayoutGuest.Classic.top(60);
    btn9->LayoutGuest.Classic.left(200);
    btn9->setText("Set Position");
    btn9->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        win->setPosition({ std::stod(txt1->getText()), std::stod(txt2->getText()) });
    };
    insertChild(btn9);


    txt3 = new PseudoTextBox();
    txt3->LayoutGuest.Classic.top(100);
    txt3->LayoutGuest.Classic.left(200);
    txt3->setText("50");
    txt3->width_set(80);
    insertChild(txt3);

    txt4 = new PseudoTextBox();
    txt4->LayoutGuest.Classic.top(100);
    txt4->LayoutGuest.Classic.left(300);
    txt4->setText("50");
    txt4->width_set(80);
    insertChild(txt4);

    PseudoButton* btn10 = new PseudoButton();
    btn10->LayoutGuest.Classic.top(140);
    btn10->LayoutGuest.Classic.left(200);
    btn10->setText("Set Size");
    btn10->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        win->setSize({ std::stod(txt3->getText()), std::stod(txt4->getText()) });
    };
    insertChild(btn10);

    Rectangle* r = new Rectangle(200, 200);
    r->LayoutGuest.Classic.left(800);
    r->LayoutGuest.Classic.top(100);
    r->fillColor_set(Colors::MidnightBlue);
    insertChild(r);

    Rectangle* r2 = new Rectangle(Eleusis::FractionLength(78.25), Eleusis::FractionLength(13.11));
    r2->LayoutGuest.Classic.left(Eleusis::FractionLength(50));
    //Rectangle* r2 = new Rectangle(50, 50);
    r2->fillColor_set(Colors::LightCyan);
    r->insertChild(r2);

    rect55 = new Rectangle(35, 35);
    rect55->LayoutGuest.Classic.left(20);
    rect55->fillColor_set(Colors::PaleVioletRed);

    //circ55 = new Circle(150);
    //circ55->fillColor_set(Colors::Yellow);
    //insertChild(rect55);
    //insertChild(circ55);

    /*mouseMove +=
        [this](Window* sender, MouseEventArgs* e)
    {
        circ55->LayoutGuest.Classic.bottom(e->Y);
        circ55->LayoutGuest.Classic.right(e->X);
        //circ55->radius_set(e->Y / 4);
        //rect55->width_set(e->X / 4);
    };*/
}

EleusisWindowTestWindow::~EleusisWindowTestWindow()
{
}

