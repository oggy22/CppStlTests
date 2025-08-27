#include "pch.h"
#include <thread>
#include <mutex>

using namespace std;

TEST(lock_and_mutex, increment) {
    std::mutex mtx;
    const int numThreads = 100;
    const int incrementsPerThread = 100000;
    long long counter = 0;
    std::vector<std::thread> threads;

    // Launch threads
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back([&]() {
            for (int j = 0; j < incrementsPerThread; j++) {
                std::lock_guard<std::mutex> lock(mtx); // comment out this line to fail the test
                counter++;
            }
            });
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }
    
    EXPECT_EQ(counter, numThreads * incrementsPerThread);
}
