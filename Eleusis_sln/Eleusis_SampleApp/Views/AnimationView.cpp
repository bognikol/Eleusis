#include "AnimationView.h"
#include "Shape.h"
#include "Timeline.h"

using namespace Eleusis;
using namespace Eleusis::SampleApp;
using namespace std;



class ExpandingCircle :
    public Circle
{
    Timeline* _timeline = nullptr;
    static const vector<RgbaColor> _colors;

public:
    ExpandingCircle() :
        Circle(24)
    {
        fillColor_set(_colors[rand() % 10]);

        CircleAnimation* l_animExpand = new CircleAnimation();
        l_animExpand->bind(this);
        l_animExpand->radius.endValue(100);
        l_animExpand->easing_set(Easing::OutQuint);
        l_animExpand->duration_set(2000);

        CircleAnimation* l_animContract = new CircleAnimation();
        l_animContract->bind(this);
        l_animContract->radius.startValue(100);
        l_animContract->radius.endValue(24);
        l_animContract->easing_set(Easing::InOutQuint);
        l_animContract->duration_set(3000);
        l_animContract->delay_set(2000);

        _timeline = new Timeline();
        _timeline->addAnimation(l_animExpand);
        _timeline->addAnimation(l_animContract);

        mouseEnter +=
            [this](Node* sender, EventArgs* e)
        {
            if (!_timeline->isRunning())
            {
                zCoordinate_set(UINT_MAX);
                _timeline->reset();
                _timeline->start();
            }
        };
    }

    ~ExpandingCircle()
    {
        delete _timeline;
    }
};

const vector<RgbaColor> ExpandingCircle::_colors = {
    Colors::OrangeRed, Colors::Magenta,  Colors::SpringGreen, Colors::Gray, Colors::DarkRed,
    Colors::Green, Colors::Turquoise, Colors::DeepSkyBlue, Colors::Pink, Colors::Gold
};

AnimationView::AnimationView()
{
	fillColor_set(Colors::White);

    Container* l_innerContainer = new Container(800, 600);
    l_innerContainer->LayoutGuest.Classic.topLeft(50._FPs, 50._FPs);
    l_innerContainer->LayoutGuest.Classic.anchorTopLeft(50._FPs, 50._FPs);
    insertChild(l_innerContainer);

    for (int i = 0; i <= 15; i++)
    {
        for (int j = 0; j <= 11; j++)
        {
            Circle* l_circ = new ExpandingCircle();
            l_circ->LayoutGuest.Classic.topLeft(j * 50 + 25, i * 50 + 25);
            l_circ->LayoutGuest.Classic.anchorTopLeft(50._FPs, 50._FPs);
            
            l_innerContainer->insertChild(l_circ);
        }
    }
}


