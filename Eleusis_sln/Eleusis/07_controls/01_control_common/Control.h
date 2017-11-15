#pragma once

#include "dllexport.h"

#include "Node.h"

namespace Eleusis
{
    class ELEUSIS_API Control :
        public Node
    {
    private:
        virtual void _render();
        virtual void _render(Region* region);
    
    public:
        Control() { enableFocus(); }

        virtual ~Control() { };
        virtual Rect getFullExtent();
    };
}  