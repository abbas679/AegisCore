#include "gtest/gtest.h"
#include "engine/EventDispatcher.h"
#include "queue/EventQueue.h"
#include "core/EventBase.h"
#include "core/EventId.h"

using namespace aegis;

TEST(EventDispatcherTests, DispatchWorks) {
    EventQueue q(10);
    EventDispatcher dispatcher;

    struct TestEvent : EventBase {
        int value = 0;
        explicit TestEvent(int v) : value(v) { type_id = EventType<TestEvent>::id; }
    };

    int received = 0;

    dispatcher.registerHandler<TestEvent>([&](TestEvent* e) {
        received = e->value;
    });

    q.push(new TestEvent(42));

    dispatcher.dispatchQueue(q);

    EXPECT_EQ(received, 42);
    EXPECT_TRUE(q.empty());
}
