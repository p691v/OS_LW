#include "../lab2/include/utils.h"
#include <gtest/gtest.h>
#include <chrono>


TEST(ThreadsTests, TestOneThread) {
    double area = Area(1, 3, 1000000);
    double epsilon = 1e-1;
    EXPECT_NEAR(area, 28.274, epsilon);
}

TEST(ThreadsTests, TestEqualityOneAndMultiThreads) {
    double area_one_thread = Area(1, 3, 1000000);
    double area_several_threads = Area(4, 3, 1000000);
    double epsilon = 1e-1;
    std::cout << area_one_thread << " " << area_several_threads << std::endl;
    EXPECT_NEAR(area_one_thread, 28.274, epsilon);
    EXPECT_NEAR(area_several_threads, 28.274, epsilon);
}

TEST(ThreadsTests, TestMultiThreadsFasterOne) {
    auto start = std::chrono::high_resolution_clock::now();
    double area_one_thread = Area(1, 3, 1000000);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_one_thread = end - start;

    start = std::chrono::high_resolution_clock::now();
    double area_several_threads = Area(4, 3, 1000000);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_multi_threads = end - start;

    EXPECT_LT(duration_multi_threads, duration_one_thread);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}