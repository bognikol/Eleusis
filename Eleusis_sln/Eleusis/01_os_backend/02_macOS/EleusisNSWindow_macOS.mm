#ifdef __APPLE__

#include "EleusisNSWindow_macOS.h"
#include "Application.h"

using namespace Eleusis;

@interface BaseNSView : NSView 
{
    - (id)initWithOwner:(EleusisNSWindow*)ownerWindow;
}

@implementation BaseNSView
{
    - (id)initWithOwner:(EleusisNSWindow*)ownerWindow 
    {
        self = [super init];

        return self;
    }

    - (void)drawRect:(NSRect)rect
    {
        CGContextRef myContext = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
        // ********** Your drawing code here ********** // 2
        //CGContextSetRGBFillColor (myContext, 1, 0, 0, 1);// 3
        //CGContextFillRect (myContext, CGRectMake (0, 0, 200, 100 ));// 4
        //CGContextSetRGBFillColor (myContext, 0, 0, 1, .5);// 5
        //CGContextFillRect (myContext, CGRectMake (0, 0, 100, 200));// 6
        
        
        //CGContextTranslateCTM (myContext, 0.0, (unsigned int)[self frame].size.height - 20);
        //CGContextScaleCTM (myContext, 1.0, -1.0);
        
        cairo_surface_t* surface = cairo_quartz_surface_create_for_cg_context (myContext, 3000, 3000);
        cairo_t* cr = cairo_create(surface);
        
        cairo_set_source_rgb (cr, 0, 0, 0);
        cairo_rectangle (cr, -5000, -5000, 10000, 10000);
        cairo_fill (cr);
        
    }
}

@implementation EleusisNSWindow
{
    Eleusis::Window* _eleusisWindowOwner;
}

- (id)initWithOwner:(Eleusis::Window*)owner
{
    self = [super init];
    
    _eleusisWindowOwner = owner;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowResized:) name:NSWindowDidResizeNotification object:self];

    return self;
}

- (void)keyDown:(NSEvent*)event
{
    KeyboardEventArgs l_keyboardInputParams;
    
    l_keyboardInputParams.VirtualKeyCode = static_cast<VirtualKey>(event.keyCode);
    l_keyboardInputParams.String = std::string(event.characters.UTF8String);

    _eleusisWindowOwner->onKeyDown(l_keyboardInputParams);
}

- (void)keyUp:(NSEvent*)event
{
    KeyboardEventArgs l_keyboardInputParams;
    
    l_keyboardInputParams.VirtualKeyCode = static_cast<VirtualKey>(event.keyCode);
    l_keyboardInputParams.String = std::string(event.characters.UTF8String);
    
    _eleusisWindowOwner->onKeyUp(l_keyboardInputParams);
}

- (void)mouseDown:(NSEvent*)event
{
    Application::nativeMsgBox("Hello world 222");

    MouseEventArgs l_mouseEventArgs;
    
    l_mouseEventArgs.Button = MouseButton::Left;
    l_mouseEventArgs.X = [event locationInWindow].x;
    l_mouseEventArgs.Y = self.frame.size.height - [event locationInWindow].y;
    
    _eleusisWindowOwner->onMouseButtonDown(l_mouseEventArgs);
}

- (void)mouseUp:(NSEvent*)event
{
    MouseEventArgs l_mouseEventArgs;
    
    l_mouseEventArgs.Button = MouseButton::Left;
    l_mouseEventArgs.X = [event locationInWindow].x;
    l_mouseEventArgs.Y = self.frame.size.height - [event locationInWindow].y;
    
    _eleusisWindowOwner->onMouseButtonUp(l_mouseEventArgs);
}

- (void)mouseMoved:(NSEvent*)event
{
    MouseEventArgs l_mouseEventArgs;
    
    l_mouseEventArgs.Button = MouseButton::None;
    l_mouseEventArgs.X = [event locationInWindow].x;
    l_mouseEventArgs.Y = self.frame.size.height - [event locationInWindow].y;
    
    _eleusisWindowOwner->onMouseMove(l_mouseEventArgs);
}

- (void) windowResized:(NSWindow*)target
{
    SizeChangedParams l_sizeChangedParams;
    
    l_sizeChangedParams.Size = {self.frame.size.width, self.frame.size.height };
    
    _eleusisWindowOwner->onSizeChanged(l_sizeChangedParams);
}



@end

#endif