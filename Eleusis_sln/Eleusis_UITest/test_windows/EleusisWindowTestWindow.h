#pragma once

#include "Window.h"
#include "event.h"
#include "TextBlock.h"
#include "PseudoTextBox.h"


namespace Eleusis
{
    namespace Test
    {
        class EleusisWindowTestWindow
            : public Eleusis::Window
        {
        public:
            EleusisWindowTestWindow();
            ~EleusisWindowTestWindow();

            Eleusis::TextualShape* block;
            Eleusis::Rectangle* rect2;
            Eleusis::PseudoControls::PseudoTextBox* l_textBox;

            Window* win;
            Eleusis::PseudoControls::PseudoTextBox* txt1;
            Eleusis::PseudoControls::PseudoTextBox* txt2;
            Eleusis::PseudoControls::PseudoTextBox* txt3;
            Eleusis::PseudoControls::PseudoTextBox* txt4;

            int count = 0;

            bool underline = false;

            Eleusis::Rectangle* rect55;
            Eleusis::Circle* circ55;

        };
    }
}




