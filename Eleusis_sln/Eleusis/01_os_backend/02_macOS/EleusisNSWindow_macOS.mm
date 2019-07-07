#ifdef __APPLE__

#include "EleusisNSWindow_macOS.h"
#include "Application.h"

#import <QuartzCore/QuartzCore.h>

using namespace Eleusis;

@implementation EleusisNSView : NSView 
{
    Window* _eleusisWindowOwner;
    NSTrackingArea* _trackingArea;
}

- (id)initWithOwner:(Window*)owner
{
    self = [super init];
    
    _eleusisWindowOwner = owner;
        
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(viewResized:) name:NSViewFrameDidChangeNotification object:self];
    
    [self updateTrackingAreas];

    self.layer = [self makeBackingLayer];
    self.layer.contentsGravity = kCAGravityTopLeft;
    self.wantsLayer = YES;

    return self;
}

- (void)updateTrackingAreas
{
    [super updateTrackingAreas];

    if (_trackingArea) {
        [self removeTrackingArea:_trackingArea];
        [_trackingArea release];
    }

    _trackingArea = [[NSTrackingArea alloc] initWithRect:self.bounds
        options: (NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveInKeyWindow)
        owner:self userInfo:nil];
    [self addTrackingArea:_trackingArea];
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
    
    raiseEvent Application::mouseUp(nullptr, &l_mouseEventArgs);
    _eleusisWindowOwner->onMouseButtonUp(l_mouseEventArgs);
}

- (void)rightMouseDown:(NSEvent *)event
{
    MouseEventArgs l_mouseEventArgs;
    
    l_mouseEventArgs.Button = MouseButton::Right;
    l_mouseEventArgs.X = [event locationInWindow].x;
    l_mouseEventArgs.Y = self.frame.size.height - [event locationInWindow].y;
    
    _eleusisWindowOwner->onMouseButtonDown(l_mouseEventArgs);
}

- (void)rightMouseUp:(NSEvent *)event
{
    MouseEventArgs l_mouseEventArgs;
    
    l_mouseEventArgs.Button = MouseButton::Right;
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

- (void)mouseDragged:(NSEvent*)event
{
    MouseEventArgs l_mouseEventArgs;
    
    l_mouseEventArgs.Button = MouseButton::None;
    l_mouseEventArgs.X = [event locationInWindow].x;
    l_mouseEventArgs.Y = self.frame.size.height - [event locationInWindow].y;
    
    _eleusisWindowOwner->onMouseMove(l_mouseEventArgs);
}

- (void)scrollWheel:(NSEvent *)event
{
    MouseScrollInputParams l_mouseWheelInputParams;

    if (fabs(event.scrollingDeltaY) > fabs(event.scrollingDeltaX))
    {
        l_mouseWheelInputParams.WheelType = MouseScrollType::Vertical;
        l_mouseWheelInputParams.WheelMove = event.scrollingDeltaY;
    }
    else 
    {
        l_mouseWheelInputParams.WheelType = MouseScrollType::Horizontal;
        l_mouseWheelInputParams.WheelMove = event.scrollingDeltaX;
    }

    l_mouseWheelInputParams.Button = MouseButton::None;
    l_mouseWheelInputParams.X = [event locationInWindow].x;
    l_mouseWheelInputParams.Y = self.frame.size.height - [event locationInWindow].y;
    _eleusisWindowOwner->onMouseWheel(l_mouseWheelInputParams);
}

- (void)mouseEntered:(NSEvent *)theEvent{
    _eleusisWindowOwner->onMouseEnter();
}

- (void)mouseExited:(NSEvent *)theEvent{
    _eleusisWindowOwner->onMouseLeave();
}

- (void) viewResized:(NSView*)target
{
    SizeChangedParams l_sizeChangedParams;
    
    l_sizeChangedParams.Size = { self.frame.size.width, self.frame.size.height };
    
    _eleusisWindowOwner->onSizeChanged(l_sizeChangedParams);
}

- (void)show:(CGContextRef)context
{
    [CATransaction begin];
    [CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];
    CGImageRef l_image = CGBitmapContextCreateImage(context);
    self.layer.contents = (__bridge id)l_image;
    CGImageRelease(l_image);
    [CATransaction commit];
}
@end

@implementation EleusisNSWindow
{
    Window* _eleusisWindowOwner;
}

- (id)initWithOwner:(Eleusis::Window*)owner
{
    self = [super init];
    self.contentView = [[EleusisNSView alloc] initWithOwner: owner];
    _eleusisWindowOwner = owner;
    return self;
}

- (void)show:(CGContextRef)context
{
    [self.contentView show:context];
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
@end

#endif