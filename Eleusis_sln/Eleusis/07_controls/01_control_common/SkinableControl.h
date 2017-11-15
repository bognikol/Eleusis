#pragma once

#include "dllexport.h"

#include "Control.h"

namespace Eleusis
{
    template <typename SkinType>
    class ELEUSIS_API SkinableControl :
        public Control
    {
    private:
        SkinType* _skin = nullptr;

    protected:
        virtual void _applySkin() = 0;

    public:
        virtual ~SkinableControl() { delete _skin; };

        void setSkin(SkinType* skin) { if (_skin) return; _skin = skin; _applySkin(); };
        SkinType* getSkin() { return _skin; };
    };
}