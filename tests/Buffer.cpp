#include <gtest/gtest.h>
#include "../Buffer.h"

TEST(Buffer, pushBack) {
	{
		Queue<int> queue(0);
		EXPECT_EQ(queue, Queue<int>({}));
		queue.pushBack(0);
		EXPECT_EQ(queue, Queue<int>({}));
	}
	{
		Queue<int> queue(1);
		queue.pushBack(0);
		EXPECT_EQ(queue, Queue({0}));
		queue.pushBack(1);
		EXPECT_EQ(queue, Queue({0}));
	}
	{
		Queue<int> queue(2);
		queue.pushBack(0);
		EXPECT_EQ(queue, Queue({0}));
		queue.pushBack(1);
		EXPECT_EQ(queue, Queue({0, 1}));
		queue.pushBack(2);
		EXPECT_EQ(queue, Queue({0, 1}));
		queue.popFront();
		EXPECT_EQ(queue, Queue({1}));
		queue.pushBack(2);
		EXPECT_EQ(queue, Queue({1, 2}));
		queue.popFront();
		queue.popFront();
		queue.pushBack(3);
		queue.pushBack(4);
		EXPECT_EQ(queue, Queue({3, 4}));
	}
}

TEST(Buffer, popFront) {
	{
		Queue<int> queue(0);
		queue.popFront();
		EXPECT_EQ(queue, Queue<int>({}));
	}
	{
		Queue<int> queue(1);
		queue.popFront();
		EXPECT_EQ(queue, Queue<int>({}));
		queue.pushBack(0);
		queue.popFront();
		EXPECT_EQ(queue, Queue<int>({}));
	}
	{
		Queue<int> queue(2);
		queue.pushBack(0);
		queue.pushBack(1);
		queue.popFront();
		EXPECT_EQ(queue, Queue<int>({1}));
		queue.popFront();
		EXPECT_EQ(queue, Queue<int>({}));
	}
}

TEST(Buffer, getter) {
	{
		Queue<int> queue(0);
		EXPECT_THROW(queue[0], std::out_of_range);
	}
	{
		Queue<int> queue(2);
		EXPECT_THROW(queue[0], std::out_of_range);
		queue.pushBack(0);
		queue.pushBack(1);
		EXPECT_EQ(queue[0], 0);
		EXPECT_EQ(queue[1], 1);
		EXPECT_THROW(queue[2], std::out_of_range);
	}
}