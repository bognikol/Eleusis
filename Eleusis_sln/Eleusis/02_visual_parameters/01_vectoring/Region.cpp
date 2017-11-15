#include "Region.h"

using namespace Eleusis;


void Region::operator += (Rect rect)
{
    _rects.push_front(rect);
	_extentIsStale = true;
}

std::list<Rect> & Region::getRects()
{
    return _rects;
}

void Region::clearRects()
{
    _rects.clear();
	_extentIsStale = true;
}

bool Region::contains(Vector v)
{
    for (auto rect : getRects())
        if (rect.contains(v)) return true;
    
    return false;
}

void Region::clip(Rect rect)
{
    auto l_rectIter = _rects.begin();

    while (true)
    {
        if (l_rectIter == _rects.end()) break;

        *l_rectIter &= rect;

        if (!l_rectIter->wellFormed())
            l_rectIter = _rects.erase(l_rectIter);
        else
            l_rectIter++;
    }

	_extentIsStale = true;
}

void Region::normalize()
{
    auto l_rectIter1 = _rects.begin();
    if (l_rectIter1 == _rects.end()) return;

    auto l_rectIter2 = l_rectIter1;
    l_rectIter2++;
    if (l_rectIter2 == _rects.end()) return;

    while (true)
    {
        if (*l_rectIter1 % *l_rectIter2)
        {
            *l_rectIter1 |= *l_rectIter2;
            _rects.erase(l_rectIter2);
            if (_rects.size() == 1) break;
            l_rectIter2 = _rects.begin();
        }
        else
        {
            l_rectIter2++;
            if (l_rectIter2 == _rects.end())
            {
                l_rectIter1++;
                if (l_rectIter1 == _rects.end()) break;
                l_rectIter2 = l_rectIter1;
                l_rectIter2++;
                if (l_rectIter2 == _rects.end()) break;
            }
        }
    }

	l_rectIter1 = _rects.begin();

	while (true)
	{
		if (l_rectIter1 == _rects.end()) break;
		l_rectIter1->integral();
		l_rectIter1++;
	}
}

Rect Region::getExtent()
{
	if (_extentIsStale)
	{
		_extent = Rect();

		for (auto & rect : _rects)
		{
			if (_extent.isZero())
				_extent = rect;
			else
				_extent |= rect;
		}
	}

    return _extent;
}