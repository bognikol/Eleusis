#include "Vector.h"
#include "Rect.h"

#include <algorithm>

using namespace Eleusis;
using namespace std;

Vector::Vector(double x, double y) :
    X(x),
    Y(y)
{
}

bool Vector::isZero()
{
    return X == 0 && Y == 0;
}

Vector Vector::operator - ()
{
    return Vector(-X, -Y);
}

bool Vector::operator == (const Vector v) const
{
    return X == v.X && Y == v.Y;
}

bool Vector::operator < (Vector v)
{
    return X < v.X && Y < v.Y;
}

bool Vector::operator > (Vector v)
{
    return X > v.X && Y > v.Y;
}

bool Vector::operator <= (Vector v)
{
    return X <= v.X && Y <= v.Y;
}

bool Vector::operator >= (Vector v)
{
    return X >= v.X && Y >= v.Y;
}

bool Vector::operator != (Vector v)
{
    return X != v.X || Y != v.Y;
}

Vector Vector::operator + (Vector v)
{
    return Vector(X + v.X, Y + v.Y);
}

Vector Vector::operator - (Vector v)
{
    return Vector(X - v.X, Y - v.Y);
}

void Vector::operator += (Vector v)
{
    X += v.X;
    Y += v.Y;
}

void Vector::operator -= (Vector v)
{
    X -= v.X;
    Y -= v.Y;
}

Vector Vector::operator & (Vector v)
{
    return Vector(min(X, v.X), min(Y, v.Y));
}

Vector Vector::operator | (Vector v)
{
    return Vector(max(X, v.X), max(Y, v.Y));
}

void Vector::operator &= (Vector v)
{
    X = min(X, v.X);
    Y = min(Y, v.Y);
}

void Vector::operator |= (Vector v)
{
    X = max(X, v.X);
    Y = max(Y, v.Y);
}

Rect Vector::operator * (Vector highVector)
{
    return Rect(*this, highVector);
}

Rect Vector::operator ^ (Vector sizeVector)
{
    return Rect(*this, *this + sizeVector);
}