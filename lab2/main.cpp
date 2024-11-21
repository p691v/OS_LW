#include <iostream>
#include <chrono>
#include <pthread.h>
#include "include/utils.h"

int main(int argc, char* argv[]) {
    long threads_num = 1, precision = 10000;
    float radius = 1;
    if (argc != 7){
        std::cerr << "Usage: " << argv[0] << " <options>\n"
                  << "Options:\n"
                  << "\t-t NUMBER\t\t Number of threads, running at the same time\n"
                  << "\t-r NUMBER\t\t Radius of a circle to calculate its area\n"
                  << "\t-p NUMBER\t\t Precision of calculations (number of generated points)"
                  << std::endl;
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (arg == "-t")
            threads_num = strtol(argv[i + 1], nullptr, 10);
        else if (arg == "-r")
            radius = strtol(argv[i + 1], nullptr, 10);
        else if (arg == "-p")
            precision = strtol(argv[i + 1], nullptr, 10);
    }
    std::cout << "Running: " << threads_num << " threads" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    double area = Area(threads_num, radius, precision);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Area of the given circle: " << area << std::endl;

    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}