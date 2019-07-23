#include "EventsView.h"

#include <sstream>

#include "ToString.h"
#include "TextBlock.h"

using namespace Eleusis;
using namespace Eleusis::SampleApp;
using namespace std;

string EventsView::_getStringParams(MouseEventArgs* e, string senderName, string eventName)
{
    stringstream sstream;

    sstream << "Mouse event: " << eventName << "\n";
	sstream << "sent by: " << senderName << "\n";
    sstream << "-----------------------------" << "\n";
    sstream << "Alt Down: " << to_string(e->AltDown) << "\n";
    sstream << "Control Down: " << to_string(e->ControlDown) << "\n";
    sstream << "Shift Down: " << to_string(e->ShiftDown) << "\n";
    sstream << "Function Down: " << to_string(e->FunctionDown) << "\n";
    sstream << "Command Down: " << to_string(e->CommandDown) << "\n";
    sstream << "Mouse Button: " << toString(e->Button) << "\n";
    sstream << "X: " << to_string(e->X) << "\n";
    sstream << "Y: " << to_string(e->Y) << "\n";
    sstream << "Primary sender: " << e->PrimarySender << "\n";
    sstream << "-----------------------------" << "\n";

    return sstream.str();
}

string EventsView::_getStringParams(MouseScrollEventArgs* e, string senderName, string eventName)
{
    stringstream sstream;

    sstream << "Mouse event: " << eventName << "\n";
    sstream << "sent by: " << senderName << "\n";
    sstream << "-----------------------------" << "\n";
    sstream << "Alt Down: " << to_string(e->AltDown) << "\n";
    sstream << "Control Down: " << to_string(e->ControlDown) << "\n";
    sstream << "Shift Down: " << to_string(e->ShiftDown) << "\n";
    sstream << "Function Down: " << to_string(e->FunctionDown) << "\n";
    sstream << "Command Down: " << to_string(e->CommandDown) << "\n";
    sstream << "Mouse Button: " << toString(e->Button) << "\n";
    sstream << "Wheel move: " << e->WheelMove << "\n";
    sstream << "Wheel type: " << toString(e->WheelType) << "\n";
    sstream << "X: " << to_string(e->X) << "\n";
    sstream << "Y: " << to_string(e->Y) << "\n";
    sstream << "Primary sender: " << e->PrimarySender << "\n";
    sstream << "-----------------------------" << "\n";

    return sstream.str();
}

string EventsView::_getStringParams(KeyboardEventArgs* e, string senderName, string eventName)
{
    stringstream sstream;

    sstream << "Keyboard event: " << eventName << "\n";
    sstream << "sent by: " << senderName << "\n";
    sstream << "-----------------------------" << "\n";
    sstream << "Alt Down: " << to_string(e->AltDown) << "\n";
    sstream << "Control Down: " << to_string(e->ControlDown) << "\n";
    sstream << "Shift Down: " << to_string(e->ShiftDown) << "\n";
    sstream << "Function Down: " << to_string(e->FunctionDown) << "\n";
    sstream << "Command Down: " << to_string(e->CommandDown) << "\n";
    sstream << "Virtual Key: " << static_cast<int>(e->VirtualKeyCode) << "\n";
    sstream << "String: " << e->String << "\n";
    sstream << "Primary sender: " << e->PrimarySender << "\n";
    sstream << "-----------------------------" << "\n";

    return sstream.str();
}

string EventsView::_getStringParamsFromFocusEvent(string senderName, string eventName)
{
	stringstream sstream;

	sstream << "Focus event: " << eventName << "\n";
	sstream << "sent by: " << senderName << "\n";

	return sstream.str();
}


EventsView::EventsView(Length width, Length height) :
	SectionViewBase()
{
    fillColor_set(Colors::White);

    _eventData = new TextualShape();
    _eventData->LayoutGuest.Classic.topLeft(70, 20);
	_eventData->fontFamily_set("Courier");
    _eventData->text_set("EVENT DATA");
	_eventData->fillColor_set(Colors::Black);
    insertChild(_eventData);

	_focusEventData = new TextualShape();
	_focusEventData->LayoutGuest.Classic.topLeft(300, 20);
	_focusEventData->fontFamily_set("Courier");
	_focusEventData->text_set("FUCUS EVENT DATA");
	_focusEventData->fillColor_set(Colors::Black);
	insertChild(_focusEventData);

	_focusHolderData = new TextualShape();
	_focusHolderData->LayoutGuest.Classic.topLeft(350, 20);
	_focusHolderData->fontFamily_set("Courier");
	_focusHolderData->text_set("FUCUS HOLDER EVENT DATA");
	_focusHolderData->fillColor_set(Colors::Black);
	insertChild(_focusHolderData);

    Rectangle* l_rect = new Rectangle(300, 200, 10);
    l_rect->fillColor_set(Colors::OrangeRed);
    l_rect->LayoutGuest.Classic.topLeft(300, 600);
    l_rect->lineColor_set(Colors::Blue);
    l_rect->lineThickenss_set(0);
    insertChild(l_rect);

    Circle* l_circle = new Circle(60);
    l_circle->fillColor_set(Colors::MediumTurquoise);
    l_circle->LayoutGuest.Classic.topLeft(150, 600);
    l_circle->lineColor_set(Colors::Orange);
    l_circle->lineThickenss_set(0);
    insertChild(l_circle);

    Polygon* l_triangle = new Polygon(100, 3);
    l_triangle->fillColor_set(Colors::SaddleBrown);
    l_triangle->LayoutGuest.Classic.topLeft(220, 680);
    l_triangle->lineColor_set(Colors::Pink);
    l_triangle->lineThickenss_set(0);
    insertChild(l_triangle);

	_registerNode(l_rect, "Red rectangle");
    _registerNode(l_circle, "Turquise circle");
    _registerNode(l_triangle, "Brown triangle");
}

void EventsView::_registerNode(Node* node, std::string nodeName)
{
	node->enableFocus();
	node->mouseClick       += [=](Node* sender, MouseEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "mouseClick")); };
	node->mouseDoubleClick += [=](Node* sender, MouseEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "mouseDoubleClick")); };
	node->mouseDown        += [=](Node* sender, MouseEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "mouseDown")); };
	node->mouseUp          += [=](Node* sender, MouseEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "mouseUp")); };
	node->mouseEnter       += [=](Node* sender, MouseEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "mouseEnter")); };
	node->mouseLeave       += [=](Node* sender, MouseEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "mouseLeave")); };
	node->mouseMove        += [=](Node* sender, MouseEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "mouseMove")); };
	node->mouseScroll      += [=](Node* sender, MouseScrollEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "mouseScroll")); };
	node->keyDown          += [=](Node* sender, KeyboardEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "keyDown")); };
	node->keyUp            += [=](Node* sender, KeyboardEventArgs* e) { _eventData->text_set(_getStringParams(e, nodeName, "keyUp")); };
	node->gotFocus +=
		[=](Node* sender, EventArgs* e)
	{
		static_cast<Shape*>(sender)->lineThickenss_set(2);
		_focusEventData->text_set(_getStringParamsFromFocusEvent(nodeName, "gotFocus"));
		_focusHolderData->text_set("Current focus holder: " + nodeName);
	};
	node->lostFocus +=
		[=](Node* sender, EventArgs* e)
	{
		static_cast<Shape*>(sender)->lineThickenss_set(0); 
		_focusEventData->text_set(_getStringParamsFromFocusEvent(nodeName, "lostFocus"));
		_focusHolderData->text_set("Current focus holder: ");
	};
}
