#include "MouseEventBubblingTestWindow.h"
#include "ToString.h"

using namespace Eleusis;
using namespace Eleusis::Test;

MouseEventDetailsPseudoControl::MouseEventDetailsPseudoControl(Node* listenedNode)
{
    eventSender = listenedNode;

    textLine_mouseClick = new TextualShape();
    textLine_mouseDoubleClick = new TextualShape();
    textLine_mouseDown = new TextualShape();
    textLine_mouseUp = new TextualShape();
    textLine_mouseWheelRotated = new TextualShape();
    textLine_mouseMove = new TextualShape();
    textLine_mouseEnter = new TextualShape();
    textLine_mouseLeave = new TextualShape();

    textLine_mouseClick->text_set("mouseClick: " + std::to_string(0));
    textLine_mouseDoubleClick->text_set("mouseDoubleClick: " + std::to_string(0));
    textLine_mouseDown->text_set("mouseDown: " + std::to_string(0));
    textLine_mouseUp->text_set("mouseUp: " + std::to_string(0));
    textLine_mouseWheelRotated->text_set("mouseScroll: " + std::to_string(0));
    textLine_mouseMove->text_set("mouseMove: " + std::to_string(0));
    textLine_mouseEnter->text_set("mouseEnter: " + std::to_string(0));
    textLine_mouseLeave->text_set("mouseLeave: " + std::to_string(0));

    textLine_mouseClick->LayoutGuest.Classic.top(0);
    textLine_mouseDoubleClick->LayoutGuest.Classic.top(20);
    textLine_mouseDown->LayoutGuest.Classic.top(40);
    textLine_mouseUp->LayoutGuest.Classic.top(60);
    textLine_mouseWheelRotated->LayoutGuest.Classic.top(80);
    textLine_mouseMove->LayoutGuest.Classic.top(100);
    textLine_mouseEnter->LayoutGuest.Classic.top(120);
    textLine_mouseLeave->LayoutGuest.Classic.top(140);

    textLine_mouseClick->fillColor_set(Colors::Black);
    textLine_mouseDoubleClick->fillColor_set(Colors::Black);
    textLine_mouseDown->fillColor_set(Colors::Black);
    textLine_mouseUp->fillColor_set(Colors::Black);
    textLine_mouseWheelRotated->fillColor_set(Colors::Black);
    textLine_mouseMove->fillColor_set(Colors::Black);
    textLine_mouseEnter->fillColor_set(Colors::Black);
    textLine_mouseLeave->fillColor_set(Colors::Black);

    Eleusis::Rectangle* rect = new Eleusis::Rectangle();
    rect->insertChild(textLine_mouseClick);
    rect->insertChild(textLine_mouseDoubleClick);
    rect->insertChild(textLine_mouseDown);
    rect->insertChild(textLine_mouseUp);
    rect->insertChild(textLine_mouseWheelRotated);
    rect->insertChild(textLine_mouseMove);
    rect->insertChild(textLine_mouseEnter);
    rect->insertChild(textLine_mouseLeave);

    insertChild(rect);

    textLine_lastMouseEventArgs = new TextualShape();
    textLine_lastMouseEventArgs->LayoutGuest.Classic.top(200);
    textLine_lastMouseEventArgs->fillColor_set(Colors::Gray);
    textLine_lastMouseEventArgs->text_set("Last event parameters: NA");

    insertChild(textLine_lastMouseEventArgs);



    eventSender->mouseClick +=
        [this](Node* sender, MouseEventArgs* e)
    {
        count_mouseClick++;
        textLine_mouseClick->text_set("mouseClick: " + std::to_string(count_mouseClick));
        textLine_lastMouseEventArgs->text_set("Last event parameters:\n" + toString(e));
    };

    eventSender->mouseDoubleClick +=
        [this](Node* sender, MouseEventArgs* e)
    {
        count_mouseDoubleClick++;
        textLine_mouseDoubleClick->text_set("mouseDoubleClick: " + std::to_string(count_mouseDoubleClick));
        textLine_lastMouseEventArgs->text_set("Last event parameters:\n" + toString(e));
    };

    eventSender->mouseDown +=
        [this](Node* sender, MouseEventArgs* e)
    {
        count_mouseDown++;
        textLine_mouseDown->text_set("mouseDown: " + std::to_string(count_mouseDown));
        textLine_lastMouseEventArgs->text_set("Last event parameters:\n" + toString(e));
    };

    eventSender->mouseUp +=
        [this](Node* sender, MouseEventArgs* e)
    {
        count_mouseUp++;
        textLine_mouseUp->text_set("mouseUp: " + std::to_string(count_mouseUp));
        textLine_lastMouseEventArgs->text_set("Last event parameters:\n" + toString(e));
    };

    eventSender->mouseScroll +=
        [this](Node* sender, MouseScrollEventArgs* e)
    {
        count_mouseWheelRotated++;
        textLine_mouseWheelRotated->text_set("mouseWRotated: " + std::to_string(count_mouseWheelRotated));
        textLine_lastMouseEventArgs->text_set("Last event parameters:\n" + toString(e));
    };

    eventSender->mouseMove +=
        [this](Node* sender, MouseEventArgs* e)
    {
        count_mouseMove++;
        textLine_mouseMove->text_set("mouseMove: " + std::to_string(count_mouseMove));
        textLine_lastMouseEventArgs->text_set("Last event parameters:\n" + toString(e));
    };

    eventSender->mouseEnter +=
        [this](Node* sender, MouseEventArgs* e)
    {
        count_mouseEnter++;
        textLine_mouseEnter->text_set("mouseEnter: " + std::to_string(count_mouseEnter));
        textLine_lastMouseEventArgs->text_set("Last event parameters:\n" + toString(e));
    };

    eventSender->mouseLeave +=
        [this](Node* sender, MouseEventArgs* e)
    {
        count_mouseLeave++;
        textLine_mouseLeave->text_set("mouseLeave: " + std::to_string(count_mouseLeave));
        textLine_lastMouseEventArgs->text_set("Last event parameters:\n" + toString(e));
    };
}

MouseEventBubblingTestWindow::MouseEventBubblingTestWindow()
{
    Rectangle* l_background = new Rectangle(2000, 2000);
    l_background->fillColor_set(Colors::White);
    insertChild(l_background);

    Rectangle* rect = new Rectangle(250, 250);
    rect->LayoutGuest.Classic.top(120);
    rect->LayoutGuest.Classic.left(50);
    rect->fillColor_set(Colors::RoyalBlue);
    insertChild(rect);

    Circle* circ = new Circle(150);
    circ->fillColor_set(Colors::DeepPink);
    circ->LayoutGuest.Classic.top(-100);
    circ->LayoutGuest.Classic.left(100);
    rect->insertChild(circ);

    Circle* circ2 = new Circle(100);
    circ2->fillColor_set(Colors::PaleTurquoise);
    circ2->LayoutGuest.Classic.top(40);
    circ2->LayoutGuest.Classic.left(-80);
    circ->insertChild(circ2);

    MouseEventDetailsPseudoControl* l_ctrl1 = new MouseEventDetailsPseudoControl(rect);
    l_ctrl1->LayoutGuest.Classic.left(500);
    l_ctrl1->LayoutGuest.Classic.top(50);
    insertChild(l_ctrl1);

    MouseEventDetailsPseudoControl* l_ctrl2 = new MouseEventDetailsPseudoControl(circ);
    l_ctrl2->LayoutGuest.Classic.left(700);
    l_ctrl2->LayoutGuest.Classic.top(50);
    insertChild(l_ctrl2);

    MouseEventDetailsPseudoControl* l_ctrl3 = new MouseEventDetailsPseudoControl(circ2);
    l_ctrl3->LayoutGuest.Classic.left(900);
    l_ctrl3->LayoutGuest.Classic.top(50);
    insertChild(l_ctrl3);



}

