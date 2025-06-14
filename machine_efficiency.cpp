#include "pch.h"

using namespace std;

// Find the first index which is lower than local top, or N
void findAfterTop(vector<int>& arr, int& i) {
	while (i < arr.size() && arr[i] >= arr[i - 1]) i++;
}

// Find the first index which is higher than local bottom, or N
void findAfterBottom(vector<int>& arr, int& i) {
	while (i < arr.size() && arr[i] <= arr[i - 1]) i++;
}

int minElementsToRemove(vector<int> arr) {
	int n = arr.size();
	if (n < 2) return n;
	int i;
	for (i=1; i<n; i++)
		if (arr[i] != arr[0]) break;
	if (i >= n) return 1;
	int count = 1;
	bool up = arr[i] > arr[0];

	while (true)
	{
		if (up)
			findAfterTop(arr, i);
		else
			findAfterBottom(arr, i);
		count++;
		if (i >= n) return count;
		up = !up;
	}
}

int minElementsToRemove2(vector<int> arr) {
	int n = arr.size();
	if (n < 2) return n;

	int lastIndex = 0;

	int removals = 0;
	for (int i = 1; i < n - 1; i++)
	{
		if (arr[lastIndex] <= arr[i] && arr[i] <= arr[i + 1]) {
			removals++;
			continue;
		}

		if (arr[lastIndex] >= arr[i] && arr[i] >= arr[i + 1]) {
			removals++;
			continue;
		}

		lastIndex = i;
	}
	if (lastIndex == 0 && arr[n - 1] == arr[0]) removals++;
	return n - removals;
}

void test(int (*func)(vector<int>)) {
	EXPECT_EQ(func({ 1, 2, 3, 4, 5 }), 2);
	EXPECT_EQ(func({ 5, 4, 3, 2, 1 }), 2);

	EXPECT_EQ(func({ 1, 1, 1, 1 }), 1);
	EXPECT_EQ(func({ 10 }), 1);

	EXPECT_EQ(func({ 1, 2, 1, 2, 1 }), 5);
	EXPECT_EQ(func({ 1, 2, 1, 2, 1, 1 }), 5);
	EXPECT_EQ(func({ 1, 1, 2, 1, 2, 1 }), 5);

	EXPECT_EQ(func({ 1, 1, 2, 2, 1, 1 }), 3);
	EXPECT_EQ(func({ 1, 1, 2, 2, 1, 1, 2, 2 }), 4);
}

int countLocalMinimumAndMaximum(std::vector<int> arr)
{
	int last = arr[0];
	int i = 1;
	int count = 1;
	int n = arr.size();

	while (i < n && arr[i] == last)
	{
		i++;
	}

	if (i == n) return 1; // All elements are the same;

	long long direction = arr[i] - last;
	while (i < arr.size())
	{
		auto nextDirection = arr[i] - last;
		if (direction * nextDirection < 0)
		{
			count++;
		}
		if (nextDirection != 0) direction = nextDirection;
		last = arr[i];
		i++;
	}

	if (direction != 0) count++; // Count the last local extremum if it exists
	return count;
}

int countLocalMinimumAndMaximum2(std::vector<int> arr)
{
	int count = 1;
	int n = arr.size();
	int last = arr[0];
	for (int i = 1; i < n - 1; ++i)
	{
		if ((arr[i] < last && arr[i] < arr[i + 1]) ||
			(arr[i] > last && arr[i] > arr[i + 1]))
		{
			count++;
			last = arr[i];
		}
	}
	// Check the last elements
	if (arr[n - 1] != last) count++;
	return count;
}

TEST(MachineEfficiency, minElementsToRemove) {
	test(minElementsToRemove);
} 

TEST(MachineEfficiency, minElementsToRemove2) {
	test(minElementsToRemove2);
}

TEST(MachineEfficiency, countLocalMinimumAndMaximum_test) {
	test(countLocalMinimumAndMaximum);
}

TEST(MachineEfficiency, countLocalMinimumAndMaximum2_test) {
	test(countLocalMinimumAndMaximum2);
}
