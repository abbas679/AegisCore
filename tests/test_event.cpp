#include "gtest/gtest.h"
#include "core/EventId.h"

using namespace aegis;

TEST(EventIdTests, UniqueIds) {
    struct A {};
    struct B {};

    EventId a_id = EventType<A>::id;
    EventId b_id = EventType<B>::id;

    EXPECT_NE(a_id, b_id);
    EXPECT_EQ(a_id, EventType<A>::id);
}
