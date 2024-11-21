#include <gtest/gtest.h> 
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include <cstring>

extern "C" {
    #include "../lab1/include/utils.h"
    #include "../lab1/include/parent.h"
}

TEST(test_string, test_simple_string)
{ 
    char str[] = "abcdef";
    char expected_str[] = "bcdf";
    ModifyString(str);
    ASSERT_TRUE(strcmp(str, expected_str) == 0);
    
} 

TEST(test_string, test_empty_string)
{ 
    char str[] = "";
    char expected_str[] = "";
    ModifyString(str);
    ASSERT_TRUE(strcmp(str, expected_str) == 0);
    
} 

TEST(test_parent, test) 
{
    const char* fileWithInput = "input.txt";

    constexpr int inputSize = 5;

    std::array<const char*, inputSize> input = {
            "first",
            "second",
            "abcd",
            "efghi",
            "q"
    };

    {
        auto inFile = std::ofstream(fileWithInput);

        for(const auto& line : input) {
            inFile << line << '\n';
        }
    }

    auto deleter = [](FILE* file) {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(deleter)> inFile(fopen(fileWithInput, "r"), deleter);

    Parent("../lab1/child1", "../lab1/child2", inFile.get());

    std::ifstream file1(input[0]);
    std::ifstream file2(input[1]);

    ASSERT_TRUE(file1.good());
    ASSERT_TRUE(file2.good());

    std::string firstOutput;
    std::string secondOutput;

    std::getline(file1, firstOutput);
    std::getline(file2, secondOutput);

    std::string firstExpectedOtput = "bcd";
    std::string secondExpectedOtput = "fgh";

    ASSERT_EQ(firstOutput, firstExpectedOtput);
    ASSERT_EQ(secondOutput, secondExpectedOtput);

    auto removeIfExists = [](const char* path) {
        if(std::filesystem::exists(path)) {
            std::filesystem::remove(path);
        }
    };

    removeIfExists(fileWithInput);
    removeIfExists(input[0]);
    removeIfExists(input[1]);
}
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}