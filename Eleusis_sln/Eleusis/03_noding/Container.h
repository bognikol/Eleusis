#pragma once

#include "Node.h"

namespace Eleusis
{
    class ELEUSIS_API Container :
        public Node
    {   

    public:     Container(Length width = 0, Length height = 0);
                Rect getFullExtent();

                void    width_set(Length width);
                Length  width_get() { return _width; };

                void    height_set(Length height);
                Length  height_get() { return _height; };

                void setWidthAndHeight(Length width, Length height);

                void clipping_set(bool clipping);
                bool clipping_get() { return _clipping; };
                
    private:    virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector);

                Length _width;
                Length _height;
    };
}