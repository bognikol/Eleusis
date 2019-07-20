#include "Windows.h"

#include "Application.h"

#include "test_windows/SampleWindow.h"
#include "test_windows/AnimationTestWindow.h"
#include "test_windows/EleusisWindowTestWindow.h"
#include "test_windows/MouseEventTestWindow.h"
#include "test_windows/TransformationTestWindow.h"
#include "test_windows/MouseEventBubblingTestWindow.h"
#include "test_windows/MouseEventTextBlockTestWindow.h"
#include "test_windows/TextBlockTestWindow.h"
#include "test_windows/test_layout/ClassicLayoutTestWindow.h"
#include "test_windows/test_layout/StackLayoutTestWindow.h"
#include "test_windows/test_layout/WrapLayoutTestWindow.h"
#include "test_windows/test_layout/ContainerTestWindow.h"
#include "test_windows/test_layout/FitChildrenTestWindow.h"
#include "test_windows/SelectEditTestWindow.h"
#include "test_windows/FocusableTestWindow.h"
#include "test_windows/test_controls/CheckBoxTestWindow.h"
#include "test_windows/test_controls/SliderTestWindow.h"


using namespace Eleusis;

#ifdef _WIN32
#include "Windows.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
#else
int main(int argc, const char * argv[])
#endif
{
    Application::registerInstance();

    return
        Application::run(new Test::WrapLayoutTestWindow());

}
