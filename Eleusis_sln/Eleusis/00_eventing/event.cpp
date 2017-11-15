#include "event.h"
#include <mutex>

using namespace Eleusis;
using namespace std;

unsigned long long HandlerBase::_getNextId()
{
    static unsigned long long _idCounter = 0;
    static mutex _idCounterMutex;

    lock_guard<mutex> l_lock(_idCounterMutex);

    _idCounter++;
    if (_idCounter == 0) _idCounter++;
    return _idCounter;
}