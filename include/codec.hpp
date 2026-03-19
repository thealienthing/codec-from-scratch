#pragma once

#include <vector>
#include <cstdint>

std::vector<uint8_t> run_length_encode(const char* data, int size);
std::vector<uint8_t> run_length_decode(const char* data, int size);
void say_hello();