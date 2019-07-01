#ifdef __APPLE__

#include "EleusisNSWindow_macOS.h"
#include "Application.h"

#include "cairo.h"
#include "cairo-quartz.h"

#include "Timer.h"

using namespace Eleusis;

@implementation EleusisNSWindow
{
    Eleusis::Window* _eleusisWindowOwner;
}

- (id)initWithOwner:(Eleusis::Window*)owner
{
    self = [super init];
    
    _eleusisWindowOwner = owner;
        
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowResized:) name:NSWindowDidResizeNotification object:self];

    self.contentView.layer = [self.contentView makeBackingLayer];
    self.contentView.layer.contentsGravity = kCAGravityTopLeft;
    self.contentView.wantsLayer = YES;

    return self;
}

- (void)show:(CGContextRef)context
{
    CGImageRef l_image = CGBitmapContextCreateImage(context);
    self.contentView.layer.contents = (__bridge id)l_image;
    CGImageRelease(l_image);
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