#include "pch.h"

int wordCount1(std::string str) {
	int count = 0;
	bool inWord = false;
	for (char c : str) {
		if (std::isspace(c)) {
			if (inWord) {
				count++;
				inWord = false;
			}
		} else {
			inWord = true;
		}
	}
	if (inWord) {
		count++;
	}
	return count;
}

int wordCount2(std::string str) {
	bool inWord = false;
	int count = 0;
	for (char c : str) {
		if (!std::isspace(c) && !inWord) count++;
		inWord = !std::isspace(c);
	}
	return count;
}

void test(int (*func)(std::string)) {
	EXPECT_EQ(func("hello there"), 2);
	EXPECT_EQ(func("hello there "), 2);
	EXPECT_EQ(func("   hello   there"), 2);
	EXPECT_EQ(func("   oneword "), 1);
}

TEST(WordCount, wordCount1) {
	test(wordCount1);
}

TEST(WordCount, wordCount2) {
	test(wordCount2);
}
