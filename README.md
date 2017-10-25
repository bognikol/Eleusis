# Eleusis

Eleusis is a lightweight, multiplatform pure-C++ GUI library with modern eventing archtecture and layouting model.

Eleusis is far from finished. Feel free to contribute.

Download compiled sample app for Windows [here]. Install Visual C++ 2015 runtime before starting the app.

## Where I Want to Go from Here

* Background
* Design Goals
* Capabilities/Features
  * Current
  * Roadmap
* Getting Started
  * Build Instructions
  * My First Application
* Contribute
  * Coding Guidelines

## Background

Eleusis started as a personal experiment how to create simple GUI library for C++ with modern features.

Eleusis is build upon Cairo and Pango, rendering libraried from GTK familly.

Eleusis is designed to be multiplatform; however, currently only Win32 implementation exists. 

## Design Goals

1. Modern eventing architecture using function-based publisher-subscriber pattern (C#-like).

2. Thinking multiplatform from day one.

3. Created for building highly reusable, customizable and stylable components in object-oriented fashion with strict and clear resource ownership.

4. Being lightweight. No direct dependencies except STL and rendering libraries (Pango and Cairo). Eleusis is a libary not a framework.

5. Modern layouting model; support for responsivnes.

6. Rich styling out of a box.

7. HTML-like fexibility. Any UI widget can contain any other UI widget.

8. As efficient and fast as possible. Utilize CPUs at multiprocessor systems. (To be implemented)

## Capabilities/Features

### Current

* Convinient access to relevant features of OS and windowing system: Application, Window, Mouse, Keyboard, Timer. Note though that Eleusis is not intended to be a framework; system calls should be used for all accesses to OS (convenience of C++).
* Keyboard and mouse events (bubling up the UI tree) and support for focus (element in focus receives keyboard events)
* Brushes: solid color, linear gradient, radial gradient, image. Mesh gradient to be implemented (x64 systems only)
* Primitive shapes (rectangle, circle, ellipse, polygon, line) as weel as free-form and textual shapes
* Editable rich text with clipboard functionality and cascading styling
* Powerful animation engine
* Flexible and powerful layouting mechanism (wrap, stack, relative sizes, center child)
* Opacity and drop shadow (blur to be implemented - Cairo does not support it yet)

### Roadmap

* Hardening, hardening, hardening
* Switch to platform-independant build tool (CMake preferably)
* Implement basic pallette of controls/widgets: TextBox, Slider, ScrollBar, Button etc.
* Implement rendering caching and rendering paralilization on multi-CPU systems
* Implement weak styling (CSS-like styling where entity has certain string indentifier which acts as a key to object which holds information about requested properties of the entity)
* Writting large number of UI tests (now we have just basics)
* Large number of small and larger features and improvments

## Getting Started

### Build Instructions

1. Download and install Visual Studio 2015 with C++ tools.
2. Open Eleusis_sln/Eleusis.sln in Visual Studio.
3. Right click on SampleApp project and click on 'Set as Start Up Project'
4. Press run. Eleusis library will be build too as it is dependecy of SampleApp.
5. Build should succeed, but run should fail (missing dll error). Go to /Dependencies/40_gtk+/binaries/{your selected platform} and copy all dlls to output folder /Output/{your selected config}/{yout selected platform}/Eleusis_SamppleApp. Eleusis actually depends only on some of dlls copied, but for convinience copy all. Full list of dependencies view [here].
6. Press run again.

### My First Application

## Contribute

You are welcomed to contribute :-)

### Coding guidelines

Few siple guidelines:

1. Use camel case with first letter lowercase.

2. Use [Allman indendation style].

3. Names of all private and protected class members should start with underscore (for example _\_node_).

4. Names of all local variables should start with prefix _l_ _ (for example l_node).

5. Prefer pointers over references (no specific reason; I find pointers more truthful then referencies which are wrapped pointers; so let's stay consistent :-)).
