#include "pch.h"

using namespace std;

TEST(List, Test1) {
	std::list<int> s{ 2, 4, 6 };

	// Traverse
	for (int val : s) {
		std::cout << val << " ";
	}

	auto it = s.begin();

	// Assertions
	ASSERT_EQ(s.size(), 3);                // Check the list has 3 elements
	EXPECT_EQ(*it, 2);                     // First element is 2
	++it;
	EXPECT_EQ(*it, 4);                     // Second element is 4
	++it;
	EXPECT_EQ(*it, 6);                     // Third element is 6
	++it;
	EXPECT_EQ(it, s.end());                // Iterator reaches end after last element
	--it;
	EXPECT_EQ(*it, 6);                     // Third element is 6
}

TEST(List, Test2) {
	std::list<int> s{ 2, 4, 6 };

	// Traverse
	for (int val : s) {
		std::cout << val << " ";
	}

	auto it = s.begin();

	// Assertions
	ASSERT_EQ(s.size(), 3);                // Check the list has 3 elements
	EXPECT_EQ(*it, 2);                     // First element is 2
	++it;
	EXPECT_EQ(*it, 4);                     // Second element is 4
	++it;
	EXPECT_EQ(*it, 6);                     // Third element is 6
	++it;
	EXPECT_EQ(it, s.end());                // Iterator reaches end after last element
	--it;
	EXPECT_EQ(*it, 6);                     // Third element is 6
}
