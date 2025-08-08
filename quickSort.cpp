#include "pch.h"

void quickSort_old(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
	size_t size = end - begin;
	if (size < 2) return;
	if (size == 2) {
		if (*begin > *(begin + 1))
			std::swap(*begin, *(begin + 1));
		return;
	}

	int pivot = *(begin + size / 2);

	auto left = begin;
	auto right = end - 1;
	while (true) {
		while (left < right && (*left) <= pivot) left++;
		if (left >= right) break;
		while (left < right && (*right) > pivot) right--;
		if (left >= right) break;
		std::swap(*left, *right);
	}
	quickSort_old(begin, left);
	quickSort_old(left, end);
}

void quickSort(std::vector<int>::iterator begin,
	std::vector<int>::iterator end) {
	auto n = end - begin;
	if (n < 2) return;

	int pivot = *(begin + n / 2);

	auto lt = begin;        // < pivot
	auto i = begin;        // scanning
	auto gt = end;          // > pivot

	while (i < gt) {
		if (*i < pivot) { std::iter_swap(i++, lt++); }
		else if (*i > pivot) { std::iter_swap(i, --gt); }
		else { ++i; } // == pivot
	}

	quickSort(begin, lt);
	quickSort(gt, end);
}

void quickSort(std::vector<int>& nums) {
	quickSort(nums.begin(), nums.end());
	std::cout << "Quick Sort end";
}