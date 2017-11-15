#pragma once

#include "dllexport.h"

#include "Shape.h"
#include "TextBlock.h"
#include "Window.h"

namespace Eleusis
{
    namespace PseudoControls
    {
        class ELEUSIS_API PseudoTextBox :
            public Eleusis::Rectangle
        {
        public:     PseudoTextBox();

                    void setText(std::string text);
                    std::string getText();

                    void setWidth(double width);

                    Event<PseudoTextBox*, EventArgs*> textChanged;

        private:    TextBlock* _textBlock;
                    bool _editMode = false;
                    Window* _parentWindow;
                    Handler<Window*, KeyboardEventArgs*> _keyDownEventHandler;

        };
    }
}