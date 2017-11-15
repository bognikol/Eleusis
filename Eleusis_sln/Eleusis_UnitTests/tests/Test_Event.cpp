#include "gtest/gtest.h"

#include "event.h"

#include <iostream>

using namespace std;
using namespace Eleusis;
using namespace ::testing;

class EventSender
{
public:
    Event<EventSender*, EventArgs*> eventHappened;
    Event<EventSender*, EventArgs*> eventHappened1;
    Event<EventSender*, EventArgs*> eventHappened2;

    void raise()
    {
        raiseEvent eventHappened(this, nullptr);
        raiseEvent eventHappened1(this, nullptr);
        raiseEvent eventHappened2(this, nullptr);
    }
};

class EventTest : public Test
{
protected:
    EventSender eventSender;
    int numRaised = 0;
};

TEST_F(EventTest, InlineLambdaAsAHandler)
{
    eventSender.eventHappened += 
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    eventSender.raise();

    EXPECT_EQ(numRaised, 1);
}

TEST_F(EventTest, InlineLambdaAsAHandlerAssignedTwice)
{
    string l_firstVariable = "";
    string l_secondVariable = "";

    eventSender.eventHappened +=
        [&, this](EventSender* sender, EventArgs* e)
    {
        l_firstVariable = "first";
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    eventSender.eventHappened +=
        [&, this](EventSender* sender, EventArgs* e)
    {
        l_secondVariable = "second";
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    eventSender.raise();

    EXPECT_EQ(l_firstVariable, "first");
    EXPECT_EQ(l_secondVariable, "second");
    EXPECT_EQ(numRaised, 2);
}

TEST_F(EventTest, PredefinedLambdaAsAHandler)
{
    auto l_handler = 
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    eventSender.eventHappened += l_handler;

    eventSender.raise();

    EXPECT_EQ(numRaised, 1);
}

TEST_F(EventTest, PredefinedLambdaAsAHandlerAssignedTwice)
{
    auto l_handler =
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    eventSender.eventHappened += l_handler;
    eventSender.eventHappened += l_handler;

    eventSender.raise();

    EXPECT_EQ(numRaised, 2);
}

TEST_F(EventTest, HandlerObjectAsAHandler)
{
    Handler<EventSender*, EventArgs*> l_handler = 
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    eventSender.eventHappened += l_handler;

    eventSender.raise();

    EXPECT_EQ(numRaised, 1);
}

TEST_F(EventTest, HandlerObjectAsAHandlerAssignedTwice)
{
    Handler<EventSender*, EventArgs*> l_handler =
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    eventSender.eventHappened += l_handler;
    eventSender.eventHappened += l_handler;

    eventSender.raise();

    EXPECT_EQ(numRaised, 1);
}

TEST_F(EventTest, HandlerObjectAsAHandlerAssignedAndThenDeassigned)
{
    Handler<EventSender*, EventArgs*> l_handler =
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    EXPECT_NE(l_handler.getID(), 0);

    eventSender.eventHappened += l_handler;

    EXPECT_NE(l_handler.getID(), 0);

    eventSender.eventHappened -= l_handler;

    EXPECT_NE(l_handler.getID(), 0);

    eventSender.raise();

    EXPECT_EQ(numRaised, 0);
}

TEST_F(EventTest, HandlerObjectContainsValidFunctionObject)
{
    Handler<EventSender*, EventArgs*> l_handler =
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    l_handler(&eventSender, nullptr);

    EXPECT_EQ(numRaised, 1);
}

TEST_F(EventTest, HandlerObjectReturnsValidTarget)
{
    Handler<EventSender*, EventArgs*> l_handler =
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    l_handler.target()(&eventSender, nullptr);

    EXPECT_EQ(numRaised, 1);
}

TEST_F(EventTest, HandlerObjectsCreatedFromSameFunctionObjectsHaveSameTargetsButDifferentIDs)
{
    function<void(EventSender* sender, EventArgs* e)> l_function =
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    Handler<EventSender*, EventArgs*> l_handler1 = l_function;
    Handler<EventSender*, EventArgs*> l_handler2 = l_function;

    eventSender.eventHappened += l_handler1;
    eventSender.eventHappened += l_handler2;

    EXPECT_NE(l_handler1.getID(), l_handler2.getID());

    eventSender.raise();

    EXPECT_EQ(numRaised, 2);
}

TEST_F(EventTest, HandlerObjectsCanBeAssignedAndDeassignedToMultipleEvents)
{
    Handler<EventSender*, EventArgs*> l_handler1 =
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    Handler<EventSender*, EventArgs*> l_handler2 =
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };

    Handler<EventSender*, EventArgs*> l_handler3 =
        [this](EventSender* sender, EventArgs* e)
    {
        EXPECT_EQ(&eventSender, sender);
        EXPECT_EQ(nullptr, e);
        numRaised++;
    };


    eventSender.eventHappened  += l_handler1;
    eventSender.eventHappened1 += l_handler1;
    eventSender.eventHappened2 += l_handler1;

    eventSender.eventHappened  += l_handler2;
    eventSender.eventHappened1 += l_handler2;
    eventSender.eventHappened2 += l_handler2;

    eventSender.eventHappened2 += l_handler3;

    EXPECT_NE(l_handler1.getID(), l_handler2.getID());
    EXPECT_NE(l_handler2.getID(), l_handler3.getID());
    EXPECT_NE(l_handler3.getID(), l_handler1.getID());

    eventSender.raise();

    EXPECT_EQ(numRaised, 7);

    eventSender.eventHappened  -= l_handler1;
    eventSender.eventHappened2 -= l_handler1;
    eventSender.eventHappened2 -= l_handler3;

    eventSender.raise();

    EXPECT_EQ(numRaised, 11);
}

