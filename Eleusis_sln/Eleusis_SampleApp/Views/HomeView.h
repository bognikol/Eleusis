#pragma once

#include "Shape.h"
#include "TextBlock.h"
#include "Container.h"
#include <string>

namespace Eleusis
{
	namespace SampleApp
	{
		class HomeView :
			public Rectangle
		{
			class NavigateButton :
				public Rectangle
			{
				TextBlock* _textBlock = nullptr;

			public:
				NavigateButton();

				void text_set(std::string text);
				std::string text_get();
			};

		public:
			class OptionSelectedEventArgs :
				public EventArgs
			{
			public:
				std::string option;
			};

			Event<HomeView*, OptionSelectedEventArgs*> optionSelected;

		private:
			Container* _navigationContainer = nullptr;
			void _addOption(std::string optionName, std::string buttonText = "");

		public:
			HomeView();
		};
	}
}