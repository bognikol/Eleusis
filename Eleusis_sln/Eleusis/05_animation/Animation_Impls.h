#pragma once

#include "dllexport.h"
#include "Animation.h"

#include <list>

namespace Eleusis
{
    class Rectangle;
    class Line;
    class Circle;
    class Ellipse;
    class Polygon;
    class GenericShape;
    class TextualShape;
    class Shape;

    class ELEUSIS_API VisualPrimitiveAnimation
        : public Animation
    {
    protected: std::list<Shape*> _animationTargets;

               void _populateDefaultStartValues();
               bool _defaultStartValuesPopulated = false;

               void _updateToCurrentValues();

    public:    void bind(Shape* target);
               void unbind(Shape* target);

               virtual void clear();
               virtual void registerAnimation();

               AnimationComponent<Length>    top;
               AnimationComponent<Length>    left;
               AnimationComponent<double>    opacity;
               AnimationComponent<double>    shadowOpacity;
               AnimationComponent<Vector>    shadowDistance;
               AnimationComponent<double>    lineThickness;
               AnimationComponent<RgbaColor> fillColor;
               AnimationComponent<RgbaColor> lineColor;
    };

    class ELEUSIS_API RectangleAnimation :
        public Animation
    {
    protected: std::list<Eleusis::Rectangle*> _animationTargets;

               void _populateDefaultStartValues();
               bool _defaultStartValuesPopulated = false;

               void _updateToCurrentValues();

    public:    void bind(Eleusis::Rectangle* target);
               void unbind(Eleusis::Rectangle* target);

               virtual void clear();
               virtual void registerAnimation();

               AnimationComponent<Length>    width;
               AnimationComponent<Length>    height;
               AnimationComponent<Length>    cornerRadius;
               AnimationComponent<Length>    top;
               AnimationComponent<Length>    left;
               AnimationComponent<double>    opacity;
               AnimationComponent<double>    shadowOpacity;
               AnimationComponent<Vector>    shadowDistance;
               AnimationComponent<double>    lineThickness;
               AnimationComponent<RgbaColor> fillColor;
               AnimationComponent<RgbaColor> lineColor;
    };

    class ELEUSIS_API EllipseAnimation :
        public Animation
    {
    protected: std::list<Eleusis::Ellipse*> _animationTargets;

               void _populateDefaultStartValues();
               bool _defaultStartValuesPopulated = false;

               void _updateToCurrentValues();

    public:    void bind(Eleusis::Ellipse* target);
               void unbind(Eleusis::Ellipse* target);

               virtual void clear();
               virtual void registerAnimation();

               AnimationComponent<Length>    width;
               AnimationComponent<Length>    height;
               AnimationComponent<Length>    top;
               AnimationComponent<Length>    left;
               AnimationComponent<double>    opacity;
               AnimationComponent<double>    shadowOpacity;
               AnimationComponent<Vector>    shadowDistance;
               AnimationComponent<double>    lineThickness;
               AnimationComponent<RgbaColor> fillColor;
               AnimationComponent<RgbaColor> lineColor;
    };

    class ELEUSIS_API CircleAnimation :
        public Animation
    {
    protected: std::list<Circle*> _animationTargets;

               void _populateDefaultStartValues();
               bool _defaultStartValuesPopulated = false;

               void _updateToCurrentValues();

    public:    void bind(Circle* target);
               void unbind(Circle* target);

               virtual void clear();
               virtual void registerAnimation();

               AnimationComponent<Length>    radius;
               AnimationComponent<Length>    top;
               AnimationComponent<Length>    left;
               AnimationComponent<double>    opacity;
               AnimationComponent<double>    shadowOpacity;
               AnimationComponent<Vector>    shadowDistance;
               AnimationComponent<double>    lineThickness;
               AnimationComponent<RgbaColor> fillColor;
               AnimationComponent<RgbaColor> lineColor;
    };

    class ELEUSIS_API PolygonAnimation :
        public Animation
    {
    protected: std::list<Eleusis::Polygon*> _animationTargets;

               void _populateDefaultStartValues();
               bool _defaultStartValuesPopulated = false;

               void _updateToCurrentValues();

    public:    void bind(Eleusis::Polygon* target);
               void unbind(Eleusis::Polygon* target);

               virtual void clear();
               virtual void registerAnimation();

               AnimationComponent<Length>    radius;
               AnimationComponent<Length>    top;
               AnimationComponent<Length>    left;
               AnimationComponent<double>    opacity;
               AnimationComponent<double>    shadowOpacity;
               AnimationComponent<Vector>    shadowDistance;
               AnimationComponent<double>    lineThickness;
               AnimationComponent<RgbaColor> fillColor;
               AnimationComponent<RgbaColor> lineColor;
    };

    class ELEUSIS_API LineAnimation :
        public Animation
    {
    protected: std::list<Line*> _animationTargets;

               void _populateDefaultStartValues();
               bool _defaultStartValuesPopulated = false;

               void _updateToCurrentValues();

    public:    void bind(Line* target);
               void unbind(Line* target);

               virtual void clear();
               virtual void registerAnimation();

               AnimationComponent<Length>    endPointX;
               AnimationComponent<Length>    endPointY;
               AnimationComponent<Length>    top;
               AnimationComponent<Length>    left;
               AnimationComponent<double>    opacity;
               AnimationComponent<double>    shadowOpacity;
               AnimationComponent<Vector>    shadowDistance;
               AnimationComponent<double>    lineThickness;
               AnimationComponent<RgbaColor> fillColor;
               AnimationComponent<RgbaColor> lineColor;
    };

    class ELEUSIS_API GenericShapeAnimation :
        public Animation
    {
    protected: std::list<GenericShape*> _animationTargets;

               void _populateDefaultStartValues();
               bool _defaultStartValuesPopulated = false;

               void _updateToCurrentValues();

    public:    void bind(GenericShape* target);
               void unbind(GenericShape* target);

               virtual void clear();
               virtual void registerAnimation();

               AnimationComponent<Length>    top;
               AnimationComponent<Length>    left;
               AnimationComponent<double>    opacity;
               AnimationComponent<double>    shadowOpacity;
               AnimationComponent<Vector>    shadowDistance;
               AnimationComponent<double>    lineThickness;
               AnimationComponent<RgbaColor> fillColor;
               AnimationComponent<RgbaColor> lineColor;
    };

    class ELEUSIS_API TextualShapeAnimation :
        public Animation
    {
    protected: std::list<TextualShape*> _animationTargets;

               void _populateDefaultStartValues();
               bool _defaultStartValuesPopulated = false;

               void _updateToCurrentValues();

    public:    void bind(TextualShape* target);
               void unbind(TextualShape* target);

               virtual void clear();
               virtual void registerAnimation();

               AnimationComponent<Length>    textSize;
               AnimationComponent<Length>    letterSpacing;
               AnimationComponent<Length>    lineSpacing;
               AnimationComponent<Length>    top;
               AnimationComponent<Length>    left;
               AnimationComponent<double>    opacity;
               AnimationComponent<double>    shadowOpacity;
               AnimationComponent<Vector>    shadowDistance;
               AnimationComponent<double>    lineThickness;
               AnimationComponent<RgbaColor> fillColor;
               AnimationComponent<RgbaColor> lineColor;
    };
}