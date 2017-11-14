# Eleusis

Eleusis is aimed to be a lightweight, multiplatform pure-C++ GUI library with modern eventing architecture and layouting model.

Eleusis is far from finished. Feel free to contribute.

Download compiled sample app for Windows [here](https://github.com/bognikol/Eleusis-Sample-App-Binaries). Install Visual C++ 2015 runtime before starting the app.

## Content

* Background
* Design Goals
* Capabilities/Features
  * Current
  * Roadmap
* Getting Started
  * Build Instructions
  * My First Application
	  * Prerequestives
	  * Simplest Eleusis App
	  * Adding Content
	  * Adding Interactivity
	  * Working with (Editable) Text
	  * Animation
	  * Further Steps
* Contribute
  * Coding Guidelines

## Background

Eleusis started as a personal experiment how to create simple GUI library for C++ with modern features.

Eleusis is build upon Cairo and Pango, rendering libraries from GTK familly.

Eleusis is designed to be multiplatform; however, currently only Win32 implementation exists. 

## Design Goals

1. Modern eventing architecture using function-based publisher-subscriber pattern (C#-like).

2. Thinking multiplatform from day one.

3. Created for building highly reusable, customizable and stylable components in object-oriented fashion with strict and clear resource ownership.

4. Being lightweight. No direct dependencies except STL and rendering libraries (Pango and Cairo). Eleusis is a library not a framework.

5. Modern layouting model; support for responsiveness.

6. Rich styling out of a box.

7. HTML-like flexibility. Any UI widget can contain any other UI widget.

8. As efficient and fast as possible. Utilize CPUs at multiprocessor systems. (To be implemented)

## Capabilities/Features

### Current

* Convenient access to relevant features of OS and windowing system: Application, Window, Mouse, Keyboard, Timer. Note though that Eleusis is not intended to be a framework; system calls should be used for all accesses to OS (convenience of C++).
* Keyboard and mouse events (bubbling up the UI tree) and support for focus (element in focus receives keyboard events)
* Brushes: solid color, linear gradient, radial gradient, image. Mesh gradient to be implemented (x64 systems only)
* Primitive shapes (rectangle, circle, ellipse, polygon, line) as well as free-form and textual shapes
* Editable rich text with clipboard functionality and cascading styling
* Powerful animation engine
* Flexible and powerful layouting mechanism (wrap, stack, relative sizes, center child)
* Opacity and drop shadow (blur to be implemented - Cairo does not support it yet)

### Roadmap

* Hardening, hardening, hardening
* Switch to platform-independent build tool (CMake preferably)
* Implement basic palette of controls/widgets: TextBox, Slider, ScrollBar, Button etc.
* Implement rendering caching and rendering paralelization on multi-CPU systems
* Implement weak styling (CSS-like styling where entity has certain string identifier which acts as a key to object which holds information about requested properties of the entity)
* Writing large number of UI tests (now we have just basics)
* Large number of small and larger features and improvements

## Getting Started

### Build Instructions

1. Download and install Visual Studio 2015 with C++ tools.
2. Open Eleusis_sln/Eleusis.sln in Visual Studio.
3. Right click on SampleApp project and click on 'Set as Start Up Project'
4. Press run. Eleusis library will be build too as it is dependency of SampleApp.
5. Build should succeed, but run should fail (missing dll error). Go to /Dependencies/40_gtk+/binaries/{your selected platform} and copy all dlls to output folder /Output/{your selected config}/{your selected platform}/Eleusis_SamppleApp. Eleusis actually depends only on some of dlls copied, but for convenience copy all. Full list of dependencies view [here].
6. Press run again.

### My First Application

Very basic walk-through for creating simple UI app on Windows using Eleusis follows.

#### Prerequestives

In order to use Eleusis, you need:

(1) Eleusis.dll and Eleusis.lib which match the platform and configuration of your build

(2) Bundle of appropriate headers (which involves Eleusis as well as Pango and Cairo headers; this unfortunate feature should be updated in the future).

(3) Dependency dlls - these are Pango and Cairo dlls, as well as dlls of Pango and Cairo dependencies (although Eleusis does not have direct dependencies except STL and Cairo and Pango, Cairo and Pango do have).

The easiest way to obtain these is to download Eleusis Bootstrap app [here](https://github.com/bognikol/Eleusis-Bootstrap).

#### Simplest Eleusis App

Entry point of Eleusis app is an entry point of any Win32 GUI application:

	#include "Windows.h"

    int APIENTRY wWinMain
	    (
	    _In_     HINSTANCE hInstance,
	    _In_opt_ HINSTANCE hPrevInstance,
	    _In_     LPWSTR    lpCmdLine,
	    _In_     int       nCmdShow
	    )
    {
		return 0;
    }

This app, obviously, does not do anything. Static class Eleusis::Application is used to start event pump and to show the first window of the application.

 	#include "Windows.h"

	#include "Application.h"
	#include "Window.h" // This is the header for Eleusis::Window

	using namespace Eleusis;

    int APIENTRY wWinMain ( ... )
    {
		Application::registerInstance();

		return Application::run(new Window());
    }

If compiled and run, this app would show blank black window. We should add some content to the window. To achieve it we might either (1) make an instance of the window and configure it before passing it to the Application::run(); or (2) derive new window type from Eleusis::Window, configure it in the constructor and only then instantiate it and pass to Application::run(). The second approach has an advantage that we can easily make multiple instances of window which appear and behave the same; this is why almost all modern UI frameworks usually use it.

We can create new file called SampleWindow.h and add following code to it:

	#include "Window.h"	

	class SampleWindow :
	    public Eleusis::Window
	{
	public:
	    SampleWindow()
	    {
		};
	};

and then run application with SampleWindow instead of just Eleusis::Window:

	...
	#include "SampleWindow.h" // This is the header to Eleusis::Window
	...
    int APIENTRY wWinMain ( ... )
    {
		Application::registerInstance();

		return Application::run(new SampleWindow());
    }

If compiled and run, this app will again show blank black window; we need to add some content to it. 

#### Adding Content

Let's color the background. To achieve this we need to add an Eleusis::Rectangle which would be appropriately colored and which would stretch from edges to edges of the window. Thus, we can modify SampleWindow.h file in the following manner (for simplicity, in this tutorial function definitions are given in header files; in real  production scenarios they should be given in separate source files):

	#include "Window.h"
	#include "Rectangle.h"	

	class SampleWindow :
	    public Eleusis::Window
	{
	public:
	    SampleWindow()
	    {
			Eleusis::Rectangle* l_background = new Eleusis::Rectangle(100._FPs, 100._FPs);
	        l_background->fillColor_set(Eleusis::Colors::White);
	        insertChild(l_background);
		};
	};

Here we initiate Rectangle calling its constructor; constructor accepts two Eleusis::Length objects, here initiated initiated using literal operators. Eleusis::Length currently has two implementations: (1) Eleusis::FractionLength, used to specify relative lengths (can be initiated with suffix _FPs - meaning fraction points); and  (2) Eleusis::DeviceIndependentLength used to specify absolute lengths (can be initiated with suffix _DIPs - meaning device independent points - or omitting suffix all together). In this situation, we want a Rectangle to stretch 100% of both width and height of the parent window. After initiating, we set Rectangle's color to Eleusis::Colors::White, which is a constant for Eleusis::RgbaColor object that represents white. And we call Eleusis::Window::insertChild() to actually add a Rectangle to the window.

If compiled and run, the app will again show a window, but the window should be completely white (apart from the border).

You may notice that in this example we use raw pointer for a Rectangle rather then std::shared_ptr. Actually, Eleusis uses shared pointers only in situations where object is explicitly intended to be shared among objects and not to have single owner (for example, when multiple Rectangles share Brush which points to same picture). In situations where object have single owner, raw pointers are used. (Using shared pointers should not be a replacement for proper memory management strategy; however, this design decision have a lot drawbacks.)

Ownership rules in Eleusis are very clear and strict: an element in GUI tree owns all its children. This rule is extended to Eleusis::Windows too, which means that Rectangle is explicitly owned by a SampleWindow after the point when insertChild() is called; Rectangle will be automatically destructed when SampleWindow is destructed; SampleWindow stops owning a Rectangle once it is removed from it (calling Eleusis::Window::removeChild(), for example); then, again, Rectangle is owned by the developer who is responsible to manage its lifetime and destruction.

Now, let's add a circle to the SampleWindow. Add this snippet at the end of the constructor:

    Eleusis::Circle* l_circle = new Eleusis::Circle(30);
    l_circle->fillColor_set(Eleusis::Colors::OrangeRed);
    l_circle->LayoutGuest.Classic.topLeft(200, 80);
    insertChild(l_circle);

We add an orange-red circle of radius 30 (of device independent points which are usually pixels) at the position 200 pixels from the top of the window and 80 pixels from the left of the window.

Here we introduce layouting: positioning elements inside a window or inside other elements. Each UI element have two different layouting roles which are independent: LayoutGuest and LayoutHost. Set of functions under LayoutGuest   are used to specify how the element should position itself inside its parent; on the other hand, set of functions under LayoutHost are used to specify global rules how children should be positioned inside the element. Only when both LayoutGuest options of a child and LayoutHost options of a parent are specified, size and position of child can be determined. At this point we do not have time to explore Eleusis layouting APIs, but will note that LayoutGuest.Classic.topLeft() function sets top-left position of an element within the parent.

#### Adding Interactivity

But what about interactivity? How to make the Circle change its color when mouse cursor hovers over? 

Eleusis offers its own simple implementation of function-based publisher-subscriber eventing pattern inspired by event-delegate mechanism in .NET languages. In essence, events are strongly-typed ordered collections of handlers (std::function objects) which are sequentially called when event is raised. Generally, adding handler to an event follows following pattern:
	
	element->eventName += handler;

where handler is some std::function object of appropriate type. UI elements in Eleusis (whose actual type is Eleusis::Node) natively support following events: mouseClick, mouseDoubleClick, mouseDown, mouseUp, mouseEnter, mouseLeave and mouseMove. Apart from mouse events, Eleusis supports keyboard events: keyDown and keyUp; however, these events are raised only on elements which currently own the focus.

For example, if we want to handle event of mouse entering the circle, we can write code like this:

	l_circle->mouseEnter +=
	    [l_circle](Node* sender, MouseEventArgs* e)
	{
	    l_circle->fillColor_set(Colors::RoyalBlue);
	};

std::function object we add as a handler does not need to be a lambda like in an example above; it can be any std::function object of appropriate type. We also need to be cautious of variable lifespans when capturing variables in lambdas or binding them using std::bind.

Handler types are not arbitrary; handlers always return void and receives two arguments: sender argument (which should be a pointer to object which raised the event) and event data argument (which is a pointer to a structure that contains additional data about the event).

To restore color of circle when mouse leaves, we can use following code:

	 l_circle->mouseLeave +=
	    [l_circle](Node* sender, MouseEventArgs* e)
	{
	    l_circle->fillColor_set(Colors::OrangeRed);
	};

#### Working with (Editable) Text

Eleusis tries to offer rich-text editing functionality. Eleusis::TextBlock is basic text object in Eleusis. TextBlock is made of Eleusis::Paragraphs, and paragraphs consist of Eleusis::Spans. Span is an array of characters that have same rendering parameters.

Eleusis::TextBlock is, as name suggests, a version of TextBlock which supports editing and selection. To add it to our window, we should add following code:

	SelectEdit* l_se = new SelectEdit();
	l_se->height_set(200);
	l_se->width_set(200);
	l_se->setText("Edit me and then click orange circle!");
	l_se->LayoutGuest.Classic.topLeft(20, 20);
	insertChild(l_se);

SelectEdit is editable by default. If compiled and run, our app will show a window with text which can be selected using mouse cursor and edited using keyboard. However, SelectEdit lacks large number of feature which modern UIs conveniently offer, for example selecting a word with a double click.

Let's give some purpose to our round button:

    l_circle->mouseClick +=
        [l_se](Node* sender, MouseEventArgs* e)
    {
        Application::nativeMsgBox(l_se->getText());
    };

#### Animation

Eleusis also incorporates quite powerful animation engine. To demonstrate how animation works in Eleusis, let's add a polygon and then define animation which should happen when double clicked:

	Eleusis::Polygon* l_poly = new Eleusis::Polygon(50, 5);
	l_poly->fillColor_set(Colors::BurlyWood);
	l_poly->LayoutGuest.Classic.topLeft(150, 500);
	insertChild(l_poly);
	
	l_poly->mouseClick +=
	    [l_poly](Node* sender, MouseEventArgs* e)
	{
	    l_poly->animate()->radius.endValue(1000);
	    l_poly->animate()->duration_set(5000);
	    l_poly->animate()->restart();
	};

To animate things in Eleusis, Animation objects need to be used. There are two ways to work with them: (1) using default animation object each UI element has (it is accessed through animate() property), or (2) using freestanding animation objects which are then bound to specific UI elements we want to animate. Major difference is in memory management: default animation object is exclusively owned by UI element; however, freestanding animation allows us to run same animation upon several UI elements simultaneously and to reuse them.

Example above is quite self-explanatory. Note, however, that start value of radius is not defined; in these situations Eleusis will take current value as a start value.

#### Further steps

Although Eleusis offers vast range of visual primitives, it does not contain key building blocks of UI - controls (in Microsoft terminology) or widgets (in GTK terminology) - which are essentially encapsulated reusable systems of visual primitives with well defines behavior enabling rapid UI development. Example of controls are text box, radio button, button, combo box, select box, progress bar. Nucleus of control infrastructure in Eleusis is implemented through Eleusis::Control and Eleusis::SkinableControl classes, but there is large amount of work to be done to provide a proper pallet of UI controls. 

## Contribute

You are welcomed to contribute :-)

### Coding guidelines

Few simple guidelines:

1. Use camel case with first letter lowercase.

2. Use [Allman indentation style](https://en.wikipedia.org/wiki/Indentation_style#Allman_style).

3. Names of all private and protected class members should start with underscore (for example _\_node_).

4. Names of all local variables should start with prefix _l\__ (for example _l\_node_).

5. Prefer pointers over references, unless unnatural.

6. Use _#pragma region_ to split large files in meaningful sections.
