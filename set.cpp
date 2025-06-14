#include "pch.h"

using namespace std;

TEST(Set, Test1) {
	std::set<int> s{ 2, 4, 6 };
	EXPECT_TRUE(s.contains(2));
	EXPECT_TRUE(s.contains(4));
	EXPECT_TRUE(s.contains(6));
	EXPECT_FALSE(s.contains(8));
}

TEST(Set, Order) {
	std::set<int> primes;
	primes.insert(3);
	primes.insert(11);
	primes.insert(2);
	primes.insert(5);
	primes.insert(7);

	int lastPrime = INT_MIN;
	for (int prime : primes)
	{
		EXPECT_LE(lastPrime, prime);
	}
}
