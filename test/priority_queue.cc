#include <gtest/gtest.h>
#include <priority_queue.hpp>


template <typename T, typename Comp>
bool isPriorityQueueSorted(yb::PriorityQueue<T, Comp> &queue) {
  for (std::size_t i = 1; i < queue.size(); ++i) {
    if (queue.comparator(queue[i], queue[i - 1])) {
      return false; // Not prioritized
    }
  }
  return true; // Prioritized
}

TEST(DefaultConstructor, BasicAssertions) {
  yb::PriorityQueue<int> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(CopyConstructor, BasicAssertions) {
  yb::PriorityQueue<int> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::PriorityQueue<int> copiedQueue(queue);
  EXPECT_EQ(copiedQueue.size(), queue.size());
  EXPECT_EQ(copiedQueue.top(), queue.top());
  EXPECT_EQ(copiedQueue.empty(), queue.empty());
  EXPECT_TRUE(isPriorityQueueSorted(copiedQueue));
}

// Test copy assignment operator
TEST(CopyAssignmentOperator, BasicAssertions) {
  yb::PriorityQueue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::PriorityQueue<int> copiedQueue;
  copiedQueue = queue;
  EXPECT_EQ(copiedQueue.size(), queue.size());
  EXPECT_EQ(copiedQueue.top(), queue.top());
  EXPECT_EQ(copiedQueue.empty(), queue.empty());
  EXPECT_TRUE(isPriorityQueueSorted(copiedQueue));
}

// Test move constructor
TEST(MoveConstructor, BasicAssertions) {
  yb::PriorityQueue<int, std::greater<int>> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::PriorityQueue<int, std::greater<int>> movedQueue(std::move(queue));
  EXPECT_EQ(movedQueue.size(), 3);
  EXPECT_TRUE(queue.empty());
  EXPECT_TRUE(isPriorityQueueSorted(movedQueue));
}

// Test move assignment operator
TEST(MoveAssignmentOperator, BasicAssertions) {
  yb::PriorityQueue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::PriorityQueue<int> movedQueue;
  movedQueue = std::move(queue);
  EXPECT_EQ(movedQueue.size(), 3);
  EXPECT_TRUE(queue.empty());
  EXPECT_TRUE(isPriorityQueueSorted(movedQueue));
}

// Test emplace function
TEST(PriorityQueueTest, Emplace) {
  yb::PriorityQueue<int, std::greater<int>> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  EXPECT_EQ(queue.size(), 3);
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

// Test emplace with initializer list
TEST(PriorityQueueTest, EmplaceInitializerList) {
  yb::PriorityQueue<int> queue;
  queue.emplace({10, 5, 20});

  EXPECT_EQ(queue.size(), 3);
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

// Test pop_back function
TEST(PriorityQueueTest, PopBack) {
  yb::PriorityQueue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);
  queue.pop_back();

  EXPECT_EQ(queue.size(), 2);
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

// Test erase function
TEST(PriorityQueueTest, Erase) {
  yb::PriorityQueue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  queue.erase(1); // Erase element at index 1

  EXPECT_EQ(queue.size(), 2);
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

// Test top function
TEST(PriorityQueueTest, Top) {
  yb::PriorityQueue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  EXPECT_EQ(queue.top(), 5);
}

// Test size function
TEST(PriorityQueueTest, Size) {
  yb::PriorityQueue<int> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  EXPECT_EQ(queue.size(), 3);
}

// Test empty function
TEST(PriorityQueueTest, Empty) {
  yb::PriorityQueue<int> queue;
  EXPECT_TRUE(queue.empty());

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  EXPECT_FALSE(queue.empty());
}

// Test swap function
TEST(PriorityQueueTest, Swap) {
  yb::PriorityQueue<int> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::PriorityQueue<int> otherQueue;
  otherQueue.emplace(30);
  otherQueue.emplace(15);

  swap(queue, otherQueue);

  EXPECT_EQ(queue.size(), 2);
  EXPECT_EQ(otherQueue.size(), 3);
  EXPECT_TRUE(isPriorityQueueSorted(otherQueue));
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

// max size test
TEST(PriorityQueueTest, MaxSize) {
  yb::PriorityQueue<int, std::less<int>, 3> queue;
  bool is_pushed = true;
  is_pushed &= queue.emplace(10);
  is_pushed &= queue.emplace(5);
  is_pushed &= queue.emplace(20);
  EXPECT_EQ(is_pushed, true);

  queue.emplace(10);
  is_pushed &= queue.emplace(30);
  EXPECT_EQ(is_pushed, false);

  EXPECT_EQ(queue.size(), 3);
  EXPECT_EQ(queue[2], 20);
}
