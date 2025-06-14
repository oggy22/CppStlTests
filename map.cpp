#include "pch.h"

using namespace std;

TEST(Map, Test1) {
	std::map<int, int> mapping;
	int x = mapping[0];
	EXPECT_EQ(x, 0);

	mapping[10] += 1;
	EXPECT_EQ(mapping[10], 1);

	auto it = mapping.find(10);
}

TEST(Map, Order) {
	std::map<int, string> mapping;
	mapping[0] = "zero";
	mapping[1] = "one";
	mapping[10] = "ten";
	mapping[5] = "five";
	mapping[-1] = "minus five";

	int lastKey = INT_MIN;
	for (const auto& [key, value] : mapping)
	{
		EXPECT_LE(lastKey, key);
	}
}
