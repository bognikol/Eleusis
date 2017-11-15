#pragma once

#include "Window.h"
#include "event.h"
#include "TextBlock.h"
#include "PseudoTextBox.h"


class SampleWindow 
    : public Eleusis::Window
{
private:
    Eleusis::Rectangle* _rect = nullptr;
    Eleusis::Circle* _circ = nullptr;


public:
    SampleWindow();
    ~SampleWindow();

};



 