#include <gtest/gtest.h>
#include <core/Event.h>

using aegis::core::Event;

TEST(EventTests, ConstructionWorks)
{
    Event e{1, "TestEvent"};

    EXPECT_EQ(e.id, 1);
    EXPECT_EQ(e.name, "TestEvent");
}
