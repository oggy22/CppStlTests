#include "pch.h"
#include <queue>
#include <vector>
#include <gtest/gtest.h> // Include the Google Test framework header
#include <experimental/generator>

std::experimental::generator<int> get_perfect_numbers() {
	uint64_t limit = 2, limit_next = 3;
	for (uint64_t n = 2; n < std::numeric_limits<uint64_t>::max(); n+=2) {
		uint64_t sum = 1;
		if (limit_next * limit_next <= n) { limit_next++; limit++; }
		for (uint64_t i = 2; i <= limit; i++)
			if (n % i == 0)
				sum += i + (n / i);
		if (sum==n) co_yield n;
	}
}

TEST(PerfectNumber, get) {
	int count = 0;
	for (uint64_t n : get_perfect_numbers()) {
		std::cout << n << std::endl;
		count++;
		if (count == 4) break;
	}
}
