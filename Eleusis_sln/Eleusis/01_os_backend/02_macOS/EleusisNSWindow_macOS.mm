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
    if (!_eleusisWindowOwner->isEnabled()) return;

    MouseInputParams l_mouseInputParams;
    
    l_mouseInputParams.Button = MouseButton::Left;
    l_mouseInputParams.X = [event locationInWindow].x;
    l_mouseInputParams.Y = self.frame.size.height - [event locationInWindow].y;
    
    [EleusisNSWindow populateSpecialKeyState:&l_mouseInputParams event:event];
    
    _eleusisWindowOwner->onMouseButtonDown(l_mouseInputParams);
}

- (void)mouseUp:(NSEvent*)event
{
    if (!_eleusisWindowOwner->isEnabled()) return;

    MouseInputParams l_mouseInputParams;
    
    l_mouseInputParams.Button = MouseButton::Left;
    l_mouseInputParams.X = [event locationInWindow].x;
    l_mouseInputParams.Y = self.frame.size.height - [event locationInWindow].y;
    
    [EleusisNSWindow populateSpecialKeyState:&l_mouseInputParams event:event];
    
    _eleusisWindowOwner->onMouseButtonUp(l_mouseInputParams);
}

- (void)rightMouseDown:(NSEvent *)event
{
    if (!_eleusisWindowOwner->isEnabled()) return;

    MouseInputParams l_mouseInputParams;
    
    l_mouseInputParams.Button = MouseButton::Right;
    l_mouseInputParams.X = [event locationInWindow].x;
    l_mouseInputParams.Y = self.frame.size.height - [event locationInWindow].y;
    
    [EleusisNSWindow populateSpecialKeyState:&l_mouseInputParams event:event];
    
    _eleusisWindowOwner->onMouseButtonDown(l_mouseInputParams);
}

- (void)rightMouseUp:(NSEvent *)event
{
    if (!_eleusisWindowOwner->isEnabled()) return;

    MouseInputParams l_mouseInputParams;
    
    l_mouseInputParams.Button = MouseButton::Right;
    l_mouseInputParams.X = [event locationInWindow].x;
    l_mouseInputParams.Y = self.frame.size.height - [event locationInWindow].y;
    
    [EleusisNSWindow populateSpecialKeyState:&l_mouseInputParams event:event];
    
    _eleusisWindowOwner->onMouseButtonUp(l_mouseInputParams);
}

- (void)mouseMoved:(NSEvent*)event
{
    if (!_eleusisWindowOwner->isEnabled()) return;

    MouseInputParams l_mouseInputParams;
    
    l_mouseInputParams.Button = MouseButton::None;
    l_mouseInputParams.X = [event locationInWindow].x;
    l_mouseInputParams.Y = self.frame.size.height - [event locationInWindow].y;
    
    [EleusisNSWindow populateSpecialKeyState:&l_mouseInputParams event:event];

    _eleusisWindowOwner->onMouseMove(l_mouseInputParams);
}

- (void)mouseDragged:(NSEvent*)event
{
    if (!_eleusisWindowOwner->isEnabled()) return;

    MouseInputParams l_mouseInputParams;
    
    l_mouseInputParams.Button = MouseButton::None;
    l_mouseInputParams.X = [event locationInWindow].x;
    l_mouseInputParams.Y = self.frame.size.height - [event locationInWindow].y;
    
    [EleusisNSWindow populateSpecialKeyState:&l_mouseInputParams event:event];

    _eleusisWindowOwner->onMouseMove(l_mouseInputParams);
}

- (void)scrollWheel:(NSEvent *)event
{
    if (!_eleusisWindowOwner->isEnabled()) return;

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
    
    [EleusisNSWindow populateSpecialKeyState:&l_mouseWheelInputParams event:event];

    _eleusisWindowOwner->onMouseWheel(l_mouseWheelInputParams);
}

- (void)mouseEntered:(NSEvent *)theEvent
{
    if (!_eleusisWindowOwner->isEnabled()) return;
    _eleusisWindowOwner->onMouseEnter();
}

- (void)mouseExited:(NSEvent *)theEvent
{
    if (!_eleusisWindowOwner->isEnabled()) return;
    _eleusisWindowOwner->onMouseLeave();
}

- (void) viewResized:(NSView*)target
{
    if (!_eleusisWindowOwner->isEnabled()) return;

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

+ (void)populateSpecialKeyState:(Eleusis::SpecialKeysInputParams*)inputParams event:(NSEvent*)event
{
    NSEventModifierFlags flags = [event modifierFlags];
    if (flags & NSEventModifierFlagShift)    inputParams->ShiftDown    = true;
    if (flags & NSEventModifierFlagControl)  inputParams->ControlDown  = true;
    if (flags & NSEventModifierFlagOption)   inputParams->AltDown      = true;
    if (flags & NSEventModifierFlagCommand)  inputParams->CommandDown  = true;
    if (flags & NSEventModifierFlagFunction) inputParams->FunctionDown = true;
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
    if (!_eleusisWindowOwner->isEnabled()) return;
    
    KeyboardInputParams l_keyboardInputParams;
    
    l_keyboardInputParams.VirtualKeyCode = static_cast<VirtualKey>(event.keyCode);
    l_keyboardInputParams.String = std::string(event.characters.UTF8String);

    [EleusisNSWindow populateSpecialKeyState:&l_keyboardInputParams event:event];
    
    _eleusisWindowOwner->onKeyDown(l_keyboardInputParams);
}

- (void)keyUp:(NSEvent*)event 
{
    if (!_eleusisWindowOwner->isEnabled()) return;

    KeyboardInputParams l_keyboardInputParams;
    
    l_keyboardInputParams.VirtualKeyCode = static_cast<VirtualKey>(event.keyCode);
    l_keyboardInputParams.String = std::string(event.characters.UTF8String);
    
    [EleusisNSWindow populateSpecialKeyState:&l_keyboardInputParams event:event];
    
    _eleusisWindowOwner->onKeyUp(l_keyboardInputParams);
}
@end

#endif
