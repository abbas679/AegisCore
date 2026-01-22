#include "gtest/gtest.h"
#include "core/EventBase.h"
#include "core/EventId.h"

using namespace aegis;

TEST(EventBaseTests, ConstructionWorks) {
    struct MyEvent : EventBase {
        int payload = 0;
        explicit MyEvent(int p) : payload(p) { type_id = EventType<MyEvent>::id; }
    };

    MyEvent e(42);

    EXPECT_EQ(e.type_id, EventType<MyEvent>::id);
    EXPECT_EQ(e.payload, 42);
}
