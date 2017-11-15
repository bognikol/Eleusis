#pragma once

namespace Eleusis
{
    class Shape;
    class Animation;
    class Node;
    class VisualPrimitive;
    struct Rect;

    class UIContext
    {
    public:  virtual cairo_t* getCairoContext() = 0;

             virtual void     notifyModelChange(Node* node, bool layoutParamChanged, bool geometryParamChanged, bool renderingParamChanged, Rect* additionaRenderingRect = nullptr) = 0;

             virtual void     registerAnimation(Animation* animation) = 0;
             virtual Rect     surfaceSize() = 0;

             virtual void     setFocus(Node* focus) = 0;
    };
}
