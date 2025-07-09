#include "pch.h"
#include <queue>
#include <vector>
#include <gtest/gtest.h> // Include the Google Test framework header

TEST(priorityqueue, test_max) {
	std::priority_queue<int> pq;
	pq.push(10);
	pq.push(20);
	pq.push(15);
	EXPECT_EQ(pq.top(), 20);
	pq.pop();
	EXPECT_EQ(pq.top(), 15);
	pq.pop();
	EXPECT_EQ(pq.top(), 10);
}

TEST(priorityqueue, test_min) {
	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
	pq.push(10);
	pq.push(20);
	pq.push(15);
	EXPECT_EQ(pq.top(), 10);
	pq.pop();
	EXPECT_EQ(pq.top(), 15);
	pq.pop();
	EXPECT_EQ(pq.top(), 20);
}
