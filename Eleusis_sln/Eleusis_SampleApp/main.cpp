#include "Application.h"
#include "SampleWindow.h"

using namespace Eleusis;

#ifdef _WIN32
#include "Windows.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
#elif
int main(int argc, const char * argv[])
#endif
{
    Application::registerInstance();

    return
        Application::run(new SampleApp::SampleWindow());
}