#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <cstring>
#include <codec.hpp>
#include <buffer.hpp>
#include <doctest/doctest.h>


const std::string test_file = "video.rgb24";
const int test_file_size = 53996544;
const

TEST_CASE("Testing Run Length Encoding") {
    Buffer COMPRESSES_TO_HALF = Buffer(std::string("AAAABBBBCCCCDDDDEEEEFFFF"));
    int size = COMPRESSES_TO_HALF.size();
    Buffer compressed = rle(COMPRESSES_TO_HALF);
    CHECK(static_cast<float>(compressed.size()) == (size/2.0));
    Buffer decoded = rld(compressed);
    std::cout << "Orig: " << COMPRESSES_TO_HALF.debug_str() << std::endl;
    std::cout << "Decd: " << decoded.debug_str() << std::endl;
    CHECK(decoded == COMPRESSES_TO_HALF);
}


TEST_CASE("Testing read file to buffer") {
    Buffer sample_buf = read_file_to_buffer(test_file);
    
    Buffer rle_buf = rle(sample_buf);
    std::cout << "rle buf sample size is " << rle_buf.size() << std::endl;
    std::cout << "original buf sample size is " << sample_buf.size() << std::endl;
    Buffer rld_buf = rld(rle_buf);
    std::cout << "rld buf sample size is " << rld_buf.size() << std::endl;
    CHECK(rld_buf == sample_buf);

}
// int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

// TEST_CASE("testing the factorial function") {
//     CHECK(factorial(1) == 1);
//     CHECK(factorial(2) == 2);
//     CHECK(factorial(2) == 4);
//     CHECK(factorial(3) == 6);
//     CHECK(factorial(10) == 3628800);
// }