#pragma once

#include "dllexport.h"

#include "Animation_Impls.h"

namespace Eleusis
{
    class ELEUSIS_API RectangleDefaultAnimation :
        public RectangleAnimation
    {
    public:    void bind  (Eleusis::Rectangle* target) = delete;
               void unbind(Eleusis::Rectangle* target) = delete;

               RectangleDefaultAnimation(Eleusis::Rectangle* target) { _animationTargets.push_back(target); };
    };

    class ELEUSIS_API EllipseDefaultAnimation :
        public EllipseAnimation
    {
    public:    void bind  (Eleusis::Ellipse* target) = delete;
               void unbind(Eleusis::Ellipse* target) = delete;

               EllipseDefaultAnimation(Eleusis::Ellipse* target) { _animationTargets.push_back(target); };
    };

    class ELEUSIS_API CircleDefaultAnimation :
        public CircleAnimation
    {
    public:    void bind  (Eleusis::Circle* target) = delete;
               void unbind(Eleusis::Circle* target) = delete;

               CircleDefaultAnimation(Eleusis::Circle* target) { _animationTargets.push_back(target); };
    };

    class ELEUSIS_API PolygonDefaultAnimation :
        public PolygonAnimation
    {
    public:    void bind  (Eleusis::Polygon* target) = delete;
               void unbind(Eleusis::Polygon* target) = delete;

               PolygonDefaultAnimation(Eleusis::Polygon* target) { _animationTargets.push_back(target); };
    };

    class ELEUSIS_API LineDefaultAnimation :
        public LineAnimation
    {
    public:    void bind  (Eleusis::Line* target) = delete;
               void unbind(Eleusis::Line* target) = delete;

               LineDefaultAnimation(Eleusis::Line* target) { _animationTargets.push_back(target); };
    };

    class ELEUSIS_API GenericShapeDefaultAnimation :
        public GenericShapeAnimation
    {
    public:    void bind  (Eleusis::GenericShape* target) = delete;
               void unbind(Eleusis::GenericShape* target) = delete;

               GenericShapeDefaultAnimation(Eleusis::GenericShape* target) { _animationTargets.push_back(target); };
    };

    class ELEUSIS_API TextualShapeDefaultAnimation :
        public TextualShapeAnimation
    {
    public:    void bind(Eleusis::TextualShape* target) = delete;
               void unbind(Eleusis::TextualShape* target) = delete;

               TextualShapeDefaultAnimation(Eleusis::TextualShape* target) { _animationTargets.push_back(target); }
    };
}