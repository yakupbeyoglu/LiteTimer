#include <gtest/gtest.h>
#include <timer.h>
#include <types.h>
#include <priority_queue.hpp>

// Test ComparatorDesc for TimerEvent
TEST(ComparatorDescTest, BasicAssertions) {
    yb::TimerEvent timer1(true, std::chrono::milliseconds(1000), [](){});
    yb::TimerEvent timer2(true, std::chrono::milliseconds(2000), [](){});

    yb::TimerEvent::ComparatorDesc comparator;
    ASSERT_TRUE(comparator(timer2, timer1)); // Expecting timer2 to be "less than" timer1
}

// Test ComparatorDesc for TimerEvent
TEST(ComparatorAscTest, BasicAssertions) {
    yb::TimerEvent timer1(true, std::chrono::milliseconds(1000), [](){});
    yb::TimerEvent timer2(true, std::chrono::milliseconds(2000), [](){});

    yb::TimerEvent::ComparatorAsc comparator;
    ASSERT_TRUE(comparator(timer1, timer2)); // Expecting timer1 to be
}

// Test Call Order
TEST(CallOrderTest, BasicAssertions) {
    yb::PriorityQueue<yb::TimerEvent, yb::TimerEvent::ComparatorAsc> queue;

    int x = -1;
    yb::TimerEvent data(false, 3_s,std::bind([&](int i) {
        x = i;
    }, 10));

    yb::TimerEvent data2(false, 1_s,std::bind([&](int i) {
        x = i;
    }, 20));


    yb::TimerEvent data3(false, 1_s,std::bind([&](int i) {
        x = i;
    }, 30));


    yb::TimerEvent data4(false, 0_s,std::bind([&](int i) {
        x = i;
    }, 0));


    queue.emplace(std::move(data));
    queue.emplace(std::move(data2));
    queue.emplace(std::move(data3));
    queue.emplace(std::move(data4));

    queue[0].invokeCallBack();
    EXPECT_EQ(x, 0);
    queue[1].invokeCallBack();
    EXPECT_EQ(x, 20);
    queue[2].invokeCallBack();
    EXPECT_EQ(x, 30);
    queue[3].invokeCallBack();
    EXPECT_EQ(x, 10);
}
