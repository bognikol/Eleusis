#pragma once

#include "dllexport.h"

#include <functional>

namespace Eleusis
{
    struct ELEUSIS_API Easing
    {
        static const std::function<double(double)> Linear;
        static const std::function<double(double)> InSine;
        static const std::function<double(double)> OutSine;
        static const std::function<double(double)> InOutSine;
        static const std::function<double(double)> InQuad;
        static const std::function<double(double)> OutQuad;
        static const std::function<double(double)> InOutQuad;
        static const std::function<double(double)> InCubic;
        static const std::function<double(double)> OutCubic;
        static const std::function<double(double)> InOutCubic;
        static const std::function<double(double)> InQuart;
        static const std::function<double(double)> OutQuart;
        static const std::function<double(double)> InOutQuart;
        static const std::function<double(double)> InQuint;
        static const std::function<double(double)> OutQuint;
        static const std::function<double(double)> InOutQuint;
        static const std::function<double(double)> InExpo;
        static const std::function<double(double)> OutExpo;
        static const std::function<double(double)> InOutExpo;
        static const std::function<double(double)> InCirc;
        static const std::function<double(double)> OutCirc;
        static const std::function<double(double)> InOutCirc;
        static const std::function<double(double)> InBack;
        static const std::function<double(double)> OutBack;
        static const std::function<double(double)> InOutBack;
        static const std::function<double(double)> InElastic;
        static const std::function<double(double)> OutElastic;
        static const std::function<double(double)> InOutElastic;
        static const std::function<double(double)> InBounce;
        static const std::function<double(double)> OutBounce;
        static const std::function<double(double)> InOutBounce;
    };
}

