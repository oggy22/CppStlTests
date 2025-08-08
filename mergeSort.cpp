#include "pch.h"

void mergeSort(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::vector<int>& extra) {
	size_t size = end - begin;
	if (size < 2) return;
	if (size == 2) {
		if (*begin > *(begin + 1))
			std::swap(*begin, *(begin + 1));
		return;
	}

	std::vector<int>::iterator mid = begin + (size / 2);
	mergeSort(begin, mid, extra);
	mergeSort(mid, end, extra);

	std::copy(begin, end, extra.begin());
	std::vector<int>::iterator copyTo = begin;
	std::vector<int>::iterator left = extra.begin();
	std::vector<int>::iterator right = extra.begin() + (size / 2);

	while (left != extra.begin() + (size / 2) && right != extra.begin() + size) {
		if (*left < *right)
			*(copyTo++) = *(left++);
		else
			*(copyTo++) = *(right++);
	}
	std::copy(left, extra.begin() + (size / 2), copyTo);
	std::copy(right, extra.begin() + size, copyTo);
}

void mergeSort(std::vector<int>& nums) {
	std::vector<int> extra(nums.size());
	mergeSort(nums.begin(), nums.end(), extra);
}