#include "TransformationTestWindow.h"
#include "ToString.h"

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace Eleusis::PseudoControls;
using namespace std;

TransformationTestWindow::TransformationTestWindow()
{
    Rectangle* l_background = new Rectangle(2000, 2000);
    l_background->fillColor_set(Colors::White);
    insertChild(l_background);

    Rectangle* rect = new Rectangle(400, 400);
    rect->fillColor_set(Colors::Pink);
    insertChild(rect);


    auto initializeSlider = 
        [this](PseudoSlider* slider, std::string text, double top, function<void(PseudoSlider*, EventArgs*)> handler = nullptr)
    {
        slider = new PseudoSlider();
        slider->fillColor_set(Colors::Green);
        slider->LayoutGuest.Classic.top(top);
        slider->setText(text);
        slider->LayoutGuest.Classic.left(20);
        insertChild(slider);
    };

    initializeSlider(_rotationSlider, "Top", 20);
    initializeSlider(_leftSlider, "Left", 120);
    initializeSlider(_rotationSlider, "Angle", 220);
    initializeSlider(_shearXSlider, "Shear X", 320);
    initializeSlider(_shearYSlider, "Shear Y", 420);
}