#pragma once

#include "dllexport.h"

#include <functional>
#include <list>

namespace Eleusis
{
    #define raiseEvent

    #define makeHandler(functionAddress) std::bind(functionAddress, this, std::placeholders::_1, std::placeholders::_2)



    class ELEUSIS_API HandlerBase
    {
    protected:
        static unsigned long long _getNextId();
    };



    template <typename SenderType, typename EventArgsType>
    class Handler :
        public HandlerBase
    {
    private:
        std::function<void(SenderType, EventArgsType)> _function = nullptr;
        unsigned long long _id = 0;

    public:
        Handler();
        Handler(std::function<void(SenderType, EventArgsType)> handlerFunction);

        void operator = (std::function<void(SenderType, EventArgsType)> handlerFunction);
        void operator () (SenderType, EventArgsType);

        bool operator == (Handler <SenderType, EventArgsType>) const;

        operator std::function<void(SenderType, EventArgsType)>();

        std::function<void(SenderType, EventArgsType)> target();
        unsigned long long getID();
    };

    template <typename SenderType, typename EventArgsType>
    Handler<SenderType, EventArgsType>::Handler()
    {
    };

    template <typename SenderType, typename EventArgsType>
    Handler<SenderType, EventArgsType>::Handler
    (std::function<void(SenderType, EventArgsType)> handlerFunction)
    {
        _function = handlerFunction;
        _id = _getNextId();
    };

    template <typename SenderType, typename EventArgsType>
    void Handler<SenderType, EventArgsType>::operator =
        (std::function<void(SenderType, EventArgsType)> handlerFunction)
    {
        if (_function) return;

        _function = handlerFunction;
        _id = _getNextId();
    }

    template <typename SenderType, typename EventArgsType>
    void Handler<SenderType, EventArgsType>::operator ()
        (SenderType sender, EventArgsType eventArgs)
    {
        _function(sender, eventArgs);
    }

    template <typename SenderType, typename EventArgsType>
    bool Handler<SenderType, EventArgsType>::operator ==
        (Handler<SenderType, EventArgsType> handler) const
    {
        return handler._id == _id;
    }

    template <typename SenderType, typename EventArgsType>
    Handler<SenderType, EventArgsType>::operator 
        std::function<void(SenderType, EventArgsType)>()
    {
        return _function;
    }

    template <typename SenderType, typename EventArgsType>
    std::function<void(SenderType, EventArgsType)>
        Handler<SenderType, EventArgsType>::target()
    {
        return _function;
    }

    template <typename SenderType, typename EventArgsType>
    unsigned long long Handler<SenderType, EventArgsType>::getID()
    {
        return _id;
    }



    template <typename SenderType, typename EventArgsType>
    class Event
    {
    public:
        void operator () (SenderType sender, EventArgsType args);
        void operator += (Handler<SenderType, EventArgsType> & handler);
        void operator += (std::function<void(SenderType, EventArgsType)> handler);
        void operator -= (Handler<SenderType, EventArgsType> & handler);

    private:
        std::list<Handler<SenderType, EventArgsType>> _handlers;

        void operator = (Event<SenderType, EventArgsType> & event) { };
    };


    template<typename SenderType, typename EventArgsType>
    void Event<SenderType, EventArgsType>::operator ()
        (SenderType sender, EventArgsType eventArgs)
    {
        if (_handlers.empty()) return;
        for (auto & handler : _handlers)
            handler(sender, eventArgs);
    }

    template<typename SenderType, typename EventArgsType>
    void Event<SenderType, EventArgsType>::operator +=
        (Handler<SenderType, EventArgsType> & handler)
    {
        _handlers.remove(handler);
        _handlers.push_back(handler);
    }

    template<typename SenderType, typename EventArgsType>
    void Event<SenderType, EventArgsType>::operator +=
        (std::function<void(SenderType, EventArgsType)> handler)
    {
        Handler<SenderType, EventArgsType> l_handler(handler);

        _handlers.push_back(l_handler);
    }


    template<typename SenderType, typename EventArgsType>
    void Event<SenderType, EventArgsType>::operator -=
        (Handler<SenderType, EventArgsType> & handler)
    {
        _handlers.remove(handler);
    }



    class ELEUSIS_API EventArgs
    {
    };
}
