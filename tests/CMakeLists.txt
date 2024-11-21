project(os_labs_tests)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)



add_executable(lab1_test lab1_test.cpp)
target_include_directories(lab1_test PUBLIC ../lab1/include)
target_link_libraries(lab1_test PRIVATE utils parent GTest::GTest)

add_executable(lab2_test lab2_test.cpp)
target_include_directories(lab2_test PUBLIC ../lab2/include)
target_link_libraries(lab2_test PRIVATE utils_lab2 GTest::GTest)

enable_testing()
add_test(NAME lab1_test COMMAND lab1_test)
add_test(NAME lab2_test COMMAND lab2_test)

set(CMAKE_CXX_STANDARD 17)