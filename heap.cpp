#include "pch.h"

using namespace std;

TEST(heap, Test1) {
	std::vector<int> v{ 3, 2, 4, 1, 5, 9 };

	std::make_heap(v.begin(), v.end());
	EXPECT_EQ(v[0], 9); // The largest element should be at the root of the heap
	EXPECT_TRUE(std::is_heap(v.begin(), v.end()));
}
