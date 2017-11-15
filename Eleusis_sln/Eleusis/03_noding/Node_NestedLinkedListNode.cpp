#include <limits>

#include "Node.h"
#include "Window.h"

using namespace Eleusis;
using namespace std;

Node::Node() :
    _zCoordinate     (0),
    _firstChild       (nullptr),
    _lastChild       (nullptr),
    _parent          (nullptr),
    _nextSibling     (nullptr),
    _previousSibling (nullptr),
    _isVisualPrimitive (false)
{
    gotFocus  += makeHandler(&Node::_gotFocus_thisHandler);
    lostFocus += makeHandler(&Node::_lostFocus_thisHandler);
}

Node::~Node()
{
    if (_firstChild)
    {
        Node* l_nextSiblingForDestruction = _firstChild;
        Node* l_siblingToBeDestructed = l_nextSiblingForDestruction;

        while (true)
        {
            l_nextSiblingForDestruction = l_siblingToBeDestructed->_nextSibling;

            delete l_siblingToBeDestructed;

            l_siblingToBeDestructed = l_nextSiblingForDestruction;
            if (!l_siblingToBeDestructed) break;
        }
    }
}

void Node::_obtainContext()
{
    if   (_parent) _uiContext = _parent->_uiContext;
    else           _uiContext =  nullptr;

    Node* l_nextChild = _firstChild;
    Node* l_lastDescendant = lastDescendant();

    while(true)
    {
        if (!l_nextChild) break;

        if   (_parent) l_nextChild->_uiContext = _parent->_uiContext;
        else           l_nextChild->_uiContext =  nullptr;

        if (l_nextChild == l_lastDescendant) break;

        l_nextChild = l_nextChild->next();
    }
}

void Node::zCoordinate_set(unsigned int zCoordinate)
{
    if (_parent)
        _parent->insertChild(this, zCoordinate);
    else
        _zCoordinate = zCoordinate;
}

unsigned int Node::zCoordinate_get()
{
    return _zCoordinate;
}

void Node::insertAfter(Node* node)
{
    if (node == this) return;
    if(node->_parent || node->_previousSibling || node->_nextSibling) node->remove();

    if (_nextSibling)
    {
        if (_zCoordinate == _nextSibling->_zCoordinate || _zCoordinate == _nextSibling->_zCoordinate + 1)
            node->_zCoordinate = _zCoordinate;
        else
            if (_zCoordinate != UINT_MAX) node->_zCoordinate = _zCoordinate + 1;
            else                          node->_zCoordinate = UINT_MAX;

            _nextSibling->_previousSibling = node;
    }
    else
    {
        if (_zCoordinate != UINT_MAX) node->_zCoordinate = _zCoordinate + 1;
        else                          node->_zCoordinate = UINT_MAX;

        if (_parent)
            _parent->_lastChild = node;
    }


    node->_nextSibling = _nextSibling;
    node->_previousSibling = this;

    _nextSibling = node;
    node->_parent = _parent;

    node->_obtainContext();

    _requestParentLayout();
}

void Node::insertBefore(Node* node)
{
    if (node == this) return;
    if (node->_parent || node->_previousSibling || node->_nextSibling) node->remove();

    if (_previousSibling)
    {
        if (_zCoordinate == _previousSibling->_zCoordinate || _zCoordinate == _previousSibling->_zCoordinate - 1)
            node->_zCoordinate = _zCoordinate;
        else
            if (_zCoordinate != 0) node->_zCoordinate = _zCoordinate - 1;
            else                   node->_zCoordinate = 0;

            _previousSibling->_nextSibling = node;
    }
    else
    {
        if (_zCoordinate != 0) node->_zCoordinate = _zCoordinate - 1;
        else                   node->_zCoordinate = 0;

        if (_parent) 
            _parent->_firstChild = node;
    }

    node->_previousSibling = _previousSibling;
    node->_nextSibling = this;

    _previousSibling = node;
    node->_parent = _parent;

    node->_obtainContext();

    _requestParentLayout();
}

void Node::insertChild(Node* node)
{
    if (node == this) return;
    if (node->_parent || node->_previousSibling || node->_nextSibling) node->remove();

    if (!_lastChild)
    {
        _firstChild = node;
        _lastChild  = node;
        node->_parent = this;
        node->_nextSibling = nullptr;
        node->_previousSibling = nullptr;
    }
    else
    {      
        _lastChild->_nextSibling = node;
        node->_previousSibling = _lastChild;
        node->_nextSibling = nullptr;

        if      (node->_zCoordinate <  _lastChild->_zCoordinate) 
                 node->_zCoordinate =  _lastChild->_zCoordinate;
        else if (node->_zCoordinate == _lastChild->_zCoordinate)
                if (node->_zCoordinate != UINT_MAX) 
                    node->_zCoordinate += 1;

        _lastChild = node;
        node->_parent = this;
    }

    node->_obtainContext();

    _requestLayout();
}

void Node::insertChild(Node* node, unsigned int zCoordinate)
{
    if (node == this) return;
    if (node->_parent || node->_previousSibling || node->_nextSibling) node->remove();
    node->_zCoordinate = zCoordinate;

    if (!_firstChild)
    {
        _firstChild = node;
        _lastChild  = node;
        node->_parent = this;
        node->_nextSibling = nullptr;
        node->_previousSibling = nullptr;
    }
    else if (node->_zCoordinate < _firstChild->_zCoordinate)
    {
        node->_previousSibling = nullptr;
        node->_nextSibling = _firstChild;
        node->_parent = this;
        _firstChild->_previousSibling = node;
        _firstChild = node;
    }
    else
    {
        Node* l_previousSibling = _firstChild;
        Node* l_nextSibling =     _firstChild->_nextSibling;

        while (true)
        {
            if (!l_nextSibling) break;
            if (l_previousSibling->_zCoordinate <= node->_zCoordinate && 
                node->_zCoordinate < l_nextSibling->_zCoordinate) 
                break;

            l_previousSibling = l_nextSibling;
            l_nextSibling = l_previousSibling->_nextSibling;
        }

        l_previousSibling->_nextSibling = node;
        node->_previousSibling = l_previousSibling;
        node->_nextSibling = l_nextSibling;
        if (l_nextSibling) 
            l_nextSibling->_previousSibling = node;
        else
            _lastChild = node;
        node->_parent = this;
    }

    node->_obtainContext();

    _requestLayout();
}

void Node::remove()
{
    if (uiContext())
    {
        Rect l_fullExtent = getFullExtent();
        if (_parent)
            uiContext()->notifyModelChange(_parent, true, false, false, &l_fullExtent);
    }

    if (!_previousSibling)
        if (_parent)
            _parent->_firstChild = _nextSibling;

    if (!_nextSibling)
        if (_parent)
            _parent->_lastChild = _previousSibling;

    if (_previousSibling)
        _previousSibling->_nextSibling = _nextSibling;
    if (_nextSibling)
        _nextSibling->_previousSibling = _previousSibling;

    _parent             = nullptr;
    _nextSibling        = nullptr;
    _previousSibling    = nullptr;

    _obtainContext();
}

void Node::removeChild(Node* node)
{
    if (node->_parent != this) return;

    node->remove();
}

void Node::removeAndDeleteChild(Node* node)
{
    if (node->_parent != this) return;

    node->remove();

    delete node;
}

Node* Node::next()
{
    if (_firstChild)  return _firstChild;
    if (_nextSibling) return _nextSibling;

    Node* l_nextParent = _parent;

    while (true)
    {
        if (!l_nextParent)              return nullptr;
        if (l_nextParent->_nextSibling) return l_nextParent->_nextSibling;
        l_nextParent = l_nextParent->_parent;
    }

    return nullptr;
}

Node* Node::previous()
{
    if (_previousSibling)
        if   (_previousSibling->lastDescendant()) return _previousSibling->lastDescendant();
        else                                      return _previousSibling;
    else
        return _parent;
}

Node* Node::nextSibling()
{
    return _nextSibling;
}

Node* Node::previousSibling()
{
    return _previousSibling;
}

Node* Node::firstChild()
{
    return _firstChild;
}

Node* Node::lastChild()
{
    return _lastChild;
}

Node* Node::firstDescendant() 
{
    return _firstChild;
}

Node* Node::lastDescendant() 
{
    Node* l_lastChild = _lastChild;
    if (!l_lastChild) return nullptr;

    Node* l_nextLastChild = nullptr;

    while (true)
    {
        l_nextLastChild = l_lastChild->_lastChild;

        if (!l_nextLastChild) break;
        l_lastChild = l_nextLastChild;
    }

    return l_lastChild;
}

Node* Node::parent()
{
    return _parent;
}

bool Node::isDescendantOf(Node* node)
{
    bool l_isDescendant = false;

    Node* l_nodeCandidate = this;

    while (true)
    {
        l_nodeCandidate = l_nodeCandidate->_parent;
        if (!l_nodeCandidate) break;
        if (l_nodeCandidate == node)
        {
            l_isDescendant = true;
            break;
        } 
    }

    return l_isDescendant;
}

bool Node::isAncestorOf(Node* node)
{
    return node->isDescendantOf(this);
}

void Node::_applyAbsoluteOffset()
{
    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_applyAbsoluteOffset();
        l_nextChild = l_nextChild->nextSibling();
    }
}

void Node::_requestRendering()
{
    if (uiContext())
        uiContext()->notifyModelChange(this, false, false, true, nullptr);
}

void Node::_requestRendering(Rect rect)
{
    if (uiContext())
        uiContext()->notifyModelChange(this, false, false, true, &rect);
}

void Node::_requestLayout()
{
    if (uiContext())
        uiContext()->notifyModelChange(this, true, false, false, nullptr);
}

void Node::_requestParentLayout()
{
    if (_parent && _parent->uiContext())
        _parent->uiContext()->notifyModelChange(_parent, true, false, false, nullptr);
}

void Node::_requestGeometryUpdate()
{
    if (uiContext())
        uiContext()->notifyModelChange(this, false, true, false, nullptr);
}

void Node::focus()
{
    if (uiContext())
        uiContext()->setFocus(this);
}

void Node::visibility_set(bool visibility)
{
    if (visibility == _visibility) return;

    _visibility = visibility;
    _requestRendering(getFullExtent());
}

bool Node::visibility_get()
{
    return _visibility;
}

void Node::_gotFocus_thisHandler(Node* sender, EventArgs* e)
{
    _inFocus = true;
}

void Node::_lostFocus_thisHandler(Node* sender, EventArgs* e)
{
    _inFocus = false;
}

Node* Node::youngestCommonAncestor(Node* node1, Node* node2)
{
    Node* l_node = nullptr;

    vector<Node*> l_node1Ancestors;

    l_node = node1;

    while (true)
    {
        if (!l_node) break;
        l_node1Ancestors.push_back(l_node);
        l_node = l_node->parent();
    }

    vector<Node*> l_node2Ancestors;

    l_node = node2;

    while (true)
    {
        if (!l_node) break;
        l_node2Ancestors.push_back(l_node);
        l_node = l_node->parent();
    }

    l_node = nullptr;
    int i1 = l_node1Ancestors.size(); i1--;
    int i2 = l_node2Ancestors.size(); i2--;

    while (true)
    {
        if (i1 < 0 || i2 < 0) break;
        if (l_node1Ancestors[i1] == l_node2Ancestors[i2])
        {
            l_node = l_node1Ancestors[i1];
        }
        i1--;
        i2--;
    }

    return l_node;
}