#include "pch.h"

void heapify(std::vector<int>& nums) {
	size_t size = nums.end() - nums.begin();
	size_t first_leaf = size / 2;	// 2->1, 3->1, 4->2
	
	for (size_t index = first_leaf - 1; index != SIZE_MAX; index--) {
		size_t curr_index = index;

		while (curr_index < first_leaf) {
			size_t left = 2 * curr_index + 1;
			size_t right = 2 * curr_index + 2;

			if (right >= size) right = left;	// hack to prevent from outbound

			if (nums[curr_index] >= nums[left] && nums[curr_index] >= nums[right]) break;

			int new_index = (nums[left] > nums[right] ? left : right);
			std::swap(nums[new_index], nums[curr_index]);
			curr_index = new_index;
		}
	}
}

void heapSort(std::vector<int>& nums) {
	//std::make_heap(nums.begin(), nums.end());
	heapify(nums);
	if (!std::is_heap(nums.begin(), nums.end())) {
		std::cout << "NOT HEAP";
	}

	auto it = nums.end();
	while (it != nums.begin()) {
		std::pop_heap(nums.begin(), it);
		it--;
	}
}