#pragma once

#include "SkinableControl.h"
#include "CheckBoxSkin.h"

namespace Eleusis
{
    class ELEUSIS_API CheckBox :
        public SkinableControl<CheckBoxSkin>
    {
        bool _isChecked = false;
        std::string _text = "";

        virtual void _applySkin();

    public:
        CheckBox();
        virtual ~CheckBox() { };

        void setText(std::string text);
        std::string getText();

        void check();
        void uncheck();

        bool isChecked() { return _isChecked; };

        Event<CheckBox*, EventArgs*> checkChanged;
        Event<CheckBox*, EventArgs*> textChanged;
        
    };
}
