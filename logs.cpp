#include "pch.h"
#include <queue>
#include <vector>
#include <gtest/gtest.h> // Include the Google Test framework header

struct Log {
	int id;
	int time;
	bool start;
};

Log findTimedOutLog(const std::vector<Log>& logs, int timeOut) {
	auto by_time = [](const Log& a, const Log& b) {
		return a.time > b.time;
		};

	std::priority_queue<Log, std::vector<Log>, decltype(by_time)> heap(by_time);
	std::unordered_set<int> removed;

	for (const Log log : logs) {
		if (log.start) {
			heap.push(log);
			if (!heap.empty() && heap.top().time < log.time - timeOut)
				return heap.top();
		}
		else {
			removed.insert(log.id);

			while (!heap.empty() && removed.contains(heap.top().id)) {
				removed.erase(heap.top().id);
				heap.pop();
			}

			if (!heap.empty() && heap.top().time < log.time - timeOut)
				return heap.top();
		}
	}
	return { -1,-1,true };
}

void test(const std::vector<Log>& logs, int timeOut, int expectedId) {
	Log log = findTimedOutLog(logs, timeOut);
	EXPECT_EQ(log.id, expectedId);
}
TEST(logsTests, test) {
	test({
		{1,0, true},
		{1,1, false}
		},
		3,
		-1);

	test({
		{1,0, true},
		{1,1, false},
		{2,2, true},
		{3,3, true},
		{3,6, true},
		},
		3,
		2);
}

// ID 1, 0, Start
// ID 2, 1, Start
// ID 1, 2, End
// ID 3, 6, Start
// ID 2, 7, End
// ID 3, 8, End
