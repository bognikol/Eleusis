#ifdef __APPLE__

#pragma once

#import <Cocoa/Cocoa.h>

#include "Window.h"

@interface EleusisNSWindow : NSWindow
    - (id)initWithOwner:(Eleusis::Window*)owner;
    - (void) windowResized:(NSWindow*)target;
@end


#endif