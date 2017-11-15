#pragma once

#include "Shape.h"

namespace Eleusis
{
	namespace SampleApp
	{
		class SectionViewBase :
			public Rectangle
		{
		public:
			SectionViewBase();
            Event<SectionViewBase*, EventArgs*> backRequested;
		};
	}
}