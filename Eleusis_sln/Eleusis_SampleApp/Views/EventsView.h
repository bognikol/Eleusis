#pragma once

#include "SectionViewBase.h"

namespace Eleusis
{
    namespace SampleApp
    {
        class EventsView :
            public SectionViewBase
        {
            static std::string _getStringParams(MouseEventArgs* e, std::string senderName, std::string eventName);
            static std::string _getStringParams(MouseScrollEventArgs* e, std::string senderName, std::string eventName);
            static std::string _getStringParams(KeyboardEventArgs* e, std::string senderName, std::string eventName);
			static std::string _getStringParamsFromFocusEvent(std::string senderName, std::string eventName);

			TextualShape* _eventData = nullptr;
			TextualShape* _focusEventData = nullptr;
			TextualShape* _focusHolderData = nullptr;

            void _registerNode(Node* node, std::string nodeName);

        public:
            EventsView(Length width = 0, Length height = 0);
        };
    }
}