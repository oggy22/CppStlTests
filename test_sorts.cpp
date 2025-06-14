#include "pch.h"

void isSorted(const std::vector<int>& sorted, const std::vector<int>& original) {
	if (sorted.size() != original.size()) {
		// gtest failure message
		FAIL() << "Sorted and original vectors have different sizes.";
		return;
	}

	if (!std::is_sorted(sorted.begin(), sorted.end())) {
		FAIL() << "The vector is not sorted correctly.";
	}

	std::multiset<int> originalSet(original.begin(), original.end());
	std::multiset<int> sortedSet(sorted.begin(), sorted.end());

	if (originalSet != sortedSet) {
		FAIL() << "The sorted vector does not contain the same elements as the original vector.";
	}
}

TEST(Sorts, Test1) {
	// generate a random vector of integers
	std::vector<int> original = { 5, 3, 8, 6, 2, 7, 4, 1 };
	
	std::vector<int> sorted = original;
	bubbleSort(sorted);
	isSorted(sorted, original);
}
