#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <cstring>
#include <codec.hpp>
#include <doctest/doctest.h>


TEST_CASE("Testing Run Length Encoding") {
    auto COMPRESSES_TO_HALF = bytes_from_string("AAAABBBBCCCCDDDDEEEEFFFF");
    int size = COMPRESSES_TO_HALF.size();
    auto compressed = run_length_encode(COMPRESSES_TO_HALF);
    CHECK(static_cast<float>(compressed.size()) == (size/2.0));
    auto decoded = run_length_decode(compressed);
    // CHECK(strcmp(COMPRESSED_TO_HALF, decoded.data());
}
// int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

// TEST_CASE("testing the factorial function") {
//     CHECK(factorial(1) == 1);
//     CHECK(factorial(2) == 2);
//     CHECK(factorial(2) == 4);
//     CHECK(factorial(3) == 6);
//     CHECK(factorial(10) == 3628800);
// }