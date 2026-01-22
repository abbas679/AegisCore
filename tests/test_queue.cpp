#include "gtest/gtest.h"
#include "queue/EventQueue.h"
#include "core/EventBase.h"
#include "core/EventId.h"

using namespace aegis;

TEST(EventQueueTests, PushPopWorks) {
    EventQueue q(10);

    struct TestEvent : EventBase {
        int payload = 0;
        explicit TestEvent(int p) : payload(p) { type_id = EventType<TestEvent>::id; }
    };

    auto e1 = new TestEvent(100);
    auto e2 = new TestEvent(200);

    EXPECT_TRUE(q.push(e1));
    EXPECT_TRUE(q.push(e2));

    EventBase* r1 = q.pop();
    EXPECT_EQ(static_cast<TestEvent*>(r1)->payload, 100);
    delete r1;

    EventBase* r2 = q.pop();
    EXPECT_EQ(static_cast<TestEvent*>(r2)->payload, 200);
    delete r2;

    EXPECT_TRUE(q.empty());
}
