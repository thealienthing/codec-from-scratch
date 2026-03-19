#include "codec.hpp"
#include <iostream>
#include <memory>
#include <vector>

std::vector<uint8_t> run_length_encode(const char* data, int size)
{
    std::vector<uint8_t> ret;
    for (auto byte = 0; byte < size;) {
        char cur = data[byte];
        int repetitions = 1;
        for (auto next = byte + 1; next < size; next++) {
            // std::cout << "Cur: " << cur << " Next: " << data[next] << std::endl;
            repetitions++;
            if (cur != data[next]) {
                // std::cout << "break" << std::endl;
                break;
            }
        }

        ret.push_back(static_cast<uint8_t>(repetitions));
        ret.push_back(static_cast<uint8_t>(cur));
        byte += repetitions;
    }
    return ret;
}

std::vector<uint8_t> run_length_decode(const char* data, int size)
{
    std::vector<uint8_t> ret;
    for (auto i = 0; i < size; i += 2) {
        int reps = static_cast<int>(data[i]);
        uint8_t val = data[i + 1];
        for (auto r = 0; r < reps; r++) {
            ret.push_back(val);
        }
    }
    return ret;
}

void say_hello() { std::cout << "Hello, from codec-from-scratch!\n"; }
