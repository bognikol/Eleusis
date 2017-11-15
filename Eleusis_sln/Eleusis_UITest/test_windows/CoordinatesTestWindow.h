#pragma once

#include "Window.h"
#include "event.h"

using namespace Eleusis;

class CoordinatesTestWindow : public Window
{
    void _initializeEventHandlers() { };

    static constexpr int X_num = 5;
    static constexpr int Y_num = 5;

public:
    CoordinatesTestWindow();
}; 
