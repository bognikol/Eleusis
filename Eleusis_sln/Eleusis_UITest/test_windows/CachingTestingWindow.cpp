#include "CachingTestWindow.h"
#include "Colors.h"

using namespace Eleusis;
using namespace std;

CachingTestWindow::CachingTestWindow()
{
    _initializeEventHandlers();

    Eleusis::Rectangle* r0 = new Eleusis::Rectangle(2000, 1300);
    r0->fillColor_set(Colors::White);
    insertChild(r0);

    circle_1 = new Circle(25);
    circle_1->fillColor_set(Colors::Pink);
    circle_1->LayoutGuest.Classic.left(200);
    circle_1->LayoutGuest.Classic.top(100);
    insertChild(circle_1);

    ellipse_1 = new Eleusis::Ellipse(120, 60);
    ellipse_1->fillColor_set(Colors::OrangeRed);
    ellipse_1->LayoutGuest.Classic.left(300);
    ellipse_1->LayoutGuest.Classic.top(170);
    insertChild(ellipse_1);

    rectangle_1 = new Eleusis::Rectangle(80,65);
    rectangle_1->fillColor_set(Colors::MediumSpringGreen);
    rectangle_1->cornerRadius_set(10);
    rectangle_1->LayoutGuest.Classic.left(45);
    rectangle_1->LayoutGuest.Classic.top(120);
    insertChild(rectangle_1);

    polygon_1 = new Eleusis::Polygon(5, 100, Eleusis::Polygon::PolygonRadiusContext::External);
    polygon_1->fillColor_set(Colors::PaleTurquoise);
    polygon_1->LayoutGuest.Classic.left(350);
    polygon_1->LayoutGuest.Classic.top(220);
    insertChild(polygon_1);

    //Eleusis::Rectangle* r1 = new Eleusis::Rectangle(2000, 1300);
    //r1->fillColor_set(Colors::Green());
    //insertChild(r1);

    mouseUp += mouseClickHandler;
}

CachingTestWindow::~CachingTestWindow()
{

}

void CachingTestWindow::_initializeEventHandlers()
{
    mouseClickHandler = 
        [this](Window* sender, MouseEventArgs* e)
    {
        //RenderingCache cache(circle_1, polygon_1);
        //cache.layout();
        //cache._render();
        //updateFrontBuffer();

        //Eleusis::Rectangle* r1 = new Eleusis::Rectangle(2000, 1300);
        //r1->fillColor_set(Colors::Green());
        //insertChild(r1);
        //_render();


    };
}
