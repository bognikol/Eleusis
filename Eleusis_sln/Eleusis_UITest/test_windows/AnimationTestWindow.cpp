#include "AnimationTestWindow.h"
#include "Colors.h"

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace Eleusis::PseudoControls;
using namespace std;

AnimationTestControl::AnimationTestControl(Animation* anim, string name)
{
    //if (!anim) throw new exception("anim parameter must not be null.");

    _animation = anim;

    height_set(50);
    width_set(650);
    fillColor_set(Colors::Wheat);



    _nameTxtBlck = new TextBlock();
    _nameTxtBlck->setText(name);
    _nameTxtBlck->LayoutGuest.Classic.top(15);
    _nameTxtBlck->LayoutGuest.Classic.left(10);
    insertChild(_nameTxtBlck);

    _delayTxtBx = new PseudoTextBox();
    _delayTxtBx->setText(to_string(_animation->delay_get()));
    _delayTxtBx->setWidth(60);
    _delayTxtBx->LayoutGuest.Classic.top(10);
    _delayTxtBx->LayoutGuest.Classic.left(80);
    _delayTxtBx->textChanged +=
        [this](PseudoTextBox* sender, EventArgs* e)
    {
        _animation->delay_set(stoi(_delayTxtBx->getText()));
    };
    insertChild(_delayTxtBx);

    _durationTxtBx = new PseudoTextBox();
    _durationTxtBx->setText(to_string(_animation->duration_get()));
    _durationTxtBx->setWidth(60);
    _durationTxtBx->LayoutGuest.Classic.top(10);
    _durationTxtBx->LayoutGuest.Classic.left(150);
    _durationTxtBx->textChanged +=
        [this](PseudoTextBox* sender, EventArgs* e)
    {
        _animation->duration_set(stoi(_durationTxtBx->getText()));
    };
    insertChild(_durationTxtBx);

    _startButton = new PseudoButton();
    _startButton->setText("Start");
    _startButton->setWidth(60);
    _startButton->LayoutGuest.Classic.top(10);
    _startButton->LayoutGuest.Classic.left(220);
    _startButton->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        _animation->start();
    };
    insertChild(_startButton);

    _stopButton = new PseudoButton();
    _stopButton->setText("Stop");
    _stopButton->setWidth(60);
    _stopButton->LayoutGuest.Classic.top(10);
    _stopButton->LayoutGuest.Classic.left(290);
    _stopButton->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        _animation->stop();
    };
    insertChild(_stopButton);

    _resetButton = new PseudoButton();
    _resetButton->setText("Reset");
    _resetButton->setWidth(60);
    _resetButton->LayoutGuest.Classic.top(10);
    _resetButton->LayoutGuest.Classic.left(360);
    _resetButton->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        _animation->reset();
    };
    insertChild(_resetButton);

    _toPointTxtBx = new PseudoTextBox();
    _toPointTxtBx->setText("");
    _toPointTxtBx->setWidth(60);
    _toPointTxtBx->LayoutGuest.Classic.top(10);
    _toPointTxtBx->LayoutGuest.Classic.left(430);
    _toPointTxtBx->textChanged +=
        [this](PseudoTextBox* sender, EventArgs* e)
    {
        _animation->toPoint((long long)stoi(_toPointTxtBx->getText()));
    };
    insertChild(_toPointTxtBx);

    _repetitionTxtBx = new PseudoTextBox();
    _repetitionTxtBx->setText("O");
    _repetitionTxtBx->setWidth(60);
    _repetitionTxtBx->LayoutGuest.Classic.top(10);
    _repetitionTxtBx->LayoutGuest.Classic.left(500);
    _repetitionTxtBx->textChanged +=
        [this](PseudoTextBox* sender, EventArgs* e)
    {
        if (_repetitionTxtBx->getText() == "O") _animation->repetition_set(AnimationRepetition::Once);
        else                                    _animation->repetition_set(AnimationRepetition::Forever);
    };
    insertChild(_repetitionTxtBx);

    _resetButton = new PseudoButton();
    _resetButton->setText("Reverse");
    _resetButton->setWidth(60);
    _resetButton->LayoutGuest.Classic.top(10);
    _resetButton->LayoutGuest.Classic.left(570);
    _resetButton->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        _animation->reverse();
    };
    insertChild(_resetButton);

}


TimelineTestControl::TimelineTestControl(Timeline* anim, string name)
{
    //if (!anim) throw new exception("anim parameter must not be null.");

    _animation = anim;

    height_set(50);
    width_set(650);
    fillColor_set(Colors::Wheat);
    
    _nameTxtBlck = new TextBlock();
    _nameTxtBlck->setText(name);
    _nameTxtBlck->LayoutGuest.Classic.top(15);
    _nameTxtBlck->LayoutGuest.Classic.left(10);
    insertChild(_nameTxtBlck);

    _startButton = new PseudoButton();
    _startButton->setText("Start");
    _startButton->setWidth(60);
    _startButton->LayoutGuest.Classic.top(10);
    _startButton->LayoutGuest.Classic.left(220);
    _startButton->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        _animation->start();
    };
    insertChild(_startButton);

    _stopButton = new PseudoButton();
    _stopButton->setText("Stop");
    _stopButton->setWidth(60);
    _stopButton->LayoutGuest.Classic.top(10);
    _stopButton->LayoutGuest.Classic.left(290);
    _stopButton->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        _animation->stop();
    };
    insertChild(_stopButton);

    _resetButton = new PseudoButton();
    _resetButton->setText("Reset");
    _resetButton->setWidth(60);
    _resetButton->LayoutGuest.Classic.top(10);
    _resetButton->LayoutGuest.Classic.left(360);
    _resetButton->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        _animation->reset();
    };
    insertChild(_resetButton);

    _repetitionTxtBx = new PseudoTextBox();
    _repetitionTxtBx->setText("O");
    _repetitionTxtBx->setWidth(60);
    _repetitionTxtBx->LayoutGuest.Classic.top(10);
    _repetitionTxtBx->LayoutGuest.Classic.left(500);
    _repetitionTxtBx->textChanged +=
        [this](PseudoTextBox* sender, EventArgs* e)
    {
        if (_repetitionTxtBx->getText() == "O") _animation->repetition_set(AnimationRepetition::Once);
        else                                    _animation->repetition_set(AnimationRepetition::Forever);
    };
    insertChild(_repetitionTxtBx);

}

AnimationTestWindow::AnimationTestWindow()
{
	l_background = new Eleusis::Rectangle(2000,1200);
	l_background->fillColor_set(Colors::White);
	insertChild(l_background);


	_rectangle1 = new Eleusis::Rectangle(50, 50);
	_rectangle1->LayoutGuest.Classic.top(50);
	_rectangle1->LayoutGuest.Classic.left(50);
	_rectangle1->fillColor_set(Colors::PapayaWhip);
	insertChild(_rectangle1);

	_rectangle2 = new Eleusis::Rectangle(50, 50);
	_rectangle2->LayoutGuest.Classic.top(150);
	_rectangle2->LayoutGuest.Classic.left(50);
	_rectangle2->fillColor_set(Colors::Purple);
	insertChild(_rectangle2);

	_rectangle3 = new Eleusis::Rectangle(50, 50);
	_rectangle3->LayoutGuest.Classic.top(250);
	_rectangle3->LayoutGuest.Classic.left(50);
	_rectangle3->fillColor_set(Colors::DeepPink);
	insertChild(_rectangle3);

    _rectAnimation1 = new RectangleAnimation();
    _rectAnimation1->duration_set(2000);
    _rectAnimation1->width.endValue(400);
    _rectAnimation1->bind(_rectangle1);

    _animationControl1 = new AnimationTestControl(_rectAnimation1, "anim1");
    _animationControl1->LayoutGuest.Classic.left(600);
    _animationControl1->LayoutGuest.Classic.top(50);
    insertChild(_animationControl1);

    _rectAnimation2 = new RectangleAnimation();
    _rectAnimation2->duration_set(2000);
    _rectAnimation2->delay_set(1000);
    _rectAnimation2->width.endValue(400);
    _rectAnimation2->bind(_rectangle2);

    _animationControl2 = new AnimationTestControl(_rectAnimation2, "anim2");
    _animationControl2->LayoutGuest.Classic.left(600);
    _animationControl2->LayoutGuest.Classic.top(150);
    insertChild(_animationControl2);

    _rectAnimation3 = new RectangleAnimation();
    _rectAnimation3->duration_set(2000);
    _rectAnimation3->delay_set(2000);
    _rectAnimation3->width.endValue(400);
    _rectAnimation3->bind(_rectangle3);

    _animationControl3 = new AnimationTestControl(_rectAnimation3, "anim3");
    _animationControl3->LayoutGuest.Classic.left(600);
    _animationControl3->LayoutGuest.Classic.top(250);
    insertChild(_animationControl3);

    _timeline1 = new Timeline();
    _timeline1->addAnimation(_rectAnimation1);
    _timeline1->addAnimation(_rectAnimation2);

    _timelineControl1 = new TimelineTestControl(_timeline1, "tml1");
    _timelineControl1->LayoutGuest.Classic.left(600);
    _timelineControl1->LayoutGuest.Classic.top(350);
    insertChild(_timelineControl1);

    _timeline2 = new Timeline();
    _timeline2->addAnimation(_timeline1);
    _timeline2->addAnimation(_rectAnimation3);

    _timelineControl2 = new TimelineTestControl(_timeline2, "tml2");
    _timelineControl2->LayoutGuest.Classic.left(600);
    _timelineControl2->LayoutGuest.Classic.top(450);
    insertChild(_timelineControl2);

    _circle = new Circle(50);
    _circle->fillColor_set(Colors::YellowGreen);
    _circle->LayoutGuest.Classic.topLeft(600, 100);

    insertChild(_circle);

    _circle->mouseClick +=
        [this](Node* sender, EventArgs* e)
    {
        //_circle->fillColor_set(Colors::Blue());
        CircleAnimation* l_circleAnimation = new CircleAnimation();
        l_circleAnimation->bind(_circle);
        l_circleAnimation->duration_set(1000);
        l_circleAnimation->delay_set(0);
        l_circleAnimation->fillColor.startValue(Colors::YellowGreen);
        l_circleAnimation->fillColor.endValue(Colors::Red);
        l_circleAnimation->start();
    };
}
