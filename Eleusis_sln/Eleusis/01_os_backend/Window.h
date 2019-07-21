#pragma once

#include "dllexport.h"

#include "IOEventTypes.h"
#include "RootNode.h"
#include "Shape.h"
#include "AnimationManager.h"
#include "Mouse.h"

#include <string>
#include <set>

namespace Eleusis
{
    struct WindowOSBundle;

    class ELEUSIS_API Window :
        public UIContext
    {
    private:    WindowOSBundle*   _windowOSBundle   = nullptr;
        
                cairo_t*          _cairoContext     = nullptr;
                cairo_surface_t*  _cairoSurface     = nullptr;
                RootNode*         _root             = nullptr;
                AnimationManager* _animationManager = nullptr;

                VisualPrimitive* _lastMouseDownVisualPrimitive = nullptr;
                VisualPrimitive* _lastMouseMoveVisualPrimitive = nullptr;

                Node* _focusHolder = nullptr;

                Region _renderingRegion;

                std::list<Node*>              _nodesWaitingLayout;
                std::list<VisualPrimitive*>   _vpsWaitingGeometryUpdate;
                std::list<Node*>              _nodesWaitingOffsetApplication;
                std::vector<Node*>            _nodesWaitingRendering;
        
                // macOS specific
                bool _enabled = true;

                VisualPrimitive* _getMouseEventTarget(MouseInputParams* inputParams);
                void _cleanUpForFollowingRenderingIteration();

                void _layout();
                void _calculateClippings();
                void _render();
                void _render(Region* region);
                void _updateGeometryAndApplyAbsoluteOffset();


    public:      Window();
                ~Window();

                void* getNativeHandle();

                void show();
                void showModal();
                void hide();
                void minimize();
                void maximize();
                bool isModal();
                WindowAppearanceState getWindowState();

                void focus();
                bool isFocused();

                void enable();
                void disable();
                bool isEnabled();

                void   setPosition(Vector posititon);
                Vector getPosition();

                void   setSize(Vector size);
                Vector getSize();

                void        nativeBorderShown_set(bool isShown);
                bool        nativeBorderShown_get();
                void        nativeTitle_set(std::string title);
                std::string nativeTitle_get();
                void        nativeIcon_set();
                void        nativeIcon_get();
                void        nativeMinimizeAllow_set(bool allow);
                bool        nativeMinimizeAllow_get();
                void        nativeMaximizeAllow_set(bool allow);
                bool        nativeMaximizeAllow_get();
                void        nativeCloseAllow_set   (bool allow);
                bool        nativeCloseAllow_get   ();

                void insertChild(Node* node);
                void insertChild(Node* node, unsigned int zCoordinate);
                void removeChild(Node* node);
                void removeAndDeleteChild(Node* node);
               
                cairo_t* getCairoContext() final;

                void notifyModelChange(Node* node, bool layoutParamChanged, bool geometryParamChanged, bool redneringParamChanged, Rect* additionaRenderingRect = nullptr) final;

                void registerAnimation(Animation* animation) final;
                Rect surfaceSize() final;

                void setFocus(Node* node);


                Event<Window*, SizeChangedEventArgs*>sizeChanged;
                Event<Window*, EventArgs*>           positionChanged;

                Event<Window*, KeyboardEventArgs*>   keyDown;
                Event<Window*, KeyboardEventArgs*>   keyUp;

                Event<Window*, MouseEventArgs*>      mouseDoubleClick;
                Event<Window*, MouseEventArgs*>      mouseDown;
                Event<Window*, MouseEventArgs*>      mouseUp;
                Event<Window*, MouseEventArgs*>      mouseMove;
                Event<Window*, MouseScrollEventArgs*>mouseScroll;

                Event<Window*, EventArgs*>           mouseEnter;
                Event<Window*, EventArgs*>           mouseLeave;


                void onSizeChanged (SizeChangedParams inputParams);
                void onPositionChanged();

                void onKeyDown (KeyboardInputParams inputParams);
                void onKeyUp   (KeyboardInputParams inputParams);

                void onMouseButtonDoubleClick (MouseInputParams inputParams);
                void onMouseButtonDown        (MouseInputParams inputParams);
                void onMouseButtonUp          (MouseInputParams inputParams);
                void onMouseMove              (MouseInputParams inputParams);
                void onMouseWheel             (MouseScrollInputParams inputParams);

                void onMouseEnter();
                void onMouseLeave();

                void onRenderingTimer();
                void onRedrawRequested(Rect);
    };
}
