#include "MouseEventTestWindow.h"
#include "Colors.h"
#include "toString.h"

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace std;

MouseEventTestPseudoControl::MouseEventTestPseudoControl(Node* node)
{
    eventSender = node;

    textLine_mouseClick         = new TextualShape();
    textLine_mouseDoubleClick   = new TextualShape();
    textLine_mouseDown          = new TextualShape();
    textLine_mouseUp            = new TextualShape();
    textLine_mouseWheelRotated  = new TextualShape();
    textLine_mouseMove          = new TextualShape();
    textLine_mouseEnter         = new TextualShape();
    textLine_mouseLeave         = new TextualShape();

    setTextColor(Colors::Black);

    textLine_mouseClick         ->text_set("mouseClick: "        + std::to_string(0));
    textLine_mouseDoubleClick   ->text_set("mouseDoubleClick: "  + std::to_string(0));
    textLine_mouseDown          ->text_set("mouseDown: "         + std::to_string(0));
    textLine_mouseUp            ->text_set("mouseUp: "           + std::to_string(0));
    textLine_mouseWheelRotated  ->text_set("mouseScroll: "       + std::to_string(0));
    textLine_mouseMove          ->text_set("mouseMove: "         + std::to_string(0));
    textLine_mouseEnter         ->text_set("mouseEnter: "        + std::to_string(0));
    textLine_mouseLeave         ->text_set("mouseLeave: "        + std::to_string(0));

    textLine_mouseClick         ->LayoutGuest.Classic.top(0);
    textLine_mouseDoubleClick   ->LayoutGuest.Classic.top(20);
    textLine_mouseDown          ->LayoutGuest.Classic.top(40);
    textLine_mouseUp            ->LayoutGuest.Classic.top(60);
    textLine_mouseWheelRotated  ->LayoutGuest.Classic.top(80);
    textLine_mouseMove          ->LayoutGuest.Classic.top(100);
    textLine_mouseEnter         ->LayoutGuest.Classic.top(120);
    textLine_mouseLeave         ->LayoutGuest.Classic.top(140);

    Eleusis::Rectangle* rect = new Eleusis::Rectangle();
    rect->insertChild(textLine_mouseClick);
    rect->insertChild(textLine_mouseDoubleClick);
    rect->insertChild(textLine_mouseDown);
    rect->insertChild(textLine_mouseUp);
    rect->insertChild(textLine_mouseWheelRotated);
    rect->insertChild(textLine_mouseMove);
    rect->insertChild(textLine_mouseEnter);
    rect->insertChild(textLine_mouseLeave);

    rect->LayoutGuest.Classic.left(815);
    rect->LayoutGuest.Classic.top(10);

    insertChild(rect);

    textLine_lastMouseEventArgs = new TextualShape();
    textLine_lastMouseEventArgs->LayoutGuest.Classic.top(200);
    textLine_lastMouseEventArgs->LayoutGuest.Classic.left(815);
    textLine_lastMouseEventArgs->fillColor_set(Colors::Gray);
    textLine_lastMouseEventArgs->text_set("Last event parameters: NA");

    insertChild(textLine_lastMouseEventArgs);

    width_set(1200);
    height_set(400);
    lineColor_set(Colors::Gray);
    lineThickenss_set(6);

    Eleusis::Line* line = new Eleusis::Line(0, 400);
    line->LayoutGuest.Classic.topLeft(0, 800);
    line->lineColor_set(Colors::Gray);
    line->lineThickenss_set(6);
    insertChild(line);

    insertChild(eventSender);
    eventSender->LayoutGuest.Classic.top(50);
    eventSender->LayoutGuest.Classic.left(50);



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

MouseEventTestPseudoControl::~MouseEventTestPseudoControl()
{
}

void MouseEventTestPseudoControl::setTextColor(RgbaColor color)
{
    textLine_mouseClick         ->fillColor_set(color);
    textLine_mouseDoubleClick   ->fillColor_set(color);
    textLine_mouseDown          ->fillColor_set(color);
    textLine_mouseUp            ->fillColor_set(color);
    textLine_mouseWheelRotated  ->fillColor_set(color);
    textLine_mouseMove          ->fillColor_set(color);
    textLine_mouseEnter         ->fillColor_set(color);
    textLine_mouseLeave         ->fillColor_set(color);
}



MouseEventTestWindow::MouseEventTestWindow()
{
    _clickHandler =
        [this](Node* sender, MouseEventArgs* e)
    {
       if (_mouseEventChecker) 
            removeAndDeleteChild(_mouseEventChecker);

        Eleusis::Shape* l_helperVisualPrimitive = nullptr;
        
        if (dynamic_cast<Circle*>(sender)) l_helperVisualPrimitive = new Eleusis::Circle(65);
        if (dynamic_cast<Ellipse*>(sender)) l_helperVisualPrimitive = new Eleusis::Ellipse(400,200);
        if (dynamic_cast<GenericShape*>(sender))
        {
            GenericShape* l_genericShape = new Eleusis::GenericShape();
            l_genericShape->moveTo(30, 30);
            l_genericShape->lineTo(300, 50);
            l_genericShape->lineTo(350, 270);
            l_genericShape->curveTo(200, 200, 200, 200, 20, 300);
            l_genericShape->closeLine();
            l_genericShape->updateShape();
            l_helperVisualPrimitive = l_genericShape;
        }
        if (dynamic_cast<Line*>(sender))
        {
            l_helperVisualPrimitive = new Eleusis::Line(250, 250);
            l_helperVisualPrimitive->LayoutGuest.Classic.topLeft(20, 20);
        }
        if (dynamic_cast<Polygon*>(sender)) l_helperVisualPrimitive = new Eleusis::Polygon(130, 5);
        if (dynamic_cast<Rectangle*>(sender)) l_helperVisualPrimitive = new Eleusis::Rectangle(400,200);
        if (dynamic_cast<TextualShape*>(sender))
        {
            TextualShape* l_textLine = new TextualShape();
            l_textLine = new Eleusis::TextualShape();
            l_textLine->text_set("This is Eleusis.");
            l_textLine->textSize_set(85);
            l_textLine->fontFamily_set("times new roman");
            l_textLine->fontWeight_set(FontWeight::w600_Semibold);
            l_helperVisualPrimitive = l_textLine;
        }

        l_helperVisualPrimitive->fillColor_set(Colors::GoldenRod);
        l_helperVisualPrimitive->lineColor_set(Colors::PaleVioletRed);
        l_helperVisualPrimitive->lineThickenss_set(6);

        _mouseEventChecker = new MouseEventTestPseudoControl(l_helperVisualPrimitive);
        _mouseEventChecker->LayoutGuest.Classic.left(20);
        _mouseEventChecker->LayoutGuest.Classic.top(150);

        insertChild(_mouseEventChecker);
    };


    Eleusis::Rectangle* background = new Eleusis::Rectangle();
    background->fillColor_set(Colors::White);
    background->width_set(2000);
    background->height_set(1200);
    insertChild(background);

    Eleusis::Circle* l_circle = new Eleusis::Circle(15);
    l_circle->fillColor_set(Colors::DarkSeaGreen);
    l_circle->LayoutGuest.Classic.top(35);
    l_circle->LayoutGuest.Classic.left(35);
    l_circle->mouseClick += _clickHandler;
    insertChild(l_circle);

    Eleusis::Ellipse* l_ellipse = new Eleusis::Ellipse(120, 60);
    l_ellipse->fillColor_set(Colors::DarkSeaGreen);
    l_ellipse->LayoutGuest.Classic.top(35);
    l_ellipse->LayoutGuest.Classic.left(125);
    l_ellipse->mouseClick += _clickHandler;
    insertChild(l_ellipse);

    Eleusis::GenericShape* l_genericShape = new Eleusis::GenericShape();
    l_genericShape->fillColor_set(Colors::DarkSeaGreen);
    l_genericShape->moveTo(10, 10);
    l_genericShape->lineTo(90, 20);
    l_genericShape->lineTo(80, 90);
    l_genericShape->curveTo(150, 50, 50, 50, 20, 90);
    l_genericShape->closeLine();
    l_genericShape->updateShape();
    l_genericShape->LayoutGuest.Classic.top(10);
    l_genericShape->LayoutGuest.Classic.left(270);
    l_genericShape->mouseClick += _clickHandler;
    insertChild(l_genericShape);    

    Eleusis::Line* l_line = new Eleusis::Line(90, 90);
    l_line->LayoutGuest.Classic.topLeft(10, 10);
    l_line->lineColor_set(Colors::DarkSeaGreen);
    l_line->lineThickenss_set(10);
    l_line->LayoutGuest.Classic.top(10);
    l_line->LayoutGuest.Classic.left(390);
    l_line->mouseClick += _clickHandler;
    insertChild(l_line);

    Eleusis::Polygon* l_polygon = new Eleusis::Polygon(40, 5, Polygon::PolygonRadiusContext::External);
    l_polygon->fillColor_set(Colors::DarkSeaGreen);
    l_polygon->LayoutGuest.Classic.top(20);
    l_polygon->LayoutGuest.Classic.left(500);
    l_polygon->mouseClick += _clickHandler;
    insertChild(l_polygon);

    Eleusis::Rectangle* l_rectangle = new Eleusis::Rectangle(90, 45);
    l_rectangle->fillColor_set(Colors::DarkSeaGreen);
    l_rectangle->LayoutGuest.Classic.top(35);
    l_rectangle->LayoutGuest.Classic.left(610);
    l_rectangle->mouseClick += _clickHandler;
    insertChild(l_rectangle);

    Eleusis::TextualShape* l_textLine = new Eleusis::TextualShape();
    l_textLine->text_set("This is Eleusis.");
    l_textLine->textSize_set(30);
    l_textLine->fontFamily_set("times new roman");
    l_textLine->fontWeight_set(FontWeight::w600_Semibold);
    l_textLine->fillColor_set(Colors::DarkSeaGreen);
    l_textLine->LayoutGuest.Classic.top(35);
    l_textLine->LayoutGuest.Classic.left(720);
    l_textLine->mouseClick += _clickHandler;
    insertChild(l_textLine);
}