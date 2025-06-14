#include "pch.h"

using namespace std;

TEST(Stack, Test1) {
	std::stack<int> s;
	s.push(10);
	s.push(20);

	int x = s.top();
	EXPECT_EQ(x, 20);

	s.pop();
	int y = s.top();
	EXPECT_EQ(y, 10);
}