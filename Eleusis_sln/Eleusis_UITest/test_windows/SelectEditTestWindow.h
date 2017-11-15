#pragma once

#include "Window.h"
#include "SelectEdit.h"

namespace Eleusis
{
    namespace Test
    {
        class SelectEditTestWindow :
            public Eleusis::Window
        {
            TextBlock* _diagnosticsText = nullptr;
            TextBlock* _selectionText2 = nullptr;
            SelectEdit* _se = nullptr;
            SelectEdit* _se2 = nullptr;
            TextBlock* _seleText = nullptr;

            Handler<Node*, MouseEventArgs*> _populateDiagnostics;

            Rectangle* rectSelector = nullptr;

        public:
            SelectEditTestWindow();

        };
    }
}
