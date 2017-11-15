#include "Easing.h"
#include <functional>
#include <cmath>

using namespace Eleusis;
using namespace std;

static double _const_pi = 3.14159265358979323846;

/*
Implementation of easing functions are copied from this library:
https://github.com/AndrewRayCode/easing-utils.git
*/

const function<double(double)> Easing::Linear = [](double t) -> double
{
    return t;
};

const function<double(double)> Easing::InSine = [](double t) -> double
{
    return -1 * cos(t * (_const_pi / 2)) + 1;
};

const function<double(double)> Easing::OutSine = [](double t) -> double
{
    return sin(t * (_const_pi / 2));
};

const function<double(double)> Easing::InOutSine = [](double t) -> double
{
    return -0.5 * (cos(_const_pi * t) - 1);
};

const function<double(double)> Easing::InQuad = [](double t) -> double
{
    return t*t;
};

const function<double(double)> Easing::OutQuad = [](double t) -> double
{
    return t*(2 - t);
};

const function<double(double)> Easing::InOutQuad = [](double t) -> double
{
    return t<.5 ? 2 * t*t : -1 + (4 - 2 * t)*t;
};

const function<double(double)> Easing::InCubic = [](double t) -> double
{
    return pow(t, 3);
};

const function<double(double)> Easing::OutCubic = [](double t) -> double
{
    return (--t)*t*t + 1;
};

const function<double(double)> Easing::InOutCubic = [](double t) -> double
{
    return t<.5 ? 4 * pow(t, 3) : (t - 1)*(2 * t - 2)*(2 * t - 2) + 1;
};

const function<double(double)> Easing::InQuart = [](double t) -> double
{
    return pow(t, 4);
};

const function<double(double)> Easing::OutQuart = [](double t) -> double
{
    return 1 - (--t)*pow(t, 3);
};

const function<double(double)> Easing::InOutQuart = [](double t) -> double
{
    return t<.5 ? 8 * pow(t, 4) : 1 - 8 * (--t)*pow(t, 3);
};

const function<double(double)> Easing::InQuint = [](double t) -> double
{
    return pow(t, 5);
};

const function<double(double)> Easing::OutQuint = [](double t) -> double
{
    return 1 + (--t)*pow(t, 4);
};

const function<double(double)> Easing::InOutQuint = [](double t) -> double
{
    return t<.5 ? 16 * pow(t, 5) : 1 + 16 * (--t)*pow(t, 4);
};

const function<double(double)> Easing::InExpo = [](double t) -> double
{
    if (t == 0) return 0; 
    return pow(2, 10 * (t - 1));
};

const function<double(double)> Easing::OutExpo = [](double t) -> double
{
    if (t == 1) return 1; 
    return (pow(2, -10 * t) + 1);
};

const function<double(double)> Easing::InOutExpo = [](double t) -> double
{
    if (t == 0 || t == 1) return t;
    double scaledTime = t * 2;
    double scaledTime1 = scaledTime - 1;
    if (scaledTime < 1)  return 0.5 * pow(2, 10 * (scaledTime1));
    return 0.5 * (-pow(2, -10 * scaledTime1) + 2);
};

const function<double(double)> Easing::InCirc = [](double t) -> double
{
    double scaledTime = t / 1; 
    return -1 * (sqrt(1 - t * t) - 1);
};

const function<double(double)> Easing::OutCirc = [](double t) -> double
{
    double t1 = t - 1; 
    return sqrt(1 - t1 * t1);
};

const function<double(double)> Easing::InOutCirc = [](double t) -> double
{
    double scaledTime = t * 2;
    double scaledTime1 = scaledTime - 2;
    if (scaledTime < 1) return -0.5 * (sqrt(1 - scaledTime * scaledTime) - 1);
    return 0.5 * (sqrt(1 - scaledTime1 * scaledTime1) + 1);
};

const function<double(double)> Easing::InBack = [](double t) -> double
{
    double magnitude = 1.70158;
    double scaledTime = t / 1; 
    return scaledTime * scaledTime * ((magnitude + 1) * scaledTime - magnitude);
};

const function<double(double)> Easing::OutBack = [](double t) -> double
{
    double magnitude = 1.70158;
    double scaledTime = (t / 1) - 1; 
    return (scaledTime * scaledTime * ((magnitude + 1) * scaledTime + magnitude)) + 1;
};

const function<double(double)> Easing::InOutBack = [](double t) -> double
{
    double magnitude = 1.70158;
    double scaledTime = t * 2;
    double scaledTime2 = scaledTime - 2;
    double s = magnitude * 1.525;
    if (scaledTime < 1) return 0.5 * scaledTime * scaledTime * (((s + 1) * scaledTime) - s);
    return 0.5 * (scaledTime2 * scaledTime2 * ((s + 1) * scaledTime2 + s) + 2);
};

const function<double(double)> Easing::InElastic = [](double t) -> double
{
    double magnitude = 0.7;
    if (t == 0 || t == 1) return t;
    double scaledTime = t / 1;
    double scaledTime1 = scaledTime - 1;
    double p = 1 - magnitude;
    double s = p / (2 * _const_pi) * asin(1);
    return -(pow(2, 10 * scaledTime1) * sin((scaledTime1 - s) * (2 * _const_pi) / p));
};

const function<double(double)> Easing::OutElastic = [](double t) -> double
{
    double magnitude = 0.7;
    double p = 1 - magnitude;
    double scaledTime = t * 2;
    if (t == 0 || t == 1) return t;
    double s = p / (2 * _const_pi) * asin(1);
    return (pow(2, -10 * scaledTime) * sin((scaledTime - s) * (2 * _const_pi) / p)) + 1;
};

const function<double(double)> Easing::InOutElastic = [](double t) -> double
{
    double magnitude = 0.7;
    double p = 1 - magnitude;
    if (t == 0 || t == 1) return t;
    double scaledTime = t * 2;
    double scaledTime1 = scaledTime - 1;
    double s = p / (2 * _const_pi) * asin(1);
    if (scaledTime < 1) return -0.5 * (pow(2, 10 * scaledTime1) * sin((scaledTime1 - s) * (2 * _const_pi) / p));
    return (pow(2, -10 * scaledTime1) * sin((scaledTime1 - s) * (2 * _const_pi) / p) * 0.5) + 1;
};

const function<double(double)> Easing::InBounce = [](double t) -> double
{
    return 1 - OutBounce(1 - t);
};

const function<double(double)> Easing::OutBounce = [](double t) -> double
{
    double scaledTime = t / 1;

    if (scaledTime < (1 / 2.75))
        return 7.5625 * scaledTime * scaledTime;
    else if (scaledTime < (2 / 2.75))
    {
        double scaledTime2 = scaledTime - (1.5 / 2.75);
        return (7.5625 * scaledTime2 * scaledTime2) + 0.75;
    }
    else if (scaledTime < (2.5 / 2.75))
    {
        double scaledTime2 = scaledTime - (2.25 / 2.75);
        return (7.5625 * scaledTime2 * scaledTime2) + 0.9375;
    }
    else
    {
        double scaledTime2 = scaledTime - (2.625 / 2.75);
        return (7.5625 * scaledTime2 * scaledTime2) + 0.984375;
    }
};

const function<double(double)> Easing::InOutBounce = [](double t) -> double
{
    if (t < 0.5) return InBounce(t * 2) * 0.5;
    return (OutBounce((t * 2) - 1) * 0.5) + 0.5;
};
