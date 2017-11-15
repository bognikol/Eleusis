#pragma once

#include "Window.h"
#include "event.h"

class CachingTestWindow : public Eleusis::Window
{
    void _initializeEventHandlers();

public:
    CachingTestWindow();
    ~CachingTestWindow();

    std::shared_ptr<Eleusis::Brush>     solidColorBrush1;
    std::shared_ptr<Eleusis::Brush>     solidColorBrush2;
    std::shared_ptr<Eleusis::Brush>     solidColorBrush3;
    std::shared_ptr<Eleusis::Brush>     linearGradientBrush;
    std::shared_ptr<Eleusis::Brush>     radialGradientBrush;

    Eleusis::Circle* circle_1;
    Eleusis::Circle* circle_2;
    Eleusis::Circle* circle_3;

    Eleusis::Rectangle* rectangle_1;
    Eleusis::Rectangle* rectangle_2;
    Eleusis::Rectangle* rectangle_3;

    Eleusis::Ellipse* ellipse_1;
    Eleusis::Ellipse* ellipse_2;
    Eleusis::Ellipse* ellipse_3;

    Eleusis::Polygon* polygon_1;
    Eleusis::Polygon* polygon_2;
    Eleusis::Polygon* polygon_3;

    std::function<void(Window*, Eleusis::MouseEventArgs*)> mouseClickHandler;
    std::function<void(Window*, Eleusis::MouseEventArgs*)> mouseMoveHandler;
};