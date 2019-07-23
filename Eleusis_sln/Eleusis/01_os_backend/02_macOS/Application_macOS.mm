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

- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)application
{
    return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification
{
    _mainWindow->show();
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
        NSApplication*	app1 = [NSApplication sharedApplication];
        [app1 setDelegate:del1];
        [app1 run];
    }
    
    return 0;
}

long long Application::timestamp()
{
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

System Application::currentSystem()
{
    return System::MacOS;
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

 void Application::nativeLog(string message)
 {
     NSLog(@"%@", [NSString stringWithCString:message.c_str() encoding:[NSString defaultCStringEncoding]]);
 }


void Application::Clipboard::putUnicodeText(string text)
{
    NSString* l_stringForClipboard = [NSString stringWithCString:text.c_str()
                                                        encoding:NSUTF8StringEncoding];
    NSPasteboard* l_pasteboard = [NSPasteboard generalPasteboard];
    [l_pasteboard clearContents];
    [l_pasteboard setString:l_stringForClipboard forType:NSPasteboardTypeString];
}

string Application::Clipboard::getUnicodeText()
{
    NSString* l_stringFromClipboard = [[NSPasteboard generalPasteboard] stringForType:NSPasteboardTypeString];
    return string([l_stringFromClipboard UTF8String]);
}

#endif
