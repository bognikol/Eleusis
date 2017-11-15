#pragma once

#include "Node.h"

namespace Eleusis
{
    class RootNode
        : public Node
    {

    public:     RootNode()
                {
                    _clipping = true;
                }

                void setContext(UIContext* uiContext); //added

                void         zCoordinate_set(unsigned int zCoordinate) = delete;
                unsigned int zCoordinate_get() = delete;

                void insertAfter(Node* node) = delete;
                void insertBefore(Node* node) = delete;
                //not deleted: void insertChild(Node* node);
                //not deleted: void insertChild(Node* node, unsigned int zCoordinate);
                void remove() = delete;
                //not deleted: void removeChild(Node* node);
                //not deleted: void removeAndDeleteChild(Node* & node);


                //not deleted: Node* next();
                //not deleted: Node* previous();

                Node* nextSibling() = delete;
                Node* previousSibling() = delete;

                //not deleted: Node* firstChild();
                //not deleted: Node* lastChild();

                Node* parent() = delete;

                virtual Rect getFullExtent();

                //not deleted: void* getContext() { return _context; };

                //not deleted: Vector getApsoluteOffsetVector() { return _apsoluteOffsetVector; };
                //not deleted: Vector getRelativeOffsetVector() { return _relativeOffsetVector; };
                //not deleted: Vector getAbsoluteSizeVector() { return _absoluteSizeVector; };

                void enableFocus() = delete;
                void disableFocus() = delete;
                bool isFocusable() = delete;
                bool inFocus() = delete;
                void focus() = delete;

                void visibility_set(bool visibility) = delete;
                bool visibility_get() = delete;

                virtual void _layout();
                virtual void _applyAbsoluteOffset();

                void setAbsoluteSizeVector(Vector sizeVector)
                {
                    _absoluteSizeVector = sizeVector;
                    _requestLayout();
                };

                virtual void requestRendering() { };
                virtual void requestRendering(Region* region) { };

                virtual void _render(Region* region);
    };
}