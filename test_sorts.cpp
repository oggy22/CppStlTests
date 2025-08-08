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

void testSortAlgorithm(std::function<void(std::vector<int>&)> sort_func, std::vector<int>& nums) {
	std::vector<int> copy(nums);
	sort_func(nums);
	isSorted(nums, copy);
}

void testSortAlgorithm(std::function<void(std::vector<int>&)> sort_func) {
	std::vector<int> nums;
	std::mt19937 gen(0);
	std::uniform_int_distribution<> dist_int(1, 100);

	for (int i = 0; i < 100; i++) {
		nums.push_back(dist_int(gen));

		if (i % 5 == 0) {
			std::vector<int> copy(nums);
			testSortAlgorithm(sort_func, copy);
		}
	}
}

TEST(Sorts, Test_bublbleSort) {
	// generate a random vector of integers
	std::vector<int> original = { 5, 3, 8, 6, 2, 7, 4, 1 };
	testSortAlgorithm(bubbleSort, original);
	testSortAlgorithm(bubbleSort);
}

TEST(Sorts, Test_heapSort) {
	// generate a random vector of integers
	std::vector<int> original = { 5, 3, 8, 6, 2, 7, 4, 1 };

	testSortAlgorithm(heapSort, original);
	testSortAlgorithm(heapSort);
}

TEST(Sorts, Test_quickSort) {
	// generate a random vector of integers
	std::vector<int> original = { 5, 3, 8, 6, 2, 7, 4, 1 };

	testSortAlgorithm(quickSort, original);
	testSortAlgorithm(quickSort);
}

TEST(Sorts, Test_mergeSort) {
	// generate a random vector of integers
	std::vector<int> original = { 5, 3, 8, 6, 2, 7, 4, 1 };

	testSortAlgorithm(mergeSort, original);
	testSortAlgorithm(mergeSort);
}
