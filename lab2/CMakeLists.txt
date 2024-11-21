project(os_lab2)

add_library(utils_lab2 src/utils.cpp)
target_include_directories(utils_lab2 PRIVATE include)

add_executable(lab2_main main.cpp)
target_include_directories(lab2_main PRIVATE include)
target_link_libraries(lab2_main utils_lab2)

set(CMAKE_CXX_STANDARD 17)