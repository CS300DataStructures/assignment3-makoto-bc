#include <gtest/gtest.h>
#include "../Buffer.h"

using namespace network;

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
		EXPECT_EQ(queue, Queue<int>({0}));
		queue.pushBack(1);
		EXPECT_EQ(queue, Queue<int>({0}));
	}
	{
		Queue<int> queue(2);
		queue.pushBack(0);
		EXPECT_EQ(queue, Queue<int>({0}));
		queue.pushBack(1);
		EXPECT_EQ(queue, Queue<int>({0, 1}));
		queue.pushBack(2);
		EXPECT_EQ(queue, Queue<int>({0, 1}));
		queue.popFront();
		EXPECT_EQ(queue, Queue<int>({1}));
		queue.pushBack(2);
		EXPECT_EQ(queue, Queue<int>({1, 2}));
		queue.popFront();
		queue.popFront();
		queue.pushBack(3);
		queue.pushBack(4);
		EXPECT_EQ(queue, Queue<int>({3, 4}));
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

TEST(Buffer, remove) {
	struct Test {
		Queue<int> queue;
		size_t removeIndex;
		Queue<int> expected;
	};

	std::vector<Test> tests {
		{
			{0},
			0,
			{},
		},
		{
			{0, 1},
			0,
			{1},
		},
		{
			{0, 1},
			1,
			{0},
		},
		{
			{0, 1, 2},
			0,
			{1, 2},
		},
		{
			{0, 1, 2},
			1,
			{0, 2},
		},
		{
			{0, 1, 2},
			2,
			{0, 1},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		tests[i].queue.remove(tests[i].removeIndex);
		EXPECT_EQ(tests[i].queue, tests[i].expected) << i;
	}

	EXPECT_THROW(Queue<int>({}).remove(0), std::out_of_range);
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

TEST(Buffer, processPackets) {
	struct Test {
		std::vector<Packet> packets;
		size_t bufferSize;
		std::vector<Response> expected;
	};

	std::vector<Test> tests {
		{ // 0
			{},
			0,
			{},
		},
		{ // 1
			{},
			1,
			{},
		},
		{ // 2
			{
				{0, 0, 0},
			},
			0,
			{
				Response::newDropped(),
			},
		},
		{ // 3
			{
				{0, 1, 0},
			},
			0,
			{
				Response::newDropped(),
			},
		},
		{ // 4
			{
				{0, 0, 0},
			},
			1,
			{
				Response::newCompletedResponse(0),
			},
		},
		{ // 5
			{
				{0, 1, 1},
			},
			1,
			{
				Response::newCompletedResponse(1),
			},
		},
		{ // 6
			{
				{0, 0, 0},
				{1, 1, 0},
			},
			0,
			{
				Response::newDropped(),
				Response::newDropped(),
			},
		},
		{ // 7
			{
				{0, 0, 0},
				{1, 1, 0},
			},
			1,
			{
				Response::newCompletedResponse(0),
				Response::newCompletedResponse(1),
			},
		},
		{ // 8
			{
				{0, 0, 1},
				{1, 1, 1},
			},
			1,
			{
				Response::newCompletedResponse(0),
				Response::newCompletedResponse(1),
			},
		},
		{ // 9
			{
				{0, 0, 2},
				{1, 1, 0},
			},
			1,
			{
				Response::newCompletedResponse(0),
				Response::newDropped(),
			},
		},
		{ // 10
			{
				{0, 0, 2},
				{1, 1, 0},
			},
			2,
			{
				Response::newCompletedResponse(0),
				Response::newCompletedResponse(2),
			},
		},
		{ // 11
			{
				{0, 0, 2},
				{1, 1, 0},
				{1, 2, 1},
			},
			1,
			{
				Response::newCompletedResponse(0),
				Response::newDropped(),
				Response::newCompletedResponse(2),
			},
		},
		{ // 12
			{
				{0, 0, 2},
				{1, 1, 0},
				{1, 1, 1},
			},
			1,
			{
				Response::newCompletedResponse(0),
				Response::newDropped(),
				Response::newDropped(),
			},
		},
		{ // 13
			{
				{0, 0, 2},
				{1, 1, 0},
				{1, 1, 1},
			},
			2,
			{
				Response::newCompletedResponse(0),
				Response::newCompletedResponse(2),
				Response::newDropped(),
			},
		},
		{ // 14
			{
				{0, 0, 4},
				{1, 1, 1},
				{1, 2, 2},
			},
			3,
			{
				Response::newCompletedResponse(0),
				Response::newCompletedResponse(4),
				Response::newCompletedResponse(5),
			},
		},
		{ // 15
			{
				{0, 0, 1},
				{1, 1, 2},
				{1, 1, 1},
			},
			2,
			{
				Response::newCompletedResponse(0),
				Response::newCompletedResponse(1),
				Response::newCompletedResponse(3),
			},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		Buffer buffer(tests[i].bufferSize);
		EXPECT_EQ(processPackets(tests[i].packets, &buffer), tests[i].expected) << i;
	}
}