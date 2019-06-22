#ifdef __APPLE__

#include "Application.h"
#include "Window.h"

#include <chrono>

#import <Cocoa/Cocoa.h>

using namespace Eleusis;
using namespace std;
using namespace std::chrono;

Event<void*, EventArgs*>      Application::renderingCycleExecuted = Event<void*, EventArgs*>();
Event<void*, MouseEventArgs*> Application::mouseUp                = Event<void*, MouseEventArgs*>();

void Application::registerInstance()
{
}

@interface	ApplicationController : NSResponder <NSApplicationDelegate>
    - (void)setStartupWindow:(Window*)window;
    - (void)onRendering:(NSTimer *)timer;
@end

@implementation ApplicationController
{
    Window* _mainWindow;
    NSTimer* _renderingTimer;
}

- (void) setStartupWindow:(Window*)window
{
    _mainWindow = window;
}

- (void)onRendering:(NSTimer *)timer
{
    _mainWindow->onRenderingTimer();
    raiseEvent Application::renderingCycleExecuted(nullptr, nullptr);
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification
{
    _renderingTimer = [NSTimer timerWithTimeInterval: 30 / 1000 target: self selector:@selector(onRendering:) userInfo:nil repeats:true];
    _renderingTimer.tolerance = 5 / 1000;
    
    [[NSRunLoop currentRunLoop]addTimer:_renderingTimer forMode:NSDefaultRunLoopMode];
    _mainWindow->show();
    
    /*!
     Now you booted up, but you have nothing, even there's no main-menu, so you
     cannot quit using @c Command+Q.
     */
}
- (void)userTapQuitMenu:(id)sender
{
    [[NSApplication sharedApplication] terminate:self];
}
@end

int Application::run(Window* startupWindow)
{
    @autoreleasepool
    {
        ApplicationController* del1	= [[ApplicationController alloc] init];
        [del1 setStartupWindow:startupWindow];
        NSApplication*	app1 = [NSApplication sharedApplication];		///	Let it to be created by accessing it.
        [app1 setDelegate:del1];
        [app1 run];
        
        /*!
         Calling of @c NSApplicationMain is not required.
         */
        //return NSApplicationMain(argc, argv);
    }
    
    return 0;
}

long long Application::timestamp()
{
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

void Application::nativeMsgBox(string message, string title)
{
    NSString* l_message = [NSString stringWithUTF8String:message.c_str()];
    NSString* l_title   = [NSString stringWithUTF8String:title.c_str()];

    if (!l_message || !l_title) return;
    
    NSAlert* l_nsAlert = [[NSAlert alloc] init];
    [l_nsAlert setMessageText:l_message];
    [l_nsAlert setInformativeText:l_title];
    [l_nsAlert runModal];
}

void Application::Clipboard::putUnicodeText(string text)
{
}

string Application::Clipboard::getUnicodeText()
{
    string l_clipboardString;
    return l_clipboardString;
}

#endif