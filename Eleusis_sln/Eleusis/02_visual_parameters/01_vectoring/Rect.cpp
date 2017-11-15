#include "Rect.h"
#include <cmath>

using namespace Eleusis;
using namespace std;

Rect::Rect() :
    lowVector (),
    highVector()
{
}

Rect::Rect(Vector lowVect, Vector highVect) :
    lowVector (lowVect),
    highVector(highVect)
{
}

Rect::Rect(double x_low, double y_low, double x_high, double y_high)
{
    lowVector.X  = x_low;
    lowVector.Y  = y_low;
    highVector.X = x_high;
    highVector.Y = y_high;
}

bool Rect::contains(Vector vector)
{
    if (lowVector  < vector &&
        highVector > vector)
        return true;

    return false;
}

bool Rect::contains(double x, double y)
{
    return contains(Vector(x, y));
}

Vector Rect::sizeVector()  
{ 
    return highVector - lowVector; 
}

double Rect::width() 
{ 
    return sizeVector().X; 
}

double Rect::height() 
{ 
    return sizeVector().Y; 
}

bool Rect::isPositive()
{
    return lowVector < highVector;
}

void Rect::format()
{
    if (!isPositive())
    {
        lowVector  = Vector(0, 0);
        highVector = Vector(0, 0);
    }
}

void Rect::integral()
{
	lowVector.X  = floor(lowVector.X);
	lowVector.Y  = floor(lowVector.Y);
	highVector.X = floor(highVector.X) + 1;
	highVector.Y = floor(highVector.Y) + 1;
}

bool Rect::operator == (const Rect r) const
{
    return highVector == r.highVector && lowVector == r.lowVector;
}

Rect Rect::operator & (Rect r)
{
    return Rect(lowVector | r.lowVector, highVector & r.highVector);
}

Rect Rect::operator | (Rect r)
{
    return Rect(lowVector & r.lowVector, highVector | r.highVector);
}

void Rect::operator &= (Rect r)
{
    lowVector  = lowVector  | r.lowVector;
    highVector = highVector & r.highVector;
}

void Rect::operator |= (Rect r)
{
    lowVector  = lowVector  & r.lowVector;
    highVector = highVector | r.highVector;
}

Rect Rect::operator && (Rect r)
{
    Rect l_rect = *this & r;
    if (l_rect.wellFormed()) return l_rect;
    return Rect();
}

void Rect::operator >> (Vector v)
{
    lowVector  = lowVector  + v;
    highVector = highVector + v;
}

void Rect::operator << (Vector v)
{
    highVector = highVector + v;
}

// Intersection operatror
// Returns true if and only if two rectanlges intersect

bool Rect::operator % (Rect r)
{
    return
        ((  lowVector.X < r.lowVector.X  && r.lowVector.X  <   highVector.X) ||
         (  lowVector.X < r.highVector.X && r.highVector.X <   highVector.X) ||
         (r.lowVector.X <   lowVector.X  && lowVector.X    < r.highVector.X) ||
         (r.lowVector.X <   highVector.X && highVector.X   < r.highVector.X))
        &&
        ((  lowVector.Y < r.lowVector.Y  && r.lowVector.Y  <   highVector.Y) ||
         (  lowVector.Y < r.highVector.Y && r.highVector.Y <   highVector.Y) ||
         (r.lowVector.Y <   lowVector.Y  &&   lowVector.Y  < r.highVector.Y) ||
         (r.lowVector.Y <   highVector.Y &&   highVector.Y < r.highVector.Y))
    ;
}

