#ifdef __APPLE__

#include "Timer.h"

#import <Cocoa/Cocoa.h>

using namespace Eleusis;
using namespace std;

@implementation EleusisNSTimer : NSObject
{
    Timer* _timer;
    NSTimer* _nsTimer;
}

- (id)initWithOwner:(Timer*)timer intervalInS:(double)interval repetition:(BOOL)repetition
{
    self = [super init];

    _timer = timer;

    _nsTimer = [NSTimer scheduledTimerWithTimeInterval:interval 
        target:self selector:@selector(timerFireMethod:) 
        userInfo:nil 
        repeats:repetition];

    return self;
}

- (void)invalidate
{
    [_nsTimer invalidate];
}

- (void)timerFireMethod:(NSTimer *)timer
{
    if (_timer->enabled_get())
        raiseEvent _timer->elapsed(_timer, nullptr);
}
@end

Timer::Timer(unsigned int duration, TimerRepetition repetition) :
    _duration(duration),
    _repetition(repetition)
{
}

Timer::~Timer()
{
    stop();
}

void Timer::start()
{
    BOOL l_repetition = NO;
    if (_repetition == TimerRepetition::Forever)
        l_repetition = YES;

    if (_timerID) stop();    
    _timerID = (void*)[[EleusisNSTimer alloc] 
        initWithOwner:this 
        intervalInS:(_duration / 1000.0)
        repetition:l_repetition];

    raiseEvent started(this, nullptr);
}

void Timer::stop()
{
    if (!_timerID) return;

    [(EleusisNSTimer*)_timerID invalidate];
    [(EleusisNSTimer*)_timerID release];
    _timerID = nullptr;
}

void Timer::duration_set(unsigned int duration)
{
    _duration = duration;
}

unsigned int Timer::duration_get()
{
    return _duration;
}

void Timer::repetition_set(TimerRepetition repetition)
{
    _repetition = repetition;
}

TimerRepetition Timer::repetition_get()
{
    return _repetition;
}

void Timer::enabled_set(bool enable)
{
    _enabled = enable;
}

bool Timer::enabled_get()
{
    return _enabled;
}

#endif