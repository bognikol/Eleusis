#include "Window.h"
#include "Application.h"

using namespace Eleusis;
using namespace std;


#pragma region EVENT DISPATCHING

VisualPrimitive* Window::_getMouseEventTarget(MouseInputParams* inputParams)
{
    Node* l_targetNode = _root->lastDescendant();
    VisualPrimitive* l_visualPrimitive;

    while (true)
    {
        if (!l_targetNode) return nullptr;
        if (l_targetNode->isVisualPrimitive())
        {
            l_visualPrimitive = static_cast<VisualPrimitive*>(l_targetNode);
            if (l_visualPrimitive->getExtent().contains(inputParams->X, inputParams->Y))
                if (l_visualPrimitive->contains(inputParams->X, inputParams->Y))
                    return l_visualPrimitive;
        }
        l_targetNode = l_targetNode->previous();
    }
}

/*void Window::onSizeChanged(SizeChangedParams inputParams)
{
    _root->setAbsoluteSizeVector(inputParams.Size);

    SizeChangedEventArgs l_sizeChangedEventArgs(inputParams);
    raiseEvent sizeChanged(this, &l_sizeChangedEventArgs);
}*/

void Window::onRedrawRequested(Rect rectToBeRedrawn)
{
    notifyModelChange(nullptr, false, false, true, &rectToBeRedrawn);
}

void Window::onPositionChanged()
{
    // TODO: To be implemented
}

void Window::onKeyDown(KeyboardInputParams inputParams)
{
    KeyboardEventArgs l_keyboardEventArgs(inputParams);
    raiseEvent keyDown(this, &l_keyboardEventArgs);

    Node* l_targetNode = _focusHolder;
    l_keyboardEventArgs.PrimarySender = _focusHolder;

    while (true)
    {
        if (!l_targetNode) break;
        if (l_targetNode->isFocusable())
            raiseEvent l_targetNode->keyDown(l_targetNode, &l_keyboardEventArgs);
        l_targetNode = l_targetNode->parent();
    }
}

void Window::onKeyUp(KeyboardInputParams inputParams)
{
    KeyboardEventArgs l_keyboardEventArgs(inputParams);
    raiseEvent keyUp(this, &l_keyboardEventArgs);

    Node* l_targetNode = _focusHolder;
    l_keyboardEventArgs.PrimarySender = _focusHolder;

    while (true)
    {
        if (!l_targetNode) break;
        if (l_targetNode->isFocusable())
            raiseEvent l_targetNode->keyUp(l_targetNode, &l_keyboardEventArgs);
        l_targetNode = l_targetNode->parent();
    }
}

void Window::onMouseButtonDoubleClick(MouseInputParams inputParams)
{
    MouseEventArgs l_mouseEventArgs(inputParams);

    Node* l_targetNode = _getMouseEventTarget(&inputParams);
    l_mouseEventArgs.PrimarySender = l_targetNode;

    raiseEvent mouseDown(this, &l_mouseEventArgs);
    raiseEvent mouseDoubleClick(this, &l_mouseEventArgs);

    while (true)
    {
        if (!l_targetNode) break;

        raiseEvent l_targetNode->mouseDown(l_targetNode, &l_mouseEventArgs);
        raiseEvent l_targetNode->mouseDoubleClick(l_targetNode, &l_mouseEventArgs);
        l_targetNode = l_targetNode->parent();
    }
}

void Window::onMouseButtonDown(MouseInputParams inputParams)
{
    MouseEventArgs l_mouseEventArgs(inputParams);

    _lastMouseDownVisualPrimitive = _getMouseEventTarget(&inputParams);

    Node* l_targetNode = _lastMouseDownVisualPrimitive;
    l_mouseEventArgs.PrimarySender = l_targetNode;

    raiseEvent mouseDown(this, &l_mouseEventArgs);

    while (true)
    {
        if (!l_targetNode) break;
        raiseEvent l_targetNode->mouseDown(l_targetNode, &l_mouseEventArgs);
        l_targetNode = l_targetNode->parent();
    }

    setFocus(_lastMouseDownVisualPrimitive);
}

void Window::onMouseButtonUp(MouseInputParams inputParams)
{
    MouseEventArgs l_mouseEventArgs(inputParams);

    VisualPrimitive* l_currentMouseUpVisualPrimitive = _getMouseEventTarget(&inputParams);
    Node* l_targetNode = l_currentMouseUpVisualPrimitive;
    l_mouseEventArgs.PrimarySender = l_targetNode;

    raiseEvent mouseUp(this, &l_mouseEventArgs);

    while (true)
    {
        if (!l_targetNode) break;

        raiseEvent l_targetNode->mouseUp(l_targetNode, &l_mouseEventArgs);
        l_targetNode = l_targetNode->parent();
    }

    if (_lastMouseDownVisualPrimitive != l_currentMouseUpVisualPrimitive) return;
    if (!_lastMouseDownVisualPrimitive) return;

    l_targetNode = _lastMouseDownVisualPrimitive;

    while (true)
    {
        if (!l_targetNode) break;
        raiseEvent l_targetNode->mouseClick(l_targetNode, &l_mouseEventArgs);
        l_targetNode = l_targetNode->parent();
    }
}

void Window::onMouseMove(MouseInputParams inputParams)
{
    MouseEventArgs l_mouseEventArgs(inputParams);

    VisualPrimitive* l_currentVisualPrimitiveMouseMove = _getMouseEventTarget(&inputParams);
    Node* l_targetNode = l_currentVisualPrimitiveMouseMove;
    l_mouseEventArgs.PrimarySender = l_targetNode;

    raiseEvent mouseMove(this, &l_mouseEventArgs);

    if (_lastMouseMoveVisualPrimitive != l_currentVisualPrimitiveMouseMove)
    {
        Node* l_youngestCommonAncestor = Node::youngestCommonAncestor(l_currentVisualPrimitiveMouseMove, _lastMouseMoveVisualPrimitive);

        if (l_youngestCommonAncestor)
        {
            Node* l_node = _lastMouseMoveVisualPrimitive;
            while (true)
            {
                if (!l_node || l_node == l_youngestCommonAncestor) break;
                raiseEvent l_node->mouseLeave(l_node, &l_mouseEventArgs);
                l_node = l_node->parent();
            }

            l_node = l_currentVisualPrimitiveMouseMove;
            while (true)
            {
                if (!l_node || l_node == l_youngestCommonAncestor) break;
                raiseEvent l_node->mouseEnter(l_node, &l_mouseEventArgs);
                l_node = l_node->parent();
            }
        }

        _lastMouseMoveVisualPrimitive = l_currentVisualPrimitiveMouseMove;
    }

    while (true)
    {
        if (!l_targetNode) break;

        raiseEvent l_targetNode->mouseMove(l_targetNode, &l_mouseEventArgs);
        l_targetNode = l_targetNode->parent();
    }
}

void Window::onMouseWheel(MouseScrollInputParams inputParams)
{
    MouseScrollEventArgs l_mouseWheelEventArgs(inputParams);
    raiseEvent mouseScroll(this, &l_mouseWheelEventArgs);

    Node* l_targetNode = _getMouseEventTarget(&inputParams);

    while (true)
    {
        if (!l_targetNode) break;
        raiseEvent l_targetNode->mouseScroll(l_targetNode, &l_mouseWheelEventArgs);
        l_targetNode = l_targetNode->parent();
    }
}

void Window::onMouseEnter()
{
    raiseEvent mouseEnter(this, nullptr);
}

void Window::onMouseLeave()
{
    raiseEvent mouseLeave(this, nullptr);
}

#pragma endregion




void Window::_layout()
{
    _root->_layout();
}

void Window::_calculateClippings()
{
    _root->_calculateChildrenClippings();
}

void Window::insertChild(Node* node)
{
    _root->insertChild(node);
}

void Window::insertChild(Node* node, unsigned int zCoordinate)
{
    _root->insertChild(node, zCoordinate);
}

void Window::removeChild(Node* node)
{
    _root->removeChild(node);
}

void Window::removeAndDeleteChild(Node* node)
{
    _root->removeAndDeleteChild(node);
}

void Window::_updateGeometryAndApplyAbsoluteOffset()
{
    Node* l_nextChild = _root->firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        if (l_nextChild->isVisualPrimitive())
            static_cast<VisualPrimitive*>(l_nextChild)->_updateGeometry();
        l_nextChild = l_nextChild->next();
    }

    l_nextChild = _root->firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        static_cast<VisualPrimitive*>(l_nextChild)->_applyAbsoluteOffset();
        l_nextChild = l_nextChild->next();
    }
}

cairo_t* Window::getCairoContext()
{
    return _cairoContext;
}

void Window::notifyModelChange(Node* node, bool layoutParamChanged, bool geometryParamChanged, bool renderingParamChanged, Rect* additionaRenderingRect)
{
    if (additionaRenderingRect) 
        _renderingRegion += *additionaRenderingRect;

    if (!node) return;

    if (!node->isVisualPrimitive())
    {
        if (layoutParamChanged)
        {
            _nodesWaitingLayout.push_back(node);
            _nodesWaitingOffsetApplication.push_back(node);
        }
    }
    else
    {
        if (layoutParamChanged)
        {
            if (geometryParamChanged)
            {
                _nodesWaitingLayout.push_back(node);
                _nodesWaitingOffsetApplication.push_back(node);
                _vpsWaitingGeometryUpdate.push_back(static_cast<VisualPrimitive*>(node));
            }
            else
            {
                _nodesWaitingLayout.push_back(node);
                _nodesWaitingOffsetApplication.push_back(node);
                // if _absoluteSizeVector is changed during layout, then this node will be pushed to _vpsWaitingGeometryUpdate
            }
        }
        else
        {
            if (geometryParamChanged)
            {
                _vpsWaitingGeometryUpdate.push_back(static_cast<VisualPrimitive*>(node));
                _nodesWaitingOffsetApplication.push_back(node);
            }
            else
            {
                if (renderingParamChanged)
                {
                    _nodesWaitingRendering.push_back(node);
                }
            }
        }
    }
}

void Window::registerAnimation(Animation* animation)
{
    _animationManager->registerAnimation(animation);
}

void Window::onRenderingTimer()
{
    _animationManager->updateAll(Application::timestamp());

    if (!_nodesWaitingLayout.empty())
    {
		// TODO:
		// find oldest ancestor and call layout on it

        _nodesWaitingLayout.sort();
        _nodesWaitingLayout.unique();

        for (auto l_node : _nodesWaitingLayout)
        {
            l_node->_layout();
            l_node->_calculateChildrenClippings();
        }
    }

    if (!_vpsWaitingGeometryUpdate.empty())
    {  
		_vpsWaitingGeometryUpdate.sort();
		_vpsWaitingGeometryUpdate.unique();

        for (auto l_vp : _vpsWaitingGeometryUpdate)
        {
			_renderingRegion += l_vp->getExtent();
			l_vp->_updateGeometry();
        }
    }

    if (!_nodesWaitingOffsetApplication.empty())
    {
        for (auto l_node : _nodesWaitingLayout)
            _renderingRegion += l_node->getFullExtent();

        for (auto l_node : _nodesWaitingOffsetApplication)
            l_node->_applyAbsoluteOffset();

        _nodesWaitingOffsetApplication.sort();
        _nodesWaitingOffsetApplication.unique();

        for (auto l_node : _nodesWaitingOffsetApplication)
            _renderingRegion += l_node->getFullExtent();
    }

    if (!_nodesWaitingRendering.empty() || !_renderingRegion.getRects().empty())
    {
        for (auto l_node : _nodesWaitingRendering)
            if (l_node->isVisualPrimitive())
                _renderingRegion += static_cast<VisualPrimitive*>(l_node)->getExtent();

		_renderingRegion.normalize();
        _render(&_renderingRegion);
    }

    // PREPEARE STATE FOR NEXT ITERATION
    _cleanUpForFollowingRenderingIteration();
}

void Window::_cleanUpForFollowingRenderingIteration()
{
    for (auto node : _nodesWaitingLayout)
    {
        Node* l_node = node;

        while (true)
        {
            if (!l_node) break;
            l_node->_layoutingExecuted = false;
            l_node = l_node->next();
        }
    }

    for (auto vp : _vpsWaitingGeometryUpdate)
    {
        vp->_geometryUpdateExecuted = false;
    }

    for (auto node : _nodesWaitingOffsetApplication)
    {
        Node* l_node = node;

        while (true)
        {
            if (!l_node) break;
            l_node->_absoluteOffsetApplicationExecuted = false;
            l_node = l_node->next();
        }
    }

    _nodesWaitingLayout.clear();
    _vpsWaitingGeometryUpdate.clear();
    _nodesWaitingOffsetApplication.clear();
    _nodesWaitingRendering.clear();
    _renderingRegion = Region();
}

void Window::setFocus(Node* node)
{
    if (node == _focusHolder) return;

    if (node && !node->isFocusable())
        node = nullptr;

    Node* l_youngestCommonAncestor = Node::youngestCommonAncestor(node, _focusHolder);

    Node* l_targetNode = _focusHolder;
    while (true)
    {
        if (!l_targetNode || l_targetNode == l_youngestCommonAncestor) break;
        if (l_targetNode->isFocusable())
        {
            raiseEvent l_targetNode->lostFocus(l_targetNode, nullptr);
        }
        l_targetNode = l_targetNode->parent();
    }

    _focusHolder = node;

    l_targetNode = _focusHolder;
    while (true)
    {
        if (!l_targetNode || l_targetNode == l_youngestCommonAncestor) break;
        if (l_targetNode->isFocusable())
            raiseEvent l_targetNode->gotFocus(l_targetNode, nullptr);
        l_targetNode = l_targetNode->parent();
    }
}
