#include "Windows.h"

#include "Application.h"
#include "SampleWindow.h"

using namespace Eleusis;

int APIENTRY wWinMain
(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nCmdShow
)
{
    Application::registerInstance();

    return
        Application::run(new SampleApp::SampleWindow());
}